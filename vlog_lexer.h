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
    uint32_t current_line;
    uint32_t line_char;

    bool is_whitespace_char(char c);
protected:
    char current_char;

    // Get the next character (current_char is being taken as part of current
    // token).  Returns True if whitespace found (current_char will be set to
    // next non-whitespace character and should not be used as part of current
    // token).
    bool consume_char();
    void emit_token(const TokenType& token);
public:
    VLogLexer(Stream<char>& input);

    bool next_token();
};

struct TokenErr {
    char* msg;
    uint32_t line;
    uint32_t line_char;

    TokenErr(char* m, uint32_t l, uint32_t lc) : msg(m), line(l), line_char(lc) {}
}

};

#endif __VLOG_LEXER_H__

