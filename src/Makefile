

STROBJ=fieldlist.o field.o strlist.o str.o
OBJ=cutter.o

PROG=cutter
CFLAGS=-g -Wall
LDFLAGS=-g
$(PROG): $(OBJ) $(STROBJ) 
	$(CC) -o $(PROG) $(OBJ) $(STROBJ)


fieldlist.o:	fieldlist.c fieldlist.h field.h
field.o:	field.c fieldlist.h field.h
strlist.o:	strlist.c strlist.h
str.o:	str.c str.h
cutter.o:	cutter.c fieldlist.h field.h strlist.h str.h

clean:	
	rm -f $(OBJ) $(STROBJ)
