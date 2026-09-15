

#ifndef _MPOOL_H_

#define _MPOOL_H_


//#include <signal.h>

#include "ASN1_xmalloc.h"
/************************************************************************/
/* mpool struct                                                         */
/************************************************************************/
struct mpool
{
    struct mpool_blob *blob;
};

/************************************************************************/
/* mpool_blob struct                                                         */
/************************************************************************/
struct mpool_blob
{
    ASNUINT32 size;
    ASNUINT8 *base; /* Base of allocated section */
    ASNUINT8 *ptr; /* End of allocated section */
    struct mpool_blob *next; /* Next Pool */
};
#define DEFAULT_MPOOL_SIZE 32768
/********************************************************************************/
/* Description: Create a new pool -- pass zero for default              		*/
/* Input:                                                                      */
/*       size:the size of the first blob of memory that will be allocated		*/
/* Output: none                                                                 */
/* Return: address of the new pool									        	*/
/********************************************************************************/
ASN1_CPPLINK struct mpool *new_mpool(ASNUINT32 size);

/********************************************************************************/
/* Description: Free a pool              		                              	*/
/* Input:                                                                       */
/*       pool: the new pool		                                                */
/* Output: none                                                                 */
/* Return: none                 									        	*/
/********************************************************************************/
ASN1_CPPLINK ASNVoid free_mpool(struct mpool *pool);

/********************************************************************************/
/* Description: Allocate from a pool                                			*/
/* Input:                                                                       */
/*       pool:the pool that be allocate                                         */ 
/*       size:the size of memory that will be allocated from the pool           */		                                                      
/* Output: none                                                                 */
/* Return: none                 									        	*/
/********************************************************************************/
ASN1_CPPLINK ASNVoid *mpool_malloc(struct mpool *pool, ASNUINT32 size);
ASN1_CPPLINK ASNVoid *mpool_calloc(struct mpool *pool, ASNUINT32 unit_size, ASNUINT32 unit_cnt);

/********************************************************************************/
/* Description: Allocate from a pool for string                          		*/
/* Input:                                                                       */
/*       pool:the pool that be allocate                                         */ 
/*       str:character string                                                   */		                                                      
/* Output: none                                                                 */
/* Return: none                 									        	*/
/********************************************************************************/
ASN1_CPPLINK ASNINT8 *mpool_strdup(struct mpool *pool, const ASNINT8 *str);

/********************************************************************************/
/* Description: Realloc from a pool                                  			*/
/* Input:                                                                       */
/*       pool:the pool that be realloc                                          */ 
/*       memblock:old address                                                   */
/*       size:the size of memory that will be realloc from the pool             */                                             		                                                      
/* Output: none                                                                 */
/* Return: none                 									        	*/
/********************************************************************************/
ASN1_CPPLINK ASNVoid *mpool_realloc( struct mpool *pool,ASNVoid *memblock, ASNUINT32 size );

/********************************************************************************/
/* Description: Realloc from a pool for buf and set buf's pointers              */                   			
/* Input:                                                                       */
/*       pool:the pool that be realloc                                          */ 
/*       membuf:old address                                                     */
/*       size:the size of memory that will be realloc from the pool             */                                             		                                                      
/* Output: none                                                                 */
/* Return: none                 									        	*/
/********************************************************************************/
ASN1_CPPLINK ASNVoid *mpool_bufrealloc( struct mpool *pool,ASN1_Buffer *membuf, ASNUINT32 size );


#endif /* _MPOOL_H_ */


