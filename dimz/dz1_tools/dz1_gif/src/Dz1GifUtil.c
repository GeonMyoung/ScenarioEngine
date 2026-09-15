#include <dz1_bmp.h>
#include "Dz1GifLzw.h"
#include "Dz1GifUtil.h"
#include "Dz1GifStruct.h"



///////////////////////////////////////////////////////////////////////////////
// Local API :: Thread Control
typedef struct ChkDoneArg
{
	Dz1Error *err_hold;
	u32_t cnt;
} ChkDoneArg;

static Dz1Error _chk_done(void *ptr, Dz1GifDataEntry *p)
{
	ChkDoneArg *arg = (ChkDoneArg *)ptr;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (p->present == Dz1GifDataEntryPresent_graphic)
	{
		Dz1GifGraphic *gb = p->x.graphic;
		if (gb->thid != -1)
		{
			if (gb->isDone == FALSE)
			{
				arg->cnt++;
				//Dz1Thread_printf("@@@ Thread %08X running\n", gb->thid);
			}
			else
			{
				//Dz1Thread_printf("@@@ Thread %08X done\n", gb->thid);
				Dz1Thread_wait(gb->thid, arg->err_hold);
				gb->thid = -1;
			}
		}
	}
	Dz1Error_set(errp, 0);

	return err;
}

static Dz1Error _thread_all_done(Dz1GifDataArr *arr, bool_t *isAllDone, Dz1Error *err_hold)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	ChkDoneArg arg = { err_hold, 0 };
	*isAllDone = FALSE;
	if ((*errp = arr->travel(arr, _chk_done, (void *)&arg)).code)
	{	// Error 발생 -> Err Hold에 복사
		ERR_OUT(errp);
		memcpy(err_hold, errp, sizeof(Dz1Error));
		Dz1Error_set(errp, 0);
	}
	else if (arg.cnt == 0)
	{	// Error 없고 실행중인 쓰레드 0
		*isAllDone = TRUE;
		memcpy(errp, err_hold, sizeof(Dz1Error));
	}
	else
	{	// Error 는 없지만 실행중인 쓰래드 있음
		Dz1Thread_printf("### Still Running %u Thread\n", arg.cnt);
	}
	return err;
}

typedef struct ThreadWaitArg
{
	Dz1GifDataArr *arr;
	Dz1Error *err_hold;
} ThreadWaitArg;

static Dz1Error _chk_thread_all_done(void *ptr, bool_t *wakeup)
{
	ThreadWaitArg *arg = (ThreadWaitArg *)ptr;
	Dz1GifDataArr *arr = arg->arr;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if ((*errp = _thread_all_done(arr, wakeup, arg->err_hold)).code) ERR_OUT(errp);
	return err;
}

Dz1Error _Dz1Gif_waitThreadWork(Dz1GifDataArr *arr, Dz1Sync *sync)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1Error err_hold = DZ1_ERROR_INITIALIZER;
	ThreadWaitArg arg = { arr, &err_hold };
	bool_t isDone = FALSE;

	u64_t dur;
	
	while((*errp = _thread_all_done(arr, &isDone, &err_hold)).code == 0 && isDone == FALSE)
	{
		dur = DZ1UINT64(5000000);
		Dz1Sync_wait(sync, &dur, _chk_thread_all_done, (void *)&arg);
	}

	if (errp->code == 0)
		memcpy(errp, &err_hold, sizeof(Dz1Error));

	return err;
}

Dz1Error Dz1Gif_waitThreadWork(Dz1GifDataArr *arr, Dz1Sync *sync)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1Sync_lock(sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)sync);

	if ((*errp = _Dz1Gif_waitThreadWork(arr, sync)).code) ERR_OUT(errp);

	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)sync);
	return err;
}
// Local API :: Thread Control
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local API :: Convert Pixel <-> LZW
Dz1Error _convert_LZW2pixels(Dz1Binary *dst, Dz1GifTableBasedImgData *src, Dz1GifImgDescr *local_descr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	size_t img_size = local_descr->width * local_descr->height;
	if ((dst->data = (u8_t *)Dz1Malloc((dst->size = (u32_t)img_size), errp)) == NULL) ERR_OUT(errp);
	else
	{
		if ((*errp = Dz1GifLzw_dec(dst, src, local_descr)).code) ERR_OUT(errp);
	}

	return err;
}

