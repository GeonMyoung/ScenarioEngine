#ifndef DZ1_GIF_TYPES_H
#define DZ1_GIF_TYPES_H

#include <dz1_error.h>

struct Dz1GifColor;
struct Dz1GifColorList;
typedef struct Dz1GifColorIndex
{
	u32_t				 numOfColor;
	struct Dz1GifColor	*colors[256];
} Dz1GifColorIndex;

#define							 Dz1GifColorIndex_new(listp, errp) _Dz1GifColorIndex_new((listp), (errp), __FILE__, __LINE__)
DZ1_CPPLINK Dz1GifColorIndex   *_Dz1GifColorIndex_new(struct Dz1GifColorList *src, Dz1Error *err, char *__file__, int __line__);
DZ1_CPPLINK Dz1GifColorIndex	*Dz1GifColorIndex_clone(Dz1GifColorIndex *src, Dz1Error *err);
DZ1_CPPLINK void				 Dz1GifColorIndex_del(Dz1GifColorIndex *p);
static __inline__ void			 Dz1GifColorIndex_delAndSetNull(void *pptr)
{
	Dz1GifColorIndex **p = (Dz1GifColorIndex **)pptr;
	Dz1GifColorIndex_del(*p); *p = NULL;
}

#endif