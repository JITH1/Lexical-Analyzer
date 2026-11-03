#include "All_Type.h"

const char *tokens[] = {"KEYWORD","IDENTIFIER","INTEGER","FLOAT","CHAR_CONSTANT","STRING_LITERAL","OPERATOR","SPECIAL_SYMBOL","PREPROCESSOR","COMMENT","ERROR","HEADER",NULL};

const char *key[] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","inline","int","long","register","restrict","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while","_Bool","_Complex","_Imaginary",NULL};

const char *assgn_op[] = {"+=","-=","*=","/=","%=","<<=","&=",">>=","^=","~=","|=",NULL};

const char arith[] = "+/%*-";

const char *rational_op[] = {"<=",">=","==","!=",NULL};

const char *logical[] = {"&&","||",NULL};

const char special[] = "(){}[];:,";

void preprocessor_token(Process_Line *Line_Info,char *token)
{
    char buffer[100];
    int i = 0 , j = 0;

    Line_data *temp ;
    Allocate_node(Line_Info,&temp);

    while((token[i] != '\0') && (token[i] != ' '))
    {
        if(token[i] != '<')
        buffer[j++] = token[i++];
        else if(token[i] == '<')
        break;
    }

    buffer[j] = '\0';

    strcpy(temp->token,tokens[PREPROCESSOR]);
    strcpy(temp->lexeme,buffer);

    if(token[i] == '\0')
    {
        return;
    }

    if(token[i] == ' ')
    {
        while(token[i] == ' ' && token[i] != '\0')
        {
            i++;
        }

    }

    Allocate_node(Line_Info,&temp);

    if(token[i] == '\0')
    {
        strcpy(temp->token,tokens[ERROR]);
        strcpy(temp->lexeme,buffer);
        return;
    }

    j = 0;
    
    if(token[i] == '<')
    {
        Allocate_node(Line_Info,&temp);

        while(token[i] != '>' && token[i] != '\0')
        {
            buffer[j++] = token[i++];
        }

        if(token[i] == '>')
        {
            buffer[j++] = token[i++];
            buffer[j] = '\0';

            strcpy(temp->token,tokens[HEADER]);
            strcpy(temp->lexeme,buffer);
        }
        else
        {
            buffer[j] = '\0';
            strcpy(temp->token,tokens[ERROR]);
            strcpy(temp->lexeme,buffer);
            return;
        }
    }

    tokanize_line(Line_Info,token+i);
}