Dz1Error _convert_pixels2LZW(Dz1GifTableBasedImgData *dst, Dz1Binary *src, Dz1GifImgDescr *descr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	ERR_SET_OUT(errp, ENOSYS);

	return err;
}
// Local API :: Convert Pixel <-> LZW
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local API :: Dz1GifDecodeOpt
static Dz1Error _lzw_decde_th(void *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1GifParallelArg *arg = (Dz1GifParallelArg *)ptr;

	Dz1GifDecodeOptParallel *opt = arg->opt;
	Dz1GifGraphic *graphic = arg->graphic;
	Dz1GifRenderingData *data = graphic->data;

	pthread_cleanup_push(Dz1GifParallelArg_delAndSetNull, (void *)&arg);


	if (data->present == Dz1GifRenderingDataPresent_tbi)
	{
		Dz1GifRenderTableBasedImg *p = data->x.tbi;
		if ((*errp = _convert_LZW2pixels(p->pixels, p->lzw, p->descr)).code) ERR_OUT(errp);
	}

	Dz1Sync_lock(opt->sync);
	pthread_cleanup_push(Dz1Sync_lockCancel, (void *)opt->sync);

	graphic->isDone = TRUE;
	Dz1Sync_signal(opt->sync);

	pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)graphic->sync);

	pthread_cleanup_pop(1); // (Dz1GifParallelArg_delAndSetNull, (void *)&arg);
	return err;
}

