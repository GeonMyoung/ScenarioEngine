#ifndef DZ1_FIFO_H
#define DZ1_FIFO_H

#include <dz1_error.h>

typedef void Dz1Fifo;

typedef struct Dz1FifoFindArg
{
	Dz1CmpFunc		 cmp;
	void			*b;
	void			*ret;
} Dz1FifoFindArg;


///////////////////////////////////////////////////////////////////////////////
// Dz1Fifo
/*
 * Dz1Fifo_new : create Dz1Fifo structure
 *
 * @del : user data delete function
 * @dump : user data dump function
 * @size : fifo size (== 0 -> Dynamic size FIFO, > 0 -> Static sized FIFO, < 0 -> Static sized FIFO(auto delete)
 * @err : Address of Dz1Error structure
 *
 * return : Address of Dz1Fifo Structure
 *
 * NOTE :
 *   size == 0 -> Dynamic size FIFO
 *   size > 0 -> Static sized FIFO
 *               When fifo is full, Dz1Fifo_push will return ENOMEM
 *   size < 0 -> Static sized FIFO
 *               When fifo is full, Dz1Fifo_push will return SUCCESS and First Entry will deleted
 */
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1Fifo_new(Dz1DelFunc del, Dz1DumpFunc dump, int size, Dz1Error *err);
#define							 Dz1Fifo_newDynamic(del, dump, errp)		Dz1Fifo_new(del, dump, 0, errp)

/*
 * Dz1Fifo_del : Delete Dz1Fifo structure
 *
 * @p : Address of Dz1Fifo
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Fifo_empty(void *p);
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Fifo_del(void *p);
static __inline__ void			 Dz1Fifo_delAndSetNull(void *ptr)
{
	void **p = (void **)ptr;
	Dz1Fifo_del(*p); *p = NULL;
}

/*
 * Dz1Fifo_dump : Dump Dz1Fifo to target console
 *
 * @ptr : Address of Dz1Fifo
 * @tab : indent level
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1Fifo_dump(void *ptr, int tab);

/*
 * Dz1Fifo_push : Push user data to target FIFO
 *
 * @ptr : target FIFO
 * @data : user data to push
 *
 * return : Dz1Error Structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Fifo_push(void *ptr, void *data);

/*
 * Dz1Fifo_pop : Pop user data from target FIFO
 *
 * @ptr : target FIFO
 * @err : Address of Dz1Error structure
 *
 * return : user data
 */
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1Fifo_pop(void *ptr, Dz1Error *err);

/*
 * Dz1Fifo_remove: Remove user data from target FIFO
 *
 * @ptr : target FIFO
 * @removeptr : user data pointer be removed
 *
 */
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1Fifo_remove(void *ptr, void *removeptr);
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1Fifo_extract(void *ptr, void *removeptr);

typedef Dz1Error (*Dz1FifoTravelFunc)(void *param, void *data);
typedef int (*Dz1FifoTravelFunc2)(void *param, void *data, Dz1Error *errp);
/*
 * Dz1Fifo_travel : Push user data to target FIFO
 *
 * @ptr : target FIFO
 * @func : function for each entries
 * @param : function parameter
 *
 * return : Dz1Error Structure
 */
#define							 Dz1Fifo_travel Dz1Fifo_travelForward
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Fifo_travelForward(void *ptr, Dz1FifoTravelFunc func, void *param);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1Fifo_travelBackward(void *ptr, Dz1FifoTravelFunc func, void *param);

