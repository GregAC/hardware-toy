#ifndef  __VLOG_LEXER_H__
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
    TOKEN_ASSIGN,
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
    TOKEN_RBRACKET,
    TOKEN_LSQBRACKET,
    TOKEN_RSQBRACKET,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_GTEQ,
    TOKEN_LTEQ,
    TOKEN_GT,
    TOKEN_LT,
    TOKEN_EQ,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,

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

struct TokenMapping {
    TokenType   type;
    const char* str;
};

class VLogLexer {
private:
    enum ConsumeCharState {
        CONSUME_IDLE,
        CONSUME_BEGUN_COMMENT,
        CONSUME_BLOCK_COMMENT,
        CONSUME_LINE_COMMENT,
        CONSUME_FINISHING_BLOCK_COMMENT,
        CONSUME_FINISHING_BLOCK_COMMENT2
    };

    enum LexerState {
        LEX_KWID,
        LEX_NON_KWID,
        LEX_GT,
        LEX_LT,
        LEX_NUM
    };

    Stream<char>& input_stream;

    char token_buffer[256];

    uint32_t   token_buf_pos;
    uint32_t   current_pos;
    uint32_t   current_line;
    uint32_t   line_char;
    LexerState lex_state;

    char current_char;
    bool eof;

    bool is_whitespace_char(char c);
    bool is_kwid_char(char c);

    static TokenMapping token_mapping_table[];
    static unsigned int num_token_mappings;

    bool* live_token_mappings;

    // Get the next character (current_char is being taken as part of current
    // token).  Returns True if whitespace found (current_char will be set to
    // next non-whitespace character and should not be used as part of current
    // token).
    bool consume_char();
    void emit_token(const TokenType& token);
public:
    VLogLexer(Stream<char>& input);

    bool next_token();
    void do_things();
};

struct TokenErr {
    char* msg;
    uint32_t line;
    uint32_t line_char;

    TokenErr(char* m, uint32_t l, uint32_t lc) : msg(m), line(l), line_char(lc) {}
};

};

#endif //__VLOG_LEXER_H__

