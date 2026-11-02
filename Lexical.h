#ifndef LEXI_H
#define LEXI_H

extern const char *tokens[] ;
extern const char *key[] ;
extern const char *assgn_op[] ;
extern const char arith[] ;
extern const char *rational_op[] ;
extern const char *logical[];
extern const char special[] ;

Status implement_lexical(Process_Line *Line_Info);
Status Open_files(Process_Line *Line_Info);
void preprocessor_token(Process_Line *Line_Info,char *token);
void Allocate_node(Process_Line *Line_Info,Line_data **temp);
void print_lexical(Process_Line *Line_Info);
void tokanize_line(Process_Line *Line_Info,char *token);
int check_key(char buffer[]);
int is_operator(char buffer[],Process_Line *Line_Info);

#endif