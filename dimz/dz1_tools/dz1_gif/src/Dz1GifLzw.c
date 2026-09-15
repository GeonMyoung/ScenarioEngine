#include "Dz1GifLzw.h"

#define PRINT_ERR(v)			do { Dz1Thread_printf("%s(%d) = %s:%u\n", strerror(v), v, __FILE__, __LINE__); } while(0)
#define PRINT_ERR_WITH(v, c)	do { (v) = (c); Dz1Thread_printf("%s(%d) = %s:%u\n", strerror(v), v, __FILE__, __LINE__); } while(0)
typedef struct MyStream
{
	u8_t *ptr;
	size_t size;
} MyStream;

static int MyStream_getc(MyStream *p)
{
	int ret = 0;
	if (p == NULL) ret = -1;
	else if (p->size == 0) ret = -1;
	else
	{
		ret = (int)(*p->ptr);
		p->ptr++;
		p->size--;
	}
	return ret;
}

#define MAX_CODES 4096
typedef struct Dz1GifLzwCtx
{
	u8_t	stack[MAX_CODES + 2];
	u8_t	suffix[MAX_CODES + 2];
	u16_t	prefix[MAX_CODES + 2];

	u32_t	curr_size;

	u32_t	clear_code;
	u32_t	eof_code;

	u32_t	first_available_code;

	u32_t	table_max;
	u32_t	table_usage;
} Dz1GifLzwCtx;

static void Dz1GifLzwCtx_init(Dz1GifLzwCtx *ctx, int code_size)
{
	ctx->curr_size = code_size + 1;
	ctx->table_max = 1 << ctx->curr_size;
	ctx->clear_code = 1 << code_size;
	ctx->eof_code = ctx->clear_code + 1;
	ctx->table_usage = ctx->first_available_code = ctx->clear_code + 2;
}

