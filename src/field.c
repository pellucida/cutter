
# include	<limits.h>
# include	<string.h>
# include	<stdlib.h>

# include	"constant.h"
# include	"field.h"
# include	"fieldlist.h"

enum	{
	FLDNO_MIN	= 1,
	FLDNO_MAX	= USHRT_MAX,
};
typedef	unsigned short	fieldnr_t;

/*
//	parse field specifications of form: n,k-m,l-,-q
//	eg 1,3-7,9-2,7-,-2
//	where
//		3-7 == 3,4,5,6,7
//		7-3 == 7,6,5,4,3   (reversed)
//		7-  == 7,8,9....   (until last field)
//		-7  == ....9,8,7   (from last field)
//		-   == 1-
//	single fields ,n, are implemented as ,n-n, 
*/
int	parse_fieldlist (FIELDLIST* fieldlist, char fieldspec[]) {
	int	result	= ok;
	char*	t	= fieldspec;
	char*	p	= 0;

	while ((p = strsep (&t, ","))!= 0 && result==ok) {
		FIELD	fld	=  { .reversed = false, .low = FLDNO_MIN, .high = FLDNO_MAX }; // ...,-,... = all
		char*	s	= strchr (p, '-');
		if (s) {
			*s	= '\0';
			if (p!=s) {	// ...,n-m,...
				fld.low	= atoi (p);
			} 
			else	fld.low	= 0;
			if (s[1] != '\0') {	// ...,n-m,...
				fld.high	= atoi (s+1);
			} 
			if (fld.low == 0) {
				fld.low	= FLDNO_MAX;
				if (fld.high == FLDNO_MAX)
					fld.high	= FLDNO_MIN;
			}	
			if (fld.low > fld.high) {
				fieldnr_t tmp	= fld.low;
				fld.low	= fld.high;
				fld.high	= tmp;
				fld.reversed	= true;
			}
		}
		else	{	// ...,n,...
			fld.low	= atoi (p);
			fld.high = fld.low;
		}
		result	= fieldlist_append (fieldlist, fld);
	}
	return	result;
}
