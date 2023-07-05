# if	!defined( STRLIST_H)
# define	STRLIST_H	1

# include	<stdlib.h>
# include	"constant.h"

struct	strlist	{
	size_t	size;
	size_t	last;	/* largest index used */
	char**	elts;
};
typedef	struct	strlist	STRLIST;

int	strlist_Create(STRLIST** ipp, size_t size);
int	strlist_Delete(STRLIST** ipp);

static	inline	size_t	strlist_count (STRLIST* il) {
	return	il->last;
}
static	inline	int	strlist_get (STRLIST* il, size_t i, char** eltp) {
	int	result	= err;
	if (i < il->last) {
		*eltp	= il->elts[i];
		result	= ok;
	}
	return	result;
}

int	strlist_append (STRLIST* il, char* n);

static	inline	void	strlist_clear(STRLIST* il) {
	il->last	= 0;
}
# endif
