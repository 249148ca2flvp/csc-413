#ifndef TOKEN_H
#define TOKEN_H

// Forward declaration to avoid circular dependency
typedef struct Symbol Symbol;

// Token types enumeration
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_INTEGER,
    TOKEN_OPERATOR,
    TOKEN_SEPARATOR,
    TOKEN_KEYWORD,
    TOKEN_COMMENT,
    TOKEN_EOF,
    TOKEN_BOGUS
} TokenType;

// Token structure
typedef struct Token {
    int leftPosition;
    int rightPosition;
    Symbol* symbol;
} Token;

// Constructor/Destructor
Token* token_create(int leftPos, int rightPos, Symbol* sym);
void token_destroy(Token* token);

// Accessors
int token_getLeftPosition(Token* token);
int token_getRightPosition(Token* token);
TokenType token_getKind(Token* token);
const char* token_toString(Token* token);
Symbol* token_getSymbol(Token* token);

// Utility
void token_print(Token* token);
const char* token_typeToString(TokenType type);

#endif
