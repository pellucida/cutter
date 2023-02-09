# include	<stdlib.h>
# include	<string.h>

# include	"constant.h"
# include	"field.h"
# include	"fieldlist.h"

typedef	struct	field	elt_t;

int	fieldlist_grow (FIELDLIST* ip, size_t newsize) {
	int	result	= err;
	size_t	oldsize	= ip->size;

	if (newsize > oldsize) {
		elt_t*	news	= realloc (ip->elts, newsize*sizeof(news[0]));
		if (news) {
			memset (&news [oldsize], 0, (newsize - oldsize)*sizeof(news[0])) ;
			ip->elts	= news;
			ip->size	= newsize;
			result	= ok;
		}
	}
	else	result	= ok;

	return	result;
}
int	fieldlist_Create (FIELDLIST** ipp, size_t size) {
	int	result	= err;
	FIELDLIST*	s	= calloc (sizeof(*s),1);
	if (s) {
		s->elts	= 0;
		s->last	= 0;
		s->size	= 0;
		result	= fieldlist_grow (s, size);
		if (result == ok) {
			*ipp	= s;
		}
		else {
			free (s);
		}
	}
	return	result;
}
int	fieldlist_append (FIELDLIST* ip, elt_t n) {
	int	result	= ok;
	if (ip->last >= ip->size) {
		result	= fieldlist_grow (ip, ip->size*2);
		if (result == ok) {
			result	= fieldlist_append (ip, n);
		}
	}
	else	{
		ip->elts[ip->last++]	= n;
	}
	return	result;
}
