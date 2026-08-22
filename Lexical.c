#include "All_Type.h"
#include "Flags.h"
#include "Lexical.h"

const char *token[] = {"KEYWORD","IDENTIFIER","INTEGER","FLOAT","CHAR_CONSTANT","STRING_LITERAL","OPERATOR","SPECIAL_SYMBOL","PREPROCESSOR","COMMENT","ERROR","HEADER",NULL};

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
        
        Line_Info->lines[Line_Info->Line_Count].Head = NULL ;

        unsigned int length = strlen(Line_Info->lines[Line_Info->Line_Count].contents) ;

        Line_Info->lines[Line_Info->Line_Count].contents[length-1] = '\0' ;
        
        char *line_string = Line_Info->lines[Line_Info->Line_Count].contents ;
 
        if(line_string[0] == '#')
        {
            if(preprocessor_token(Line_Info,line_string))
            {
                printf("Preprocessor directive examined...!\n");
            }
        }
        else
        {
            break ;
        }
        
        Line_Info->Line_Count++; 
     }

     return SUCCESS ;

}

Token_type preprocessor_token(Process_Line *Line_Info,char *str)
{
    int i = strlen(str) , p = 0 , n = 0;
    
    char buffer[100];

    Line_data *node ; 

    Allocate_node(Line_Info,&node);
    
    while(p<i)
    {
        if(str[p]!=' '&& str[p]!='<')
        {
           buffer[n++] = str[p++] ;
        }
        else
        {
            buffer[n] = '\0';
            strcpy(node->token,buffer);
            strcpy(node->lexeme,token[PREPROCESSOR]);
            n = 0;
            buffer[n++] = str[p++];
        }

    }
    
    Allocate_node(Line_Info,&node);
    buffer[n] = '\0';
    strcpy(node->token,buffer);
    strcpy(node->lexeme,token[HEADER]);
    
    return SUCCESS ;
    
}

void Allocate_node(Process_Line *Line_Info,Line_data **temp)
{
    if(Line_Info->lines[Line_Info->Line_Count].Head == NULL)
    {
        *temp = malloc(sizeof(Line_data));
        Line_Info->lines[Line_Info->Line_Count].Head = *temp ;
        (*temp)->link = NULL ;
    }
    else
    {
        *temp = Line_Info->lines[Line_Info->Line_Count].Head ;

        while((*temp)->link != NULL)
        {
            *temp = (*temp)->link ;
        }

        (*temp)->link = malloc(sizeof(Line_data)) ;
        *temp = (*temp)->link ;
        (*temp)->link = NULL ;

    }
}

void print_lexical(Process_Line *Line_Info)
{
    printf("\n+----------+-------------------------+--------------------------------------------+\n");
    printf("| Line No. | Token                     | Lexeme                                   |\n");
    printf("+----------+---------------------------+------------------------------------------+\n");

    Line_data *ptr ;

     for(int i = 0 ; i < Line_Info->Line_Count ; i++)
     {
         if(Line_Info->lines[i].Head == NULL)
         {
             continue ;
         }

         ptr = Line_Info->lines[i].Head ;

         while(ptr!=NULL)
         {
            printf("| %-8d | %-25s | %-40s |\n",(i+1),ptr->token,ptr->lexeme);
            ptr = ptr->link ;
         }
     }

    printf("+----------+---------------------------+------------------------------------------+\n");


}