static Dz1Error Dz1GifDecodeOpt_sceneOperParallel(Dz1GifDecodeOptParallel *opt, Dz1GifDescr *descr, Dz1GifGraphic *graphic)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1GifRenderingData *data = graphic->data;
	if (data->present == Dz1GifRenderingDataPresent_pte)
	{
		graphic->thid = -1;
		graphic->isDone = TRUE;
	}
	else if (data->present == Dz1GifRenderingDataPresent_tbi)
	{
		Dz1GifParallelArg *arg = NULL;
		
		//Dz1Thread_printf("@@@ GIF Parallel Frame %u\n", opt->seq++);
		
		if ((arg = Dz1GifParallelArg_new(opt, descr, graphic, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1GifParallelArg_delAndSetNull, (void *)&arg);
			if ((*errp = Dz1Thread_create(&graphic->thid, _lzw_decde_th, (void *)arg, DZ1_THREAD_LOG_BASIS)).code) ERR_OUT(errp);
			else
			{
				//Dz1Thread_printf("@@@ Decompress Thread %08X start\n", graphic->thid);
				arg = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1GifParallelArg_delAndSetNull, (void *)&arg);
		}
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}

Dz1BMP *Dz1GifUtil_createBKG(u16_t width, u16_t height, Dz1Error *errp)
{
	Dz1BMP *ret = Dz1BMP_create(width, height, Dz1BMPBPP_colorTrue, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1BMP_fill(ret, 0, 0, 0);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1GifDescr_getBgColor(Dz1GifDescr *descr, u8_t *r, u8_t *g, u8_t *b)
{
	if (descr != NULL && descr->gctPresent)
	{
		Dz1GifColorArray *palette = descr->palette;
		Dz1GifColor *color = Dz1GifColorArray_getColor(palette, descr->bgcIdx);
		if (color != NULL)
		{
			*r = color->red;
			*g = color->green;
			*b = color->blue;
		}
	}
}

Dz1BMP *Dz1GifUtil_createBackground(Dz1GifDescr *descr, Dz1Error *errp)
{
	Dz1BMP *ret = Dz1BMP_create(descr->width, descr->height, Dz1BMPBPP_colorTrue, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		u8_t r = 0, g = 0, b = 0;
		if (descr != NULL) Dz1GifDescr_getBgColor(descr, &r, &g, &b);
		Dz1BMP_fill(ret, r, g, b);
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static Dz1Error Dz1GifDecodeOpt_sceneOperSequential(Dz1GifDecodeOptSequential *opt, Dz1GifDescr *descr, Dz1GifGraphic *graphic)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1GifRenderingData *data = graphic->data;

	//Dz1Thread_printf("@@@ GIF Sequential frame %u\n", opt->seq);

	if (opt->canvas == NULL && (opt->canvas = Dz1GifUtil_createBKG(descr->width, descr->height, errp)) == NULL) ERR_OUT(errp);
	else if (opt->last == NULL && (opt->last = Dz1GifUtil_createBackground(descr, errp)) == NULL) ERR_OUT(errp);
	else if (data->present == Dz1GifRenderingDataPresent_pte)
	{
	}
	else if (data->present == Dz1GifRenderingDataPresent_tbi)
	{
		Dz1GifRenderTableBasedImg *p = data->x.tbi;
		if ((*errp = _convert_LZW2pixels(p->pixels, p->lzw, p->descr)).code) ERR_OUT(errp);
		else
		{
			u32_t dur;
			if ((*errp = Dz1GifUtil_render(descr, graphic, opt->canvas, opt->last, &dur)).code) ERR_OUT(errp);
			else opt->user_handle(opt->user_ptr, opt->seq++, dur, opt->canvas);
		}
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}

Dz1Error Dz1GifDecodeOpt_sceneOper(Dz1GifDecodeOpt *opt, Dz1GifDescr *descr, Dz1GifGraphic *graphic)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (opt->present == Dz1GifDecodeOptPresent_sequential)
	{
		if ((*errp = Dz1GifDecodeOpt_sceneOperSequential(opt->x.sequential, descr, graphic)).code) ERR_OUT(errp);
	}
	else if (opt->present == Dz1GifDecodeOptPresent_parallel)
	{
		if ((*errp = Dz1GifDecodeOpt_sceneOperParallel(opt->x.parallel, descr, graphic)).code) ERR_OUT(errp);
	}
	else ERR_SET_OUT(errp, EINVAL);

	return err;
}

Dz1Error Dz1GifDecodeOpt_postProc(Dz1GifDecodeOpt *opt, Dz1GifDataArr *datas)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (opt == NULL || datas == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (opt->present == Dz1GifDecodeOptPresent_sequential) { }
	else if (opt->present == Dz1GifDecodeOptPresent_parallel)
	{
		Dz1GifDecodeOptParallel *parallel = opt->x.parallel;
		if ((*errp = Dz1Gif_waitThreadWork(datas, parallel->sync)).code) ERR_OUT(errp);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return err;
}

// Local API :: Dz1GifDecodeOpt
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Public API :: Count Graphic
static Dz1Error _countGraphic(void *ptr, Dz1GifDataEntry *p)
{
	u32_t *ret = (u32_t *)ptr;
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (p->present == Dz1GifDataEntryPresent_graphic)
	{
		Dz1GifGraphic *graphic = p->x.graphic;
		Dz1GifRenderingData *data = graphic->data;
		if (data->present == Dz1GifRenderingDataPresent_tbi) (*ret)++;
	}
	Dz1Error_set(errp, 0);
	return err;
}

u32_t Dz1GifUtil_countGraphic(Dz1Gif *gif)
{
	u32_t ret = 0;
	if (gif) gif->datas->travel(gif->datas, _countGraphic, (void *)&ret);
	return ret;
}
// Public API :: Count Graphic
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Public API :: Palette Helper
Dz1GifColor *_Dz1GifColorArray_getColor(Dz1GifColorArray *palette, u32_t idx, char *__file__, int __line__)
{
	Dz1GifColor *ret = NULL;

	if (palette == NULL) { }
	else
	{
		if (palette->idx == NULL)
			palette->idx = _Dz1GifColorIndex_new(palette->list, NULL, __file__, __line__);

		if (idx >= palette->idx->numOfColor) { }
		else ret = palette->idx->colors[idx];
	}
	return ret;
}

bool_t _Dz1GifColorArray_available(Dz1GifColorArray *palette, char *__file__, int __line__)
{
	bool_t ret = FALSE;

	if (palette != NULL)
	{
		if (palette->list != NULL && palette->list->count(palette->list) > 0)
		{
			if (palette->idx == NULL)
				palette->idx = _Dz1GifColorIndex_new(palette->list, NULL, __file__, __line__);
			ret = TRUE;
		}
	}

	return ret;
}
// Public API :: Palette Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Public API :: BitBlt
// static __inline__ Dz1GifColor color_white = { 0, 0xFF, 0xFF, 0xFF };
static u32_t _get_pixel(Dz1Binary *pixels, u16_t x, u16_t y, Dz1GifImgDescr *descr)
{
	if (x >= descr->width || y >= descr->height) return -1;
	else
	{
		u32_t pos = y * descr->width + x;
		return pixels->data[pos];
	}
}

static u32_t _get_pixel_ex(Dz1Binary *pixels, u32_t x, u32_t y, Dz1GifImgDescr *descr)
{
	if (x < descr->x || descr->x + descr->width <= x) return -1;
	else if (y < descr->y || descr->y + descr->height <= y) return -1;
	else
	{
		u32_t pos = (y - descr->y) * descr->width + (x - descr->x);
		return pixels->data[pos];
	}
}

Dz1Error Dz1GifUtil_bitblt(Dz1BMP *work_bmp,
						   Dz1GifDescr *global_descr,
						   Dz1GifImgDescr *local_descr,
						   Dz1GifGraphicControlExt *ctrl,
						   Dz1GifColorArray *palette,
						   Dz1GifRenderTableBasedImg *img)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1GifColor *color = NULL;
	u16_t x, y, reverse_y, global_y;
	u32_t idx;

	for (y = 0; errp->code == 0 && y < local_descr->height; y++)
	{
		global_y = local_descr->y + y;
		reverse_y = (global_descr->height - 1) - global_y;
		for (x = 0; errp->code == 0 && x < local_descr->width; x++)
		{
			if ((idx = _get_pixel(img->pixels, x, y, local_descr)) == -1) ERR_SET_OUT(errp, EFAULT);
			else if (ctrl->tpColPresent && ctrl->tpColorIdx == idx) { /* 투명색 -> NOP */ }
			else if ((color = Dz1GifColorArray_getColor(palette, idx))  == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1BMP_setPixelTrueColor(work_bmp, local_descr->x + x, reverse_y, color->red, color->green, color->blue);
		}
	}
	return err;
}

Dz1Error Dz1GifUtil_bitbltWithBgColor(Dz1BMP *dst,
									  Dz1GifDescr *global_descr,
									  Dz1GifImgDescr *local_descr,
									  Dz1GifGraphicControlExt *ctrl, 
									  Dz1GifColorArray *palette,
									  Dz1GifRenderTableBasedImg *img,
									  Dz1GifColor *bgColor)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1GifColor white = { 0, 255, 255, 255 };

	Dz1GifColor *color = NULL;
	register u32_t x, y, reverse_y;
	register u32_t idx;

	if (bgColor == NULL) bgColor = &white;

	for (y = 0, reverse_y = global_descr->height - 1; y < global_descr->height; y++, reverse_y--)
	{
		for (x = 0; x < global_descr->width; x++)
		{
			if ((idx = _get_pixel_ex(img->pixels, x, y, local_descr)) == -1)
			{	// 영역의 바깥쪽
				color = bgColor;
				Dz1BMP_setPixelTrueColor(dst, x, reverse_y, color->red, color->green, color->blue);
			}
			else if (ctrl->tpColPresent && ctrl->tpColorIdx == idx)
			{	// 영역 내부 하지만 투명 컬러가 지정됨
				color = bgColor;
				Dz1BMP_setPixelTrueColor(dst, x, reverse_y, color->red, color->green, color->blue);
			}
			else if ((color = Dz1GifColorArray_getColor(palette, idx))  == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1BMP_setPixelTrueColor(dst, x, reverse_y, color->red, color->green, color->blue);
		}
	}
	return err;
}

Dz1Error Dz1GifUtil_bitbltWithPrevious(Dz1BMP *dst,
									   Dz1GifDescr *global_descr,
									   Dz1GifImgDescr *local_descr,
									   Dz1GifGraphicControlExt *ctrl, 
									   Dz1GifColorArray *palette,
									   Dz1GifRenderTableBasedImg *img,
									   Dz1BMP *prev)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1GifColor *color = NULL;
	register u32_t x, y, reverse_y;
	register u32_t idx;
	u32_t r = 0, g = 0, b = 0;

	for (y = 0, reverse_y = global_descr->height - 1; y < global_descr->height; y++, reverse_y--)
	{
		for (x = 0; x < global_descr->width; x++)
		{
			if ((idx = _get_pixel_ex(img->pixels, x, y, local_descr)) == -1)
			{	// 영역의 바깥쪽
				Dz1BMP_getPixelTrueColor(prev, x, reverse_y, &r, &g, &b);
				Dz1BMP_setPixelTrueColor(dst, x, reverse_y, r, g, b);
			}
			else if (ctrl->tpColPresent && ctrl->tpColorIdx == idx)
			{	// 영역 내부 하지만 투명 컬러가 지정됨
				Dz1BMP_getPixelTrueColor(prev, x, reverse_y, &r, &g, &b);
				Dz1BMP_setPixelTrueColor(dst, x, reverse_y, r, g, b);
			}
			else if ((color = Dz1GifColorArray_getColor(palette, idx))  == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1BMP_setPixelTrueColor(dst, x, reverse_y, color->red, color->green, color->blue);
		}
	}
	return err;
}
// Public API :: BitBlt
///////////////////////////////////////////////////////////////////////////////

static Dz1Error _bitblt(Dz1BMP *dst, u16_t width, u16_t height,
						Dz1GifColorArray *palette, Dz1Binary *pixels,
						Dz1GifColor *tp, Dz1GifImgDescr *descr,
						Dz1GifColor *bg, Dz1BMP *last, int mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t idx = 0;
	Dz1GifColor *color;
	u16_t src_x, src_y, dst_y;
	u32_t r = 0, g = 0, b = 0;
	for (src_y = 0, dst_y = height - 1; src_y < height; src_y++, dst_y--)
	{
		for (src_x = 0; src_x < width; src_x++)
		{
			if ((idx = _get_pixel_ex(pixels, src_x, src_y, descr)) == -1 ||
				(tp != NULL && tp->idx == idx))
			{	// 영역의 바깥쪽 || 투명
				switch(mode)
				{
				case 0: break;	// NOP
				case 1:			// Use BG Color
					Dz1BMP_setPixelTrueColor(dst, src_x, dst_y, bg->red, bg->green, bg->blue);
					break;
				case 2:			// Use Last BMP Color
					Dz1BMP_getPixelTrueColor(dst, src_x, dst_y, &r, &g, &b);
					Dz1BMP_setPixelTrueColor(dst, src_x, dst_y, r, g, b);
					break;
				}
			}
			else if ((color = Dz1GifColorArray_getColor(palette, idx))  == NULL) ERR_SET_OUT(errp, EFAULT);
			else Dz1BMP_setPixelTrueColor(dst, src_x, dst_y, color->red, color->green, color->blue);
		}
	}
	return err;
}

static Dz1Error _Dz1GifUtil_render(u16_t width, u16_t height, Dz1GifColorArray *palette,
								   Dz1GifRenderingData *data, Dz1BMP *canvas,
								   Dz1GifGraphicControlExt *gce,
								   Dz1GifColor *bg, Dz1BMP *last, int mode)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (data->present == Dz1GifRenderingDataPresent_pte)
	{
		//Dz1GifRenderPlainTextExt *pte = data->x.pte;
		ERR_SET_OUT(errp, ENOSYS);
	}
	else if (data->present == Dz1GifRenderingDataPresent_tbi)
	{
		Dz1GifRenderTableBasedImg *tbi = data->x.tbi;
		Dz1GifImgDescr *lDescr = tbi->descr;
		Dz1GifColorArray *pal = lDescr->palette != NULL ? lDescr->palette : palette;
		if (pal == NULL)
		{
			ERR_SET_OUT(errp, EFAULT);
		}
		else
		{
			Dz1GifColor *tp = gce == NULL || gce->tpColPresent == FALSE ? NULL : Dz1GifColorArray_getColor(pal, gce->tpColorIdx);
			Dz1Binary *pixels = tbi->pixels;
			if ((*errp = Dz1BMP_copyImage(canvas, last)).code) ERR_OUT(errp);
			else if ((*errp = _bitblt(canvas, width, height, pal, pixels, tp, lDescr, bg, last, mode)).code) ERR_OUT(errp);
		}
	}
	return err;
}

Dz1Error Dz1GifUtil_render2(u16_t width, u16_t height,
							Dz1GifColorArray *palette, Dz1GifColor *bgColor,
							Dz1GifGraphic *src, Dz1BMP *canvas, Dz1BMP *last,
							u32_t *ret_dur_ms)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t _dur, *durp = ret_dur_ms ? ret_dur_ms : &_dur;
	if (bgColor == NULL || src == NULL || canvas == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1GifGraphicControlExt _dumb = { Dz1GifGraphicControlCmd_doNotDispose, FALSE, FALSE, 10, 0 };
		Dz1GifGraphicControlExt *gce = src->gce == NULL ? &_dumb : src->gce;
		Dz1GifRenderingData *data = src->data;

		if ((*errp = _Dz1GifUtil_render(width, height, palette, data, canvas, gce, bgColor, NULL, 0)).code) ERR_OUT(errp);
		else
		{
			(*durp) = gce->delay * 10;

			// Background Frame처리
			switch(gce->disposal)
			{
			default:
			case Dz1GifGraphicControlCmd_noMean:
			case Dz1GifGraphicControlCmd_doNotDispose:
				if ((*errp = Dz1BMP_copyImage(last, canvas)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1GifGraphicControlCmd_restoreToBgColor:
				if ((*errp = Dz1BMP_fill(last, bgColor->red, bgColor->green, bgColor->blue)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1GifGraphicControlCmd_restoreToPrev:
				break;
			}
		}
	}
	return err;
}

static Dz1GifColor _Dz1GifDefaultBKGColor = { 0, 0x0, 0x0, 0x0 };
Dz1GifColor *Dz1GifDefaultBKGColor = &_Dz1GifDefaultBKGColor;

Dz1Error Dz1GifUtil_render(Dz1GifDescr *descr, Dz1GifGraphic *src,
						   Dz1BMP *canvas, Dz1BMP *last, 
//						   Dz1GifGraphicControlCmd *prev_dispose,
						   u32_t *ret_dur_ms)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (descr == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1GifColorArray *palette = descr->palette;
		Dz1GifColor *bgColor = palette ? Dz1GifColorArray_getColor(palette, descr->bgcIdx) : Dz1GifDefaultBKGColor;
//		if ((*errp = Dz1GifUtil_render2(descr->width, descr->height, palette, bgColor, src, canvas, last, prev_dispose, ret_dur_ms)).code) ERR_OUT(errp);
		if ((*errp = Dz1GifUtil_render2(descr->width, descr->height, palette, bgColor, src, canvas, last, ret_dur_ms)).code) ERR_OUT(errp);
	}
	return err;
}