static __inline__ void Dz1GifLzwCtx_del(Dz1GifLzwCtx *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

static u32_t code_mask[13] =
{
   0x0000L, 0x0001L, 0x0003L, 0x0007L,		// 0 ~ 3
   0x000FL, 0x001FL, 0x003FL, 0x007FL,		// 4 ~ 7
   0x00FFL, 0x01FFL, 0x03FFL, 0x07FFL,		// 8 ~ 11
   0x0FFFL									// 12
};

typedef struct Dz1GifSource
{
	MyStream	*stream;

	u8_t		 b_out;
	u32_t		 bits_left;
} Dz1GifSource;

static u32_t Dz1GifSource_getBits(Dz1GifSource *ctx, u32_t bit_len, u32_t eof_code)
{
	int temp;
	u32_t ret_len = bit_len, work_bit_len;

	u32_t ret = 0, ret_temp = 0;
	u32_t dst_pos = 0;

	while(bit_len)
	{
		if (ctx->bits_left == 0)
		{
			// 남은 비트수가 없으니 하나 가져온다.
			if ((temp = MyStream_getc(ctx->stream)) < 0) { ret = eof_code; break; }
			else
			{
				ctx->b_out = (u8_t)(temp & 0xFF);
				ctx->bits_left = 8;
			}
		}

		work_bit_len = bit_len < ctx->bits_left ? bit_len : ctx->bits_left;

		ret_temp = (ctx->b_out >> (8 - ctx->bits_left)) & code_mask[bit_len];// 남아있는 비트를 ret의 LSB에 맞춰서 담아둔다.
		ret |= ret_temp << dst_pos;

		dst_pos += work_bit_len;
		bit_len -= work_bit_len;
		ctx->bits_left -= work_bit_len;
	}

	if (ret != eof_code) ret &= code_mask[ret_len];

	return ret;
}

static u16_t _calc_row(u16_t y, Dz1GifImgDescr *descr)
{
	u16_t ret = 0;
	if (descr->isInterlaced)
	{
		u16_t pass1 =		  ((descr->height + 7) / 8);
		u16_t pass2 = pass1 + ((descr->height + 3) / 8);
		u16_t pass3 = pass2 + ((descr->height + 1) / 4);

		if (0 <= y && y < pass1)
		{
			ret = (y * 8) % descr->height;
		}
		else if (pass1 <= y && y < pass2)
		{
			u16_t v = y - pass1;
			ret = (v * 8 + 4) % descr->height;
		}
		else if (pass2 <= y && y < pass3)
		{
			u16_t v = y - pass2;
			ret = (v * 4 + 2) % descr->height;
		}
		else
		{
			u16_t v = y - pass3;
			ret = (v * 2 + 1) % descr->height;
		}
	}
	else ret = y;
	return ret;
}

typedef struct Dz1GifDestination
{
	u16_t			x;
	u16_t			y;
	Dz1Binary		*plane;
	Dz1GifImgDescr	*descr;
} Dz1GifDestination;

static int Dz1GifDestination_put(Dz1GifDestination *dst, u8_t pixel)
{
	int err = 0;

	Dz1GifImgDescr *descr = dst->descr;
	Dz1Binary *dst_plane = dst->plane;
	if (dst->y >= descr->height)
	{
		Dz1Thread_printf("descr = "); Dz1GifImgDescr_dump(descr, 0);
		Dz1Thread_printf("Next Pixel = %u, %u\n", dst->x, dst->y);
		err = ENOMEM;
	}
	else
	{
		u16_t row = _calc_row(dst->y, descr);
		u8_t *stride = &dst_plane->data[row * descr->width];

		stride[dst->x] = pixel;

		dst->x++;
		if (dst->x == descr->width)
		{
			dst->x = 0;
			dst->y++;
		}
	}
	return err;
}

#define PIXEL_OF(x)			x
#define CODE_OF(x)			x

#define ADD_PIXEL_TO_STACK(stkp, v, ctxp, errv)				do { if ( (stkp) >= ( (ctxp)->stack + MAX_CODES) ) PRINT_ERR_WITH((errv), ENOMEM); else { *(stkp) = (v); (stkp)++; } } while(0)

typedef struct Dz1GifLzwEnv
{
	bool_t isFirstCode;

	u32_t code;
	u32_t fetch_code;

	u32_t appended_first_pixel;
	u32_t old_pixel;

	u8_t *stack_ptr;
} Dz1GifLzwEnv;

static int _put_stack(Dz1GifLzwEnv *env, Dz1GifLzwCtx *ctx)
{
	int err = 0;
	while (err == 0 && env->code >= ctx->first_available_code)
	{
		ADD_PIXEL_TO_STACK(env->stack_ptr, ctx->suffix[env->code], ctx, err);	// suffix table에서 code에 대한 스트링을 찾아서 stack에 삽입
		env->code = ctx->prefix[env->code];										// code값을 prefix table에서 찾아서 대입
	}
	if (err == 0)
		ADD_PIXEL_TO_STACK(env->stack_ptr, PIXEL_OF((u8_t)(env->code & 0xFF)), ctx, err);
	return err;
}

static int _add_string(Dz1GifLzwEnv *env, Dz1GifLzwCtx *ctx)
{
	int err = 0;
	if (ctx->table_usage < ctx->table_max)
	{	
		env->appended_first_pixel = PIXEL_OF(env->code);
		ctx->suffix[ctx->table_usage]	= env->appended_first_pixel;
		ctx->prefix[ctx->table_usage++]	= env->old_pixel;
		env->old_pixel = PIXEL_OF(env->fetch_code);
	}

	if (ctx->table_usage >= ctx->table_max && ctx->curr_size < 12)
	{	// code_size 확장
		ctx->table_max <<= 1;
		ctx->curr_size++;
	}

	return err;
}

static int _flush_stack(Dz1GifDestination *dst, Dz1GifLzwEnv *env, Dz1GifLzwCtx *ctx)
{
	int err = 0;
	while (err == 0 && env->stack_ptr > ctx->stack)
	{
		env->stack_ptr--;
		if ((err = Dz1GifDestination_put(dst, *env->stack_ptr)) != 0) PRINT_ERR(err);
	}
	return err;
}

static int _normal_code_proc(Dz1GifDestination *dst, Dz1GifLzwEnv *env, Dz1GifLzwCtx *ctx)
{
	int err = 0;
	if (env->isFirstCode)
	{	// first code process
		env->isFirstCode = FALSE;
		if (env->fetch_code >= ctx->table_usage) env->fetch_code = 0;			// don't care
		env->old_pixel = env->appended_first_pixel = PIXEL_OF(env->fetch_code);

		if ((err = Dz1GifDestination_put(dst, (u8_t)(PIXEL_OF(env->fetch_code) & 0xFF) )) != 0) PRINT_ERR(err); // 출력
	}
	else
	{	// after first code process
		env->code = env->fetch_code;
		if (env->code >= MAX_CODES) PRINT_ERR_WITH(err, E2BIG);
		else
		{
			if (env->code >= ctx->table_usage)
			{	// 사전에 없는 코드
				env->code = CODE_OF(env->old_pixel);
				ADD_PIXEL_TO_STACK(env->stack_ptr, env->appended_first_pixel, ctx, err);
			}

			if ((err = _put_stack(env, ctx)) != 0) PRINT_ERR(err);
			else if ((err = _add_string(env, ctx)) != 0) PRINT_ERR(err);
			else if ((err = _flush_stack(dst, env, ctx)) != 0) PRINT_ERR(err);
		}
	}
	return err;
}

Dz1Error Dz1GifLzw_dec(Dz1Binary *dst_plane, Dz1GifTableBasedImgData *data, Dz1GifImgDescr *descr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	// init source
	Dz1Binary *bin = data->lzw;
	MyStream stream = { bin->data, bin->size };
	Dz1GifSource bit_supply = { &stream, 0, 0 };

	// init destination
	Dz1GifDestination dst = { 0, 0, dst_plane, descr };

	// Set Initial Code Size
	u32_t code_size = data->lzwMinimumCodeSize;

	Dz1GifLzwCtx *ctx = NULL;

	if (code_size < 2 || 9 < code_size)
	{
		ERR_SET_OUT(errp, EFAULT);
	}
	else if ((ctx = (Dz1GifLzwCtx *)Dz1Calloc(sizeof(Dz1GifLzwCtx), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		int status = 0;
		Dz1GifLzwEnv env = { TRUE, 0, 0, 0, 0, ctx->stack };
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ctx);

		Dz1GifLzwCtx_init(ctx, code_size);

		while (errp->code == 0 && dst.y < descr->height)
		{
			pthread_testcancel();
			env.fetch_code = Dz1GifSource_getBits(&bit_supply, ctx->curr_size, ctx->eof_code);
			if (env.fetch_code == ctx->eof_code)
			{	// EOF
				if (env.isFirstCode) ERR_SET_OUT(errp, EPIPE);
				break;
			}
			else if (env.fetch_code == ctx->clear_code)
			{	// clean code
				Dz1GifLzwCtx_init(ctx, code_size);
				env.isFirstCode = TRUE;
				continue;
			}
			// normal code
			else if ((status = _normal_code_proc(&dst, &env, ctx)) != 0) ERR_SET_OUT(errp, status);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&ctx);
	}
	return err;
}

