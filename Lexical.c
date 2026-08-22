#include "All_Type.h"
#include "Flags.h"
#include "Lexical.h"

const char *token[] = {"KEYWORD","IDENTIFIER","INTEGER","FLOAT","CHAR_CONSTANT","STRING_LITERAL","OPERATOR","SPECIAL_SYMBOL","PREPROCESSOR","COMMENT","ERROR",NULL};

const char *keywords[] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","inline","int","long","register","restrict","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while","_Bool","_Complex","_Imaginary",NULL};



Status implement_lexical(Process_Line *Line_Info)
{
     Line_Info->fptr = fopen(Line_Info->Input_fname,"r");

     if(!Line_Info->fptr)
     {
         printf(RED"\nCan't open file %s please check your directory...!\n"RESET,Line_Info->Input_fname);
         return FAILED ; 
     }

     Line_Info->Line_Count = 0 ;

     LINE S_t ;

     size_t n = sizeof(S_t.contents);

     while(fgets(Line_Info->lines[Line_Info->Line_Count].contents,n,Line_Info->fptr) != NULL) 
     {
        if(Line_Info->lines[Line_Info->Line_Count].contents[0] == '\n')
        {
            Line_Info->lines[Line_Info->Line_Count].Head = NULL ;
            Line_Info->Line_Count++;
            continue ;
        }

        unsigned int length = strlen(Line_Info->lines[Line_Info->Line_Count].contents) ;

        Line_Info->lines[Line_Info->Line_Count].contents[length] = '\0' ;
        
        char *line_string = Line_Info->lines[Line_Info->Line_Count].contents ;
 
        if(line_string[0] == '#')
        {
            preprocessor_token(Line_Info,line_string);
        }

     }
     
     return SUCCESS ;

}

Token_type preprocessor_token(Process_Line *Line_Info,char *str)
{
    int i = 0 , n = 0;
    
    char buffer[100];

    while(str[i]!='\0')
    {
        if(str[i]!=' ' || str[i]!='<')
        {
           buffer[n++] = str[i] ;
        }

        i++;
    }

    
    
    return PREPROCESSOR ;
}

