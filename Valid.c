#include "All_Type.h"
#include "Flags.h"
#include "Valid.h"

Status Validate_Input_File(int input_count,char *input[],Process_Line *Line_Info)
{
     if(input_count < 2)
     {
        printf(RED"\nInsufficient Number Of Arguments...!\n"RESET);
        return FAILED ;
     } 
     else if(input_count > 2)
     {
        printf(RED"\nToo Many Arguments...!\n"RESET);
        return FAILED ;
     }

     if(input[1][0] == '.')
     {
        printf(RED"\nInvalid Extention...!\n"RESET);
        return FAILED;
     }

     char *extn = strrchr(input[1],'.');

     if(!extn)
     {
         printf(RED"\nThe Input File Does Not Contain .c Extention...!\n"RESET);
         return FAILED ;
     }

     if(strcmp(extn,".c") != 0)
     {
        printf(RED"\nInvalid File Type...Only Supports .c extn Source File...!\n"RESET);
        return FAILED ;
     }

     Line_Info->fptr = fopen(input[1],"r");

     if(!Line_Info->fptr)
     {
        printf(RED"\nCan't Open File...please check %s Exist In Your Directory...!\n"RESET,input[1]);
        return FAILED ;
     }

     fclose(Line_Info->fptr);

     strcpy(Line_Info->Input_fname,input[1]);

     printf(GREEN"\nInput File %s is valid\n",Line_Info->Input_fname);

     return SUCCESS ;

}