void tokanize_line(Process_Line *Line_Info,char *token)
{
    char buffer[100];
    int i = 0 , j = 0;

    while(token[i] != '\0')
    {

        if(token[i] == ' ')
        {
            i++;
            continue;
        }

        if(strchr(special,token[i]))
        {
            buffer[j++] = token[i];
            buffer[j] = '\0';

            Line_data *temp ;
            Allocate_node(Line_Info,&temp);

            strcpy(temp->token,tokens[SPECIAL_SYMBOL]);
            strcpy(temp->lexeme,buffer);

            j = 0;
            i++;
            continue;
        }

        if((isalpha(token[i]) || token[i] == '_'))
        {
            while(isalnum(token[i]) || token[i] == '_')
            {
                buffer[j++] = token[i++];
            }

            buffer[j] = '\0';

            Line_data *temp ;
            Allocate_node(Line_Info,&temp);

            if(check_key(buffer))
            {
                strcpy(temp->token,tokens[KEYWORD]);
                strcpy(temp->lexeme,buffer);
            }
            else 
            {
                strcpy(temp->token,tokens[IDENTIFIER]);
                strcpy(temp->lexeme,buffer);
            }

            j = 0;
    
            continue;
              
        }

        if(isdigit(token[i]))
        {
            while(isdigit(token[i]) || token[i] == '.')
            {
                buffer[j++] = token[i++];
            }

            buffer[j] = '\0';

            Line_data *temp ;
            Allocate_node(Line_Info,&temp);

            if(strchr(buffer,'.'))
            {
                strcpy(temp->token,tokens[FLOAT]);
                strcpy(temp->lexeme,buffer);
            }
            else
            {
                strcpy(temp->token,tokens[INTEGER]);
                strcpy(temp->lexeme,buffer); 
            }

            j = 0;
         //   i++;      // Check if must increment ? 
            continue;
        }

        int m = 0 ;

        if((m = is_operator(token+i,Line_Info)) != 0)
        {
            i+=m;
            continue;
        }

        if(token[i] == '"')
        {
            
            i++;
            
            Line_data *temp ;
            Allocate_node(Line_Info,&temp);

            while((token[i]!='\0') && (token[i]!= '"'))
            {
                buffer[j++] = token[i++];
            }

            if(token[i] == '"')
            {
                strcpy(temp->token,tokens[STRING_LITERAL]);
                strcpy(temp->lexeme,buffer);
            }
            else
            {
                strcpy(temp->token,tokens[ERROR]);
                strcpy(temp->lexeme,buffer);
            }

            j = 0;

            if(token[i] == '\0')
            {
                continue;
            }

            i++;
            continue;
        }

        if(token[i] == '\'')
        {
         
            int closed = 0;

            j = 0;
            buffer[j++] = token[i++];                          // opening quote

            while(token[i] != '\0' && token[i] != '\'' && j < (int)sizeof(buffer) - 3)
            { 
                if(token[i] == '\\' && token[i+1] != '\0')     // escape: take backslash and next char together
                {
                   buffer[j++] = token[i++];
                }

                buffer[j++] = token[i++];
            }

            if(token[i] == '\'')                               // closing quote
            {
                buffer[j++] = token[i++];
                closed = 1;
            }

            buffer[j] = '\0';

            // valid forms: 'A' (len 3) or '\n', '\\', '\'', '\0', '\x41' (len >= 4 and starts with backslash)
            int valid = closed && ((buffer[1] != '\\' && j == 3) || (buffer[1] == '\\' && j >= 4));

            Line_data *temp;
            Allocate_node(Line_Info,&temp);
            strcpy(temp->token, valid ? tokens[CHAR_CONSTANT] : tokens[ERROR]);
            strcpy(temp->lexeme,buffer);

            j = 0;
            continue;

        }

        i++;
    }

}

int check_key(char buffer[])
{
    int i = 0;

    while(key[i] != NULL)
    {
        if(strcmp(key[i],buffer) == 0)
        {
            return 1;
        }

        i++;
    }

    return 0;
}

