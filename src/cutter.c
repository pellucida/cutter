/*
//	@(#) cutter.c - produce a cut like subset of a file in any order
//
//	License: Creative Commons CC0 
//		http://creativecommons.org/publicdomain/zero/1.0/legalcode
//	Author:	James Sainsbury
//		toves@sdf.lonestar.org
//
*/
# include	<stdio.h>
# include	<string.h>
# include	<stdlib.h>
# include	<unistd.h>

# include	"constant.h"
# include	"field.h"
# include	"fieldlist.h"
# include	"strlist.h"
# include	"str.h"

void	process_line (FILE* output, int outdel, int silent, FIELDLIST* flds,  STRLIST* cflds);
int	process_file (FILE* input, FILE* output, char* indel, int outdel, int silent, FIELDLIST* flds);
int	process_fields (STR* line, char* delimiter, STRLIST* cflds);

enum	{
	MAXFIELDS	= 1024,
	MAXLINE		= 4096,

};

static	char*	progname	= "cutter";

static	void	Usage (void) {
	fprintf (stderr, "Usage %s [-s] [-d delim] [-O del] -f fields files ...\n",
			progname);
	exit (EXIT_FAILURE);
}


int	main (int argc, char* argv[]) {
	int	opt	= EOF;
	int	d_flag	= 0;
	int	f_flag	= 0;
	int	O_flag	= 0;
	int	s_flag	= 0;
	char*	indel	= "\t";
	int	outdel	= '\t';

	char*	fieldstr	= 0;
	FILE*	input	= stdin;
	FILE*	output	= stdout;
	FIELDLIST*	flds	= 0;

	progname	= argv[0];

	while ((opt = getopt (argc, argv, "sO:d:f:"))!=EOF) {
		switch (opt) {
		case	's':
			if (s_flag++)
				Usage ();
		break;
		case	'd':
			if (d_flag++)
				Usage ();
			indel		= optarg;
		break;
		case	'f':
			if (f_flag++)
				Usage ();
			fieldstr		= optarg;
		break;
		case	'O':
			if (O_flag++)
				Usage ();
			outdel	= optarg [0];
		break;
		default:
			Usage ();
		break;
		}
	}
	if (!O_flag)
		outdel	= indel [0];

	if (fieldlist_Create(&flds, MAXFIELDS) == ok) {
		parse_fieldlist (flds, fieldstr);
	}
	else	{
		exit (EXIT_FAILURE);
	}

	if (optind < argc) {
		int	i	= optind;
		for (i=optind; i< argc; ++i) {
			char*	file	= argv[i];
			input	= fopen (file, "r");
			if (input) {
				process_file (input, output, indel, outdel, s_flag, flds);
				fclose (input);
			}
			else	{
				fprintf (stderr, "ERROR -- can't open '%s'\n", file);
			}
		}
	}
	else	{
		process_file (input, output, indel,outdel, s_flag, flds);
	}
	exit (EXIT_SUCCESS);
	
}
/*
*/
void process_line (FILE* output, int outdel, int silent, FIELDLIST* flds,  STRLIST* cflds) {

	int	nfields	= fieldlist_count (flds);
	int	ncflds	= strlist_count (cflds)-1;  // Number of fields in line
	int	i	= 0;
	int	nprinted	= 0;
	if (!silent && (strlist_count(cflds)==1)) { // _count == 1 => no delimiters
		char*	s	= 0;
		strlist_get (cflds, 0, &s);	
		fprintf (output, "%s\n", s);
	}
	else for (i=0; i < nfields; ++i) {
		char*	s	= 0;
		int	j	= 0;
		FIELD	f	= flds->elts[i];
		if (f.low <= ncflds) { 
			int	start	= f.low;
			int	finish	= f.high;
			int	step	= 1;
			if (finish > ncflds) {
				finish	= ncflds;
			}
			if (f.reversed) {
				int	tmp	= start;
				start	= finish;
				finish	= tmp;
				step	= -1;
			}
			for (j=start; j != finish; j += step) {
				strlist_get (cflds, j, &s);	
				fprintf (output, "%s%c", s, outdel);
				++nprinted;
			}
			strlist_get (cflds, finish, &s);
			fprintf (output, "%s", s);
			++nprinted;
		}
		if (nprinted) {
			if ((i+1) == nfields) { // last field
				fputc ('\n', output);
			}	
			else {
				fputc (outdel, output);
			}
		}
	}
}

int	process_file (FILE* input, FILE* output, char* indel, int outdel, int silent, FIELDLIST* flds) {
	STR*	line	= 0;
	STRLIST*	cflds	= 0;
	int	result	= str_Create (&line, MAXLINE);
	if (result==ok) {
		result	= strlist_Create (&cflds, MAXFIELDS); 
	}
	if (result==ok) while (str_fgetline (input, line)!= 0) {
		process_fields (line, indel, cflds);
		process_line (output, outdel, silent, flds, cflds);
		str_clear (line);
	}
	strlist_Delete (&cflds);
	str_Delete (&line);
	return	result;
}

/*
// HACK: [0] always contains the line
// A line with delimiters the _count always > 1
// ie  [1] field_1 et seq
// A line without delimiters will have _count == 1
*/
int	process_fields (STR* line, char* delimiter, STRLIST* cflds) {
	int	result	= ok;
	char*	s	= str_asciz (line);
	char*	t	= strpbrk (s, delimiter);
	strlist_clear(cflds);
	result	= strlist_append (cflds, s);
	while (t!=0 && result==ok) {
                result  = strlist_append (cflds, s);
                t       = strpbrk (s, delimiter);
                if (t) {
                        *t      = '\0';
                        s       = t+1;
                }
        }

	return	result;
}
