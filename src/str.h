# if	!defined( STR_H)
# define	STR_H	1

# include	<stdio.h>

struct	string	{
	size_t	size;
	size_t	last;
	char*	elts;
};
typedef	struct	string STR;

int	str_Create (STR** spp, size_t size);
int	str_Delete (STR** spp);
int	str_clear (STR* sp);
int	str_grow (STR* sp, size_t newsize);
static	inline	size_t	str_length (STR* sp) { return sp->last; };
static	inline	char*	str_asciz (STR* sp)  { return sp->elts; };

int	str_fgetline (FILE* input, STR* line);

# endif
