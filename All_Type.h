#ifndef ALL_H
#define ALL_H

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LINE 1000

typedef struct
{
    char token[100];
    char lexeme[100];
    struct Line_data *link;

}Line_data;
 
typedef struct
{
    char contents[300];
    Line_data *Head ;

}LINE;

typedef struct
{
    LINE lines[MAX_LINE];
    unsigned int Line_Count;
    char Input_fname[20] ;
    FILE *fptr ;

}Process_Line ;


#endif