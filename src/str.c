
# include	<stdlib.h>
# include	<string.h>
# include	<stdio.h>

# include	"constant.h"
# include	"str.h"

typedef	char	elt_t;
int	str_grow (STR* sp, size_t newsize) {
	int	result	= err;
	size_t	oldsize	= sp->size;

	if (newsize > oldsize) {
		elt_t*	news	= realloc (sp->elts, newsize*sizeof(news[0]));
		if (news) {
			memset (&news[oldsize], 0, (newsize - oldsize)*sizeof(news[0]));
			sp->elts	= news;
			sp->size	= newsize;
			result	= ok;
		}
	}
	else	result	= ok;

	return	result;
}
int	str_Create (STR** spp, size_t size) {
	int	result	= err;
	STR*	s	= calloc (sizeof(*s),1);
	if (s) {
		s->elts	= 0;
		s->last	= 0;
		s->size	= 0;
		result	= str_grow (s, size);
		if (result == ok) {
			*spp	= s;
		}
		else {
			free (s);
		}
	}
	return	result;
}
int	str_Delete (STR** spp) {
	if (spp && *spp) {
		if ((*spp)->elts) {
			free ((*spp)->elts);
			(*spp)->elts 	= 0;
			*spp	= 0;
		}
	}
	return	ok;
}
int	str_clear (STR* sp) {
	sp->last	= 0;
	sp->elts[0]	= '\0';
	return	ok;
}	

int	str_fgetline (FILE* input, STR* line) {
	int	result	= err;
	int	ch	= EOF;
	size_t	last	= 0;
	size_t	size	= line->size;
	char*	l	= line->elts;
	while ((ch = fgetc (input)) != EOF && (ch != '\n')) {
		if ((last+1) >= size) { // ensure space for \0
			str_grow (line, 2*size);
			size	= line->size;
			l	= line->elts; // oops: forgot this
		}
		l[last++]	= ch;
	}	
	l[last]	= '\0';
	line->last	= last;
	if (ch==EOF)
		result	= 0;
	return	result;
}
