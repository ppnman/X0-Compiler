#include "global.h"

char fileName[MAX_SIZE_FILENAME + 1];     /* file name */

/* 
 * variables used in lexical analysis 
 */
struct BackUp backups[MAX_SIZE_BACKUP];   /* backups of lexical analysing's status */
int iterBackUp = 0;                       /* iterator of backups */
FILE* fin;                                /* input file */
enum symbol sym;                          /* current terminal symbol read by readSymbol() */
char ch = ' ';                            /* current character read by getCh() */
int posCh;								  /* counter using by getCh() */
char lineCache[MAX_SIZE_LINE];            /* line cache using by getCh() */
int chNum;								  /* counter using by line cache */
double doubleNum;                         /* current floating number */
int intNum;                               /* current number */
char id[MAX_SIZE_IDENT + 1];              /* current identifier */

/* reserved word */
char* reserveWord[RESERVE_WORD_NUM] = { "bool", "break", "case", "char", "const", "continue", "default",
										"do", "double", "else", "exit", "false", "for", 
										"if", "int", "main", "odd", "read", "repeat", 
										"switch", "true", "until", "while", "write", "xor" };

/* symbol-value corresponding to reserved word */
enum symbol wsym[RESERVE_WORD_NUM] = { bolsym, brksym, cassym, charsym, cstsym, ctnsym, defausym,
									   dosym, dblsym, elsesym, exitsym, falsesym, forsym,
									   ifsym, intsym, mainsym, oddsym, readsym, reptsym, 
									   swtcsym, truesym, untlsym, whilesym, writesym, xorsym };

/* symbol-value of single character */
enum symbol ssym[256] = { ['+'] = plus, ['-'] = minus, ['*'] = times,
						  ['/'] = slash, ['('] = lparen, [')'] = rparen,
						  ['['] = lbracket, [']'] = rbracket, ['{'] = lbrace,
						  ['}'] = rbrace, [';'] = semic, ['%'] = modsym, [':'] = colonsym };

/* 
 * variables used in syntactical analysis 
 */
int continueList[MAX_SIZE_CONTINUE];      /* continue statement to be backfilled */
int iterCtnList = 0;                      /* the iterator of continueList */
int breakList[MAX_SIZE_BREAK];            /* break statement to be backfilled */
int iterBreakList = 0;                    /* the iterator of breakList */
struct instruction code[MAX_SIZE_CODE];   /* intermidiate code */
int iterCode = 0;                         /* the iterator of code */
struct tableObject table[MAX_SIZE_TABLE]; /* symbol table */
int iterTable = 0;                        /* the iterator of table */
int expressionNum;                        /* store the value of 'expression' in 'expressionNum'
										   * if 'expression' is a number */

/* strings corresponding to function code */
char* fctCode_string[FCTCODE_NUM] = { "lit", "opr", "lod", "lod2", "lod3", "sto", "sto2", "sto3",
									  "cal", "ini", "jmp", "jpc", "add", "add2", "add3", "tad" };