# if	!defined( FIELD_H)
# define	FIELD_H
# include	<stdlib.h>
# include	<limits.h>
/* FORWARD */ typedef	struct	fieldlist FIELDLIST;

typedef	struct	field	FIELD;

typedef	unsigned short	fieldnr_t;
struct	field	{
	unsigned char	reversed:1;
	fieldnr_t	low;
	fieldnr_t	high;
};


int	parse_fieldlist (FIELDLIST* fl, char fieldspec[]);
# endif

