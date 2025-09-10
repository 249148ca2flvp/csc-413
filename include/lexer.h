#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "source_reader.h"

typedef struct Lexer Lexer;

// Constructor/Destructor
Lexer* lexer_create(const char* sourceFile);
void lexer_destroy(Lexer* lexer);

// Core functionality
Token* lexer_nextToken(Lexer* lexer);
bool lexer_atEOF(Lexer* lexer);

// Token creation helpers
Token* lexer_newIdToken(Lexer* lexer, const char* id, int start, int end);
Token* lexer_newNumberToken(Lexer* lexer, const char* number, int start, int end);
Token* lexer_makeToken(Lexer* lexer, const char* s, int start, int end);

#endif
