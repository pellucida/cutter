# if	!defined( FIELDLIST_H)
# define	FIELDLIST_H
# include	<stdlib.h>
# include	"field.h"


typedef	struct	fieldlist	FIELDLIST;
struct	fieldlist {
	size_t	size;
	size_t	last;
	FIELD*	elts;
};

static	inline	int	fieldlist_count (FIELDLIST* fl) {
	return	fl->last;
}
int	fieldlist_Create (FIELDLIST** ipp, size_t size);
int	fieldlist_append (FIELDLIST* ip, FIELD n);

#endif