int is_operator(char buffer[],Process_Line *Line_Info)
{

    char token[30];

    if(strchr(arith,buffer[0]))   // Arithmatic operator
    {
        int i = 0 , j = 0 ;

        Line_data *temp ;
        Allocate_node(Line_Info,&temp);

        if(buffer[0] == '+')
        {
            token[j++] = buffer[i++];

            if(buffer[i] == '+')
            {
                token[j++] = buffer[i++];
                token[j] = '\0';

                strcpy(temp->token,tokens[OPERATOR]);
                strcpy(temp->lexeme,token);

                return j;
            }
            else if(buffer[i] == '=')
            {
                token[j++] = buffer[i++];
                token[j] = '\0';

                strcpy(temp->token,tokens[OPERATOR]);
                strcpy(temp->lexeme,token);

                return j;
            }

            token[j] = '\0';
            
            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);

            return j;
            
        }
        else if(buffer[0] == '-')
        {
            token[j++] = buffer[i++];

            if(buffer[i] == '-')
            {
                token[j++] = buffer[i++];
                token[j] = '\0';

                strcpy(temp->token,tokens[OPERATOR]);
                strcpy(temp->lexeme,token);

                return j;
            }
            else if(buffer[i] == '=')
            {
                token[j++] = buffer[i++];
                token[j] = '\0';

                strcpy(temp->token,tokens[OPERATOR]);
                strcpy(temp->lexeme,token);

                return j;
            }

            token[j] = '\0';

            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);

            return j;

        }
        else if(buffer[0] == '/')
        {
            token[j++] = buffer[i++];

            if(buffer[i] == '=')
            {
                token[j++] = buffer[i++];
                token[j] = '\0';

                strcpy(temp->token,tokens[OPERATOR]);
                strcpy(temp->lexeme,token);

                return j;
            }
            else if(buffer[i] == '/')
            {
                while(buffer[i] != '\0')
                {
                    token[j++] = buffer[i++];
                } 

                token[j] = '\0';

                strcpy(temp->token,tokens[COMMENT]);
                strcpy(temp->lexeme,token);

                return j;
            }

            token[j] = '\0';

            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);

            return j;

        }
        else if(buffer[0] == '%')
        {
            token[j++] = buffer[i++];

            if(buffer[i] == '=')
            {
                token[j++] = buffer[i++];
                token[j] = '\0';

                strcpy(temp->token,tokens[OPERATOR]);
                strcpy(temp->lexeme,token);

                return j;
            }

            token[j] = '\0';

            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);

            return j;
        }
        else if(buffer[0] == '*')
        {
            token[j++] = buffer[i++];

            if(buffer[i] == '=')
            {
                token[j++] = buffer[i++];
                token[j] = '\0';

                strcpy(temp->token,tokens[OPERATOR]);
                strcpy(temp->lexeme,token);

                return j;
            }

            token[j] = '\0';

            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);

            return j;
        }

    }
    else if(buffer[0] == '>' || buffer[0] == '<')
    {
        int i = 0 , j = 0;

        Line_data *temp ;
        Allocate_node(Line_Info,&temp);

        token[j++] = buffer[i++]; 

        if(buffer[i] == buffer[i-1])
        {
           token[j++] = buffer[i++];

           if(buffer[i] == '=')
           {
              token[j++] = buffer[i++];
              token[j] = '\0';
              strcpy(temp->token,tokens[OPERATOR]); // Rational Op
              strcpy(temp->lexeme,token);

              return j;
           }

           token[j] = '\0';

           strcpy(temp->token,tokens[OPERATOR]); // Bitwise Op
           strcpy(temp->lexeme,token);
           return j;
        }
        else if(buffer[i] == '=')
        {
            token[j++] = buffer[i++];
            token[j] = '\0';
            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);           // Assignment Op

            return j;
        }

        token[j] = '\0';

        strcpy(temp->token,tokens[OPERATOR]);
        strcpy(temp->lexeme,token);            // Rational Op

        return j;

    }
    else if(buffer[0] == '&' || buffer[0] == '|')
    {
        int i = 0 , j = 0;

        Line_data *temp ;
        Allocate_node(Line_Info,&temp);

        token[j++] = buffer[i++];

        if(buffer[i] == buffer[i-1])
        {
            token[j++] = buffer[i++];
            token[j] = '\0';
            
            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);           // logical Op

            return j;
        }
        else if(buffer[i] == '=')
        {
            token[j++] = buffer[i++];
            token[j] = '\0';
            
            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);           // Assignment Op

            return j;
        }

        token[j] = '\0';

        strcpy(temp->token,tokens[OPERATOR]);
        strcpy(temp->lexeme,token);              // Bitwise Op

        return j;
    }
    else if(buffer[0] == '^' || buffer[0] == '~')
    {
        int i = 0 , j = 0 ;

        Line_data *temp ;
        Allocate_node(Line_Info,&temp);

        token[j++] = buffer[i++];

        if(buffer[i] == '=')
        {
            token[j++] = buffer[i++];
            token[j] = '\0';
            
            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);          

            return j;
        }

        token[j] = '\0';

        strcpy(temp->token,tokens[OPERATOR]);
        strcpy(temp->lexeme,token);             // Bitwise Operator 

        return j;
    }
    else if(buffer[0] == '!')
    {
        int  i = 0 , j = 0 ;
         
        Line_data *temp ;
        Allocate_node(Line_Info,&temp);

        token[j++] = buffer[i++];
        
        if(buffer[i] == '=')
        {
            token[j++] = buffer[i++];
            token[j] = '\0';
            
            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);            // Rational Op 

            return j;
        }

        token[j] = '\0';

        strcpy(temp->token,tokens[OPERATOR]);
        strcpy(temp->lexeme,token);   // Bitwise Operator 

        return j;

    }
    else if(buffer[0] == '=')
    {
        int i = 0 , j = 0;

        Line_data *temp ;
        Allocate_node(Line_Info,&temp);

        token[j++] = buffer[i++];

        if(buffer[i] == '=')
        {
            token[j++] = buffer[i++];
            token[j] = '\0';

            strcpy(temp->token,tokens[OPERATOR]);
            strcpy(temp->lexeme,token);   // Assignment Operator 

            return j;
        }

        token[j] = '\0';

        strcpy(temp->token,tokens[OPERATOR]);
        strcpy(temp->lexeme,token);      // Assignment Operator 

        return j;   

    }

    return 0;     

}