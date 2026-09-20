#ifndef LEXI_H
#define LEXI_H

extern const char *token[] ;
extern const char *keywords[] ;

Status implement_lexical(Process_Line *Line_Info);
Status Open_files(Process_Line *Line_Info);
Token_type preprocessor_token(Process_Line *Line_Info,char *str);
void Allocate_node(Process_Line *Line_Info,Line_data **temp);
void print_lexical(Process_Line *Line_Info);

#endif