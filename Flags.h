#ifndef FLAG_H
#define FLAG_H

typedef enum 
{
    FAILED = 0,
    SUCCESS

}Status;

typedef enum 
{
    KEYWORD = 0,    // Reserved C words  - int, char, if, while, return etc
    IDENTIFIER ,    // Variable/function/user-defined names - main, count, total_sum
    INTEGER ,       // Integer numbers - 10, 25, 1000
    FLOAT ,         // Floating-point numbers - 3.14, 10.5
    CHAR_CONSTANT , // Character literals - 'A', '\n'
    STRING_LITERAL, // String literals - "Hello"
    OPERATOR ,      // Arithmetic, relational, logical, assignment etc. - +, -, =, ==, ++, &&
    SPECIAL_SYMBOL, // Separators/delimiters - (, ), {, }, [, ], ;, ,
    PREPROCESSOR ,  // Preprocessor directives - #include, #define
    COMMENT ,       // /* or // 
    ERROR  ,        // Invalid lexical elements
    HEADER          // eg : <stdio.h> 
    
}Token_type ;

#define RED    "\033[1;31m"
#define YELLOW "\033[33m"
#define GREEN  "\033[1;32m"
#define RESET  "\033[0m"

#endif
