#ifndef extern_
#define extern_ extern

#endif

extern_ int r8;
extern_ int r9;
extern_ int r10;
extern_ int r11;
extern_ int Line;
extern_ int Putback;
extern_ FILE *Infile;
extern_ FILE *Outfile;
extern_ struct token Token;
extern_ char Text[TEXTLEN + 1];
extern_ struct symtable Gsym[NSYMBOLS];	