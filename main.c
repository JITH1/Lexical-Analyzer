#include "All_Type.h"
#include "Flags.h"
#include "Valid.h"
#include "Lexical.h"


int main(int input_count,char *input[])
{
    Process_Line Line_Info ;

    if(Validate_Input_File(input_count,input,&Line_Info))
    {
        printf(GREEN"\nFile Validation Successfull...!\n"RESET);

        if(implement_lexical(&Line_Info))
        {
           printf(GREEN"\nLexical Analysis Completed...!\n"RESET);
        }
        else
        {
            printf(RED"\nLexical Implementation Failed...!\n\n"RESET);
            return FAILED ;
        }

        return SUCCESS ;
    }
    else
    {
        printf(RED"\nFile Validation Failed...!\n"RESET);
        return FAILED ; 
    }

    return 0 ;
}