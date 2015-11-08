#ifdef  __VLOG_LEXER_H__
#define __VLOG_LEXER_H__

#include <stdint.h>

#include "stream.h"

namespace HWToy {

enum TokenType {
    TOKEN_MODULE,
    TOKEN_ENDMODULE,
    TOKEN_INPUT,
    TOKEN_OUTPUT,
    TOKEN_LOGIC,
    TOKEN_WIRE,
    TOKEN_ASSIGN
    TOKEN_BEGIN,
    TOKEN_END,
    TOKEN_ALWAYS,
    TOKEN_POSEDGE,
    TOKEN_NEGEDGE,
    TOKEN_OR,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_AT,

    TOKEN_LBRACKET,
    TOKEN_RBRACKT,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_GTEQ,
    TOKEN_LTEQ,
    TOKEN_GT,
    TOKEN_LT,
    TOKEN_EQ,
    TOKEN_COMMA,

    TOKEN_ID,
    TOKEN_NUM,
    TOKEN_BASENUM
};

struct Token {
    TokenType type;
    uint32_t  start;
    uint32_t  end;
    uint32_t  line;

    Token(TokenType t, uint32_t s, uint32_t e, uint32_t l) : type(t), start(s), end(e), line(l) {}
};

class VLogLexer {
private:
    Stream<char> input_stream;

    uint32_t start_pos;
    uint32_t current_pos;
    uint32_t line;
protected:
    char current_char;

    void consume_char();
    void emit_token(const TokenType& token);
public:
    VLogLexer(Stream<char>& input);

    bool next_token();
};

};

#endif __VLOG_LEXER_H__

