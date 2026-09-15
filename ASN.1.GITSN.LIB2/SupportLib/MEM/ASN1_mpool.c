
#include "ASN1_mpool.h"



/********************************************************************************/
/* Description: Create a new pool -- pass zero for default              		*/
/* Input:                                                                       */
/*       size:the size of the first blob of memory that will be allocated		*/
/* Output: none                                                                 */
/* Return: address of the new pool									        	*/
/********************************************************************************/
static struct mpool_blob *new_mpool_blob(ASNUINT32 size)
{
    struct mpool_blob *blob = malloc(sizeof(struct mpool_blob));

    if (size == 0) size = DEFAULT_MPOOL_SIZE;

    blob->base = blob->ptr = malloc(size);
    blob->size = size;
    blob->next = NULL;

    return blob;
}

/********************************************************************************/
/* Description: Create a new pool -- pass zero for default              		*/
/* Input:                                                                       */
/*       size:the size of the first blob of memory that will be allocated		*/
/* Output: none                                                                 */
/* Return: address of the new pool									        	*/
/********************************************************************************/
struct mpool *new_mpool(ASNUINT32 size)
{
    struct mpool *ret = malloc(sizeof(struct mpool));

    ret->blob = new_mpool_blob(size);

    return ret;
}

/********************************************************************************/
/* Description: Free a pool              		                              	*/
/* Input:                                                                       */
/*       pool: the new pool		                                                */
/* Output: none                                                                 */
/* Return: none                 									        	*/
/********************************************************************************/
ASNVoid free_mpool(struct mpool *pool)
{
    struct mpool_blob *p, *p_next;

    if (!pool) return;
    if (!pool->blob) {
	return;
    }

    p = pool->blob;

    while(p) {
	p_next = p->next;
	free(p->base);
	free(p);
	p = p_next;
    }

    free(pool);
}

#ifdef ROUNDUP
#undef ROUNDUP
#endif

/* round up to the next multiple of 16 bytes if necessary */
/* 0xFF...FFF0 = ~0 ^ 0xF */
#define ROUNDUP(num) (((num) + 15) & (~((ASNUINT32L) 0x0) ^ 0xF))


/********************************************************************************/
/* Description: Allocate from a pool                                			*/
/* Input:                                                                       */
/*       pool:the pool that be allocate                                         */ 
/*       size:the size of memory that will be allocated from the pool           */		                                                      
/* Output: none                                                                 */
/* Return: none                 									        	*/
/********************************************************************************/
ASNVoid *mpool_malloc(struct mpool *pool, ASNUINT32 size)
{
	/*	return malloc(size);*/
	ASNVoid *ret = NULL;
	struct mpool_blob *p;
	ASNUINT32 F_UI_remain,i;
	ASNUINT64 F_UI_tempsize;
	static int count_use = 0;
	if (size == 0) 
	{	/* This is legal under ANSI C, so we should allow it too */
		size = 1;
	}
	size = size + 8;

	p = pool->blob;
	memcpy(p, pool->blob, sizeof(struct mpool_blob));

//	printf("%d pool->blob.base address:%16X \n",count_use++,&pool->blob->base);
//	printf("%d p->ptr address:%16X \n",count_use++,&p->ptr);

	/* This is a bit tricky, not only do we have to make sure that the current
	* pool has enough room, we need to be sure that we haven't rounded p->ptr
	* outside of the current pool anyway */

	F_UI_remain = p->size - ((ASNINT8 *)p->ptr - (ASNINT8 *)p->base);

	if (F_UI_remain < size || (ASNINT8 *)p->ptr > (p->size + (ASNINT8 *)p->base)) 
	{  	/* Need a new pool */
		struct mpool_blob *new_pool;
		ASNUINT32 new_pool_size = 2 * ((size > p->size) ? size : p->size);

		new_pool = new_mpool_blob(new_pool_size);
		//		printf("new_pool\n\n");
		new_pool->next = p;
		p = pool->blob = new_pool;
	}

	F_UI_tempsize = size - 8;
	for(i = 0; i < 8; i++)
	{	// save memory length
		*p->ptr = (ASNUINT8)(F_UI_tempsize & 0xFF);
		p->ptr++;
		F_UI_tempsize = F_UI_tempsize >> 8;
	}

//	printf("%d pool->blob.base address:%16X \n",count_use++,&pool->blob->base);
//	printf("%d p->ptr address:%16X \n",count_use++,&p->ptr);
	ret = (ASNVoid *)p->ptr;
	p->ptr++;
	/* make sure that the next thing we allocate is align on a ROUNDUP boundary */
//	printf("\n\nsize = %d\n\n",size);
//	printf("%d after p->ptr address:%16X \n",count_use++,&p->ptr);
//	printf("%d after p->base address:%16X \n",count_use++,&p->base);
	//p->ptr += (ASNUINT64)5;
	//p->ptr = NULL;
	p->ptr = p->base + (((p->ptr - p->base + size - 8) + 15) / 16 * 16);
//	printf("%d befor p->ptr address:%16X \n",count_use++,&p->ptr);
//	printf("%d befor p->base address:%16X \n",count_use++,&p->base);
//	printf("\nsize_process = %d\n",((size-4+15)/16*16));

	return ret;
}

