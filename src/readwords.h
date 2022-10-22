#ifndef READWORDS_H
#define READWORDS_H

#define TOKEN " \n\t\r\a"
#define BUFFER_SIZE 65536
#define LIN 2999
#define COL 15

extern void readWord(char **);
extern int getIndex(void);
extern char *getWord(char **);

#endif
