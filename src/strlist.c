
# include	<stdlib.h>
# include	<string.h>
# include	"constant.h"
# include	"strlist.h"

typedef	char*	elt_t;

int	strlist_grow (STRLIST* ip, size_t newsize) {
	int	result	= err;
	size_t	oldsize	= ip->size;

	if (newsize > oldsize) {
		elt_t*	news	= realloc (ip->elts, newsize*sizeof(news[0]));
		if (news) {
			memset (&news [oldsize], 0, (newsize - oldsize)*sizeof(news[0]));
			ip->elts	= news;
			ip->size	= newsize;
			result	= ok;
		}
	}
	else	result	= ok;

	return	result;
}
int	strlist_Create (STRLIST** ipp, size_t size) {
	int	result	= err;
	STRLIST*	s	= calloc (sizeof(*s),1);
	if (s) {
		s->elts	= 0;
		s->last	= 0;
		s->size	= 0;
		result	= strlist_grow (s, size);
		if (result == ok) {
			*ipp	= s;
		}
		else {
			free (s);
		}
	}
	return	result;
}
int	strlist_append (STRLIST* ip, char* n) {
	int	result	= ok;
	if (ip->last >= ip->size) {
		result	= strlist_grow (ip, ip->size*2);
		if (result == ok) {
			result	= strlist_append (ip, n);
		}
	}
	else	{
		ip->elts[ip->last++]	= n;
	}
	return	result;
}
int	strlist_Delete (STRLIST** ipp) {
	if (ipp && (*ipp)) {
		if ((*ipp)->elts) {
			free ((*ipp)->elts);
			(*ipp)->elts	= 0;
			*ipp	= 0;
		}
	}
	return	ok;
}