ASNVoid *mpool_calloc(struct mpool *pool, ASNUINT32 unit_size, ASNUINT32 unit_cnt)
{
	ASNUINT32 byte_size = unit_size * unit_size;
	ASNUINT32 clr_size = byte_size == 0 ? 1 : byte_size;
	ASNVoid *ret = mpool_malloc(pool, clr_size);
	if (ret != NULL) memset(ret, 0, clr_size);
	return ret;
}

/********************************************************************************/
/* Description: Allocate from a pool for string                          		*/
/* Input:                                                                       */
/*       pool:the pool that be allocate                                         */ 
/*       str:character string                                                   */		                                                      
/* Output: none                                                                 */
/* Return: none                 									        	*/
/********************************************************************************/
ASNINT8* mpool_strdup(struct mpool *pool, const ASNINT8 *str)
{
    ASNINT8 *ret;
    ASNUINT32 len;

    if(!str) return NULL;

    len = (ASNINT32)strlen(str);

    ret = mpool_malloc(pool, len+1);
    strcpy(ret, str);

    return ret;
}

/********************************************************************************/
/* Description: Realloc from a pool                                  			*/
/* Input:                                                                       */
/*       pool:the pool that be realloc                                          */ 
/*       memblock:old address                                                   */
/*       size:the size of memory that will be realloc from the pool             */                                             		                                                      
/* Output: none                                                                 */
/* Return: none                 									        	*/
/********************************************************************************/
ASNVoid* mpool_realloc( struct mpool *pool,ASNVoid *memblock, ASNUINT32 size )
{

// 	return realloc(memblock,size);
	ASNINT8 *ret;
	ASNUINT64 F_UI_LenOfMemory = 0 ;
	ASNINT32 i;
	/* get memory length */
	for (i = 1; i <= 8; i++)
	{
//		F_UI_LenOfMemory =(F_UI_LenOfMemory <<= 8) & 0xFFFFFF00;
//		F_UI_LenOfMemory = F_UI_LenOfMemory | *((char*)memblock-i);

		F_UI_LenOfMemory <<= 8;
		F_UI_LenOfMemory += *((unsigned char*)memblock - i);
	}

	ret = mpool_malloc(pool, size);
	memcpy(ret, memblock, (ASNUINT32)F_UI_LenOfMemory);
	
	return ret;
}


/********************************************************************************/
/* Description: Realloc from a pool for buf and set buf's pointers              */                   			
/* Input:                                                                       */
/*       pool:the pool that be realloc                                          */ 
/*       membuf:old address                                                     */
/*       size:the size of memory that will be realloc from the pool             */                                             		                                                      
/* Output: none                                                                 */
/* Return: none                 									        	*/
/********************************************************************************/
ASNVoid *mpool_bufrealloc( struct mpool *pool,ASN1_Buffer *membuf, ASNUINT32 size )
{
	
	ASNUINT32 F_UI_datalenth;
	F_UI_datalenth = membuf->current - membuf->data;

	membuf->data = mpool_realloc(pool, membuf,size);
	membuf->head = membuf->data;
	membuf->current = membuf->head + F_UI_datalenth;
	membuf->end = membuf->head + size;
	
	return membuf->data;
}