#define							 Dz1Fifo_travel2 Dz1Fifo_travelForward2
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1Fifo_travelForward2(void *ptr, Dz1FifoTravelFunc2 func, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1Fifo_travelBackward2(void *ptr, Dz1FifoTravelFunc2 func, void *param, Dz1Error *err);

/*
 * Dz1Fifo_isEmpty : Check target fifo is empty
 *
 * @ptr : target FIFO
 *
 * return : boolean value
 */
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1Fifo_isEmpty(void *ptr);

/*
 * Dz1Fifo_isFull : Check target fifo is Full
 *
 * @ptr : target FIFO
 *
 * return : boolean value
 */
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1Fifo_isFull(void *ptr);

/*
 * Dz1Fifo_count : get number of entries from target FIFO
 *
 * @ptr : target FIFO
 *
 * return : number of entries
 */
DZ1_CPPLINK DZ1_DLLPORT u32_t	 Dz1Fifo_count(void *ptr);

// Popping First
#define							 Dz1Fifo_getHead	Dz1Fifo_getFirst
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1Fifo_getFirst(void *ptr);

// Popping Last
#define							 Dz1Fifo_getTail	Dz1Fifo_getLast
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1Fifo_getLast(void *ptr);
// Dz1Fifo
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1FifoCursor
typedef enum
{
	Dz1FifoCursorPos_head,
	Dz1FifoCursorPos_tail,
	Dz1FifoCursorPos_max
} Dz1FifoCursorPos;

#define							 Dz1FifoCursor_new(fifo, errp)		_Dz1FifoCursor_new(fifo, errp, __FILE__, __LINE__)
DZ1_CPPLINK DZ1_DLLPORT void   *_Dz1FifoCursor_new(void *fifo, Dz1Error *err, const char *file, int line);

DZ1_CPPLINK DZ1_DLLPORT void	 Dz1FifoCursor_del(void *cursor);
static __inline__ void			 Dz1FifoCursor_delAndSetNull(void *pptr)
{
	void **p = (void **)pptr;
	Dz1FifoCursor_del(*p); *p = NULL;
}

/*
 * Dz1FifoCursor_Init : Initialize FIFO Cursor that contain target FIFO
 *
 * @p : target Cursor
 * @fifo : source FIFO
 * @pos : Initialization Position
 *
 * return : Dz1Error Structure
 */
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1FifoCursor_init(void *cursor, void *fifo, Dz1FifoCursorPos pos);

/*
 * Dz1FifoCursor_Cond : Check FIFO Cursor that contain target FIFO is valid
 *
 * @p : target FIFO
 *
 * return : boolean value
 */
DZ1_CPPLINK DZ1_DLLPORT bool_t	 Dz1FifoCursor_cond(void *cursor);

/*
 * Dz1FifoCursor_Next : FIFO Cursor move to Next Entry
 *
 * @p : target FIFO
 * @notNull : behavior flag
 *            if this is value is TRUE and next entry is NULL
 *            then cursor isn't move to next entry
 */
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1FifoCursor_next(void *cursor, bool_t notNull);

/*
 * Dz1FifoCursor_IsFirst : Check Cursor Position is First
 *
 * @p : target FIFO
 *
 * return : TRUE or FALSE
 */
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1FifoCursor_isFirst(void *cursor);

/*
 * Dz1FifoCursor_IsLast : Check Cursor Position is First
 *
 * @p : target FIFO
 *
 * return : TRUE or FALSE
 */
DZ1_CPPLINK DZ1_DLLPORT int		 Dz1FifoCursor_isLast(void *cursor);

/*
 * Dz1FifoCursor_Prev : FIFO Cursor move to Previous Entry
 *
 * @p : target FIFO
 * @notNull : behavior flag
 *            if this is value is TRUE and previous entry is NULL
 *            then cursor isn't move to previous entry
 */
DZ1_CPPLINK DZ1_DLLPORT void	 Dz1FifoCursor_prev(void *cursor, bool_t notNull);

/*
 * Dz1FifoCursor_Data : retrieve user data from current cursor position
 *
 * @p : target FIFO
 *
 * return : user data or NULL
 *
 */
DZ1_CPPLINK DZ1_DLLPORT void	*Dz1FifoCursor_data(void *cursor);

#define							 Dz1FifoCursorForward(curcorp) \
									Dz1FifoCursor_init((curcorp), NULL, Dz1FifoCursorPos_head); \
									Dz1FifoCursor_cond((curcorp)); \
									Dz1FifoCursor_next((curcorp), FALSE)

#define							 Dz1FifoCursorBackward(curcorp) \
									Dz1FifoCursor_init((curcorp), NULL, Dz1FifoCursorPos_tail); \
									Dz1FifoCursor_cond((curcorp)); \
									Dz1FifoCursor_prev((curcorp), FALSE)
// Dz1FifoCursor
///////////////////////////////////////////////////////////////////////////////

#endif
