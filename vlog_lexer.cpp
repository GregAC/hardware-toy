#include <iostream>

#include "vlog_lexer.h"

namespace HWToy {

TokenMapping VLogLexer::token_mapping_table[] = {
    {TOKEN_MODULE, "module"},
    {TOKEN_ENDMODULE, "endmodule"},
    {TOKEN_INPUT, "input"},
    {TOKEN_OUTPUT, "output"},
    {TOKEN_LOGIC, "logic"},
    {TOKEN_WIRE, "wire"},
    {TOKEN_ASSIGN, "assign"},
    {TOKEN_BEGIN, "begin"},
    {TOKEN_END, "end"},
    {TOKEN_ALWAYS, "always"},
    {TOKEN_POSEDGE, "posedge"},
    {TOKEN_NEGEDGE, "negedge"},
    {TOKEN_OR, "or"},
    {TOKEN_IF, "if"},
    {TOKEN_ELSE, "else"},
    {TOKEN_FOR, "for"}
};

unsigned int VLogLexer::num_token_mappings = sizeof(VLogLexer::token_mapping_table) / sizeof(TokenMapping);

VLogLexer::VLogLexer(Stream<char>& input) : input_stream(input), token_buf_pos(0), current_pos(0), current_line(0), line_char(0), eof(false) {
    live_token_mappings = new bool[num_token_mappings];

    for(int i = 0; i < num_token_mappings; ++i) {
        live_token_mappings[i] = true;
    }
}

bool VLogLexer::is_whitespace_char(char c) {
    return (c == '\n') || (c == ' ') || (c == '\t');
}

bool VLogLexer::is_kwid_char(char c) {
    if((c >= 'a') && (c <= 'z'))
        return true;
    if((c >= 'A') && (c <= 'Z'))
        return true;
    if((c >= '0') && (c <= '9'))
        return true;
    if((c == '-') || (c == '_'))
        return true;

    return false;
}

bool VLogLexer::consume_char() {
    bool             found_whitespace  = false;
    ConsumeCharState state             = CONSUME_IDLE;
    char             next_char;

    do {

        if(input_stream.is_eof()) {
            eof = true;

            switch(state) {
                case CONSUME_BLOCK_COMMENT: 
                    throw TokenErr("Unterminated block comment at end of file", line_char, current_line);
                case CONSUME_BEGUN_COMMENT:
                    throw TokenErr("Unexpected EOF", line_char, current_line);
            }

            return true;
        }

        next_char = input_stream.peek();

        switch(state) {
            case CONSUME_IDLE:
                if(next_char == '/') {
                    state = CONSUME_BEGUN_COMMENT;
                } else if(next_char == '\n') {
                    current_line++;
                    line_char = 0;
                }

                break;
            case CONSUME_BEGUN_COMMENT:
                if(next_char == '/') {
                    state = CONSUME_LINE_COMMENT;
                    found_whitespace = true;
                } else if(next_char == '*') {
                    state = CONSUME_BLOCK_COMMENT;
                    found_whitespace = true;
                } else {
                    return found_whitespace;
                }

                break;
            case CONSUME_BLOCK_COMMENT:
                if(next_char == '*') {
                    state = CONSUME_FINISHING_BLOCK_COMMENT;
                }

                break;
            case CONSUME_FINISHING_BLOCK_COMMENT:
                if(next_char == '/') {
                    state = CONSUME_FINISHING_BLOCK_COMMENT2;
                    break;
                }
                
                state = CONSUME_BLOCK_COMMENT;
    
                break;
            case CONSUME_FINISHING_BLOCK_COMMENT2:
                state = CONSUME_IDLE;
                break;
            case CONSUME_LINE_COMMENT:
                if(next_char  == '\n') {
                    state     = CONSUME_IDLE;
                    line_char = 0;

                    current_line++;
                }
                break;
        }

        current_char = input_stream.get();
        current_pos++;
        line_char++;

        if(is_whitespace_char(current_char))
            found_whitespace = true;

    } while (is_whitespace_char(current_char) || (state != CONSUME_IDLE));
        
    return found_whitespace;
}

void VLogLexer::emit_token(const TokenType& token) {
    token_buffer[token_buf_pos] = 0;

    switch (token) {
        case TOKEN_MODULE:
            std::cout << "TOKEN_MODULE\n";
            break;
        case TOKEN_ENDMODULE:
            std::cout << "TOKEN_ENDMODULE\n";
            break;
        case TOKEN_INPUT:
            std::cout << "TOKEN_INPUT\n";
            break;
        case TOKEN_OUTPUT:
            std::cout << "TOKEN_OUTPUT\n";
            break;
        case TOKEN_LOGIC:
            std::cout << "TOKEN_LOGIC\n";
            break;
        case TOKEN_WIRE:
            std::cout << "TOKEN_WIRE\n";
            break;
        case TOKEN_ASSIGN:
            std::cout << "TOKEN_ASSIGN\n";
            break;
        case TOKEN_BEGIN:
            std::cout << "TOKEN_BEGIN\n";
            break;
        case TOKEN_END:
            std::cout << "TOKEN_END\n";
            break;
        case TOKEN_ALWAYS:
            std::cout << "TOKEN_ALWAYS\n";
            break;
        case TOKEN_POSEDGE:
            std::cout << "TOKEN_POSEDGE\n";
            break;
        case TOKEN_NEGEDGE:
            std::cout << "TOKEN_NEGEDGE\n";
            break;
        case TOKEN_OR:
            std::cout << "TOKEN_OR\n";
            break;
        case TOKEN_IF:
            std::cout << "TOKEN_IF\n";
            break;
        case TOKEN_ELSE:
            std::cout << "TOKEN_ELSE\n";
            break;
        case TOKEN_FOR:
            std::cout << "TOKEN_FOR\n";
            break;
        case TOKEN_AT:
            std::cout << "TOKEN_AT\n";
            break;
        case TOKEN_LBRACKET:
            std::cout << "TOKEN_LBRACKET\n";
            break;
        case TOKEN_RBRACKET:
            std::cout << "TOKEN_RBRACKET\n";
            break;
        case TOKEN_LSQBRACKET:
            std::cout << "TOKEN_LSQBRACKET\n";
            break;
        case TOKEN_RSQBRACKET:
            std::cout << "TOKEN_RSQBRACKET\n";
            break;
        case TOKEN_LBRACE:
            std::cout << "TOKEN_LBRACE\n";
            break;
        case TOKEN_RBRACE:
            std::cout << "TOKEN_RBRACE\n";
            break;
        case TOKEN_GTEQ:
            std::cout << "TOKEN_GTEQ\n";
            break;
        case TOKEN_LTEQ:
            std::cout << "TOKEN_LTEQ\n";
            break;
        case TOKEN_GT:
            std::cout << "TOKEN_GT\n";
            break;
        case TOKEN_LT:
            std::cout << "TOKEN_LT\n";
            break;
        case TOKEN_EQ:
            std::cout << "TOKEN_EQ\n";
            break;
        case TOKEN_COMMA:
            std::cout << "TOKEN_COMMA\n";
            break;
        case TOKEN_SEMICOLON:
            std::cout << "TOKEN_SEMICOLON\n";
            break;
        case TOKEN_ID:
            std::cout << "TOKEN_ID(" << token_buffer << ")\n";
            break;
        case TOKEN_NUM:
            std::cout << "TOKEN_NUM\n";
            break;
        case TOKEN_BASENUM:
            std::cout << "TOKEN_BASENUM\n";
            break;
    }

    token_buf_pos = 0;
    
    for(int i = 0; i < num_token_mappings; ++i) {
        live_token_mappings[i] = true;
    }
}

bool VLogLexer::next_token() {
    bool         whitespace;
    bool         kwid_char;
    bool         seen_match;
    unsigned int current_match;

    while(true) {
        switch(lex_state) {
            case LEX_KWID:
                seen_match = false;

                for(int i = 0;i < num_token_mappings; ++i) {
                    if(live_token_mappings[i]) {
                        char token_char = token_mapping_table[i].str[token_buf_pos];

                        if(current_char == token_char) {
                            if(token_mapping_table[i].str[token_buf_pos + 1] == 0) {
                                seen_match    = true;
                                current_match = i;
                            }
                        } else {
                            live_token_mappings[i] = false;
                        }
                    }
                }
                break;
            case LEX_NON_KWID:
                switch(current_char) {
                    case '@': 
                        emit_token(TOKEN_AT);
                        break;
                    case '(':
                        emit_token(TOKEN_LBRACKET);
                        break;
                    case ')':
                        emit_token(TOKEN_RBRACKET);
                        break;
                    case '[':
                        emit_token(TOKEN_LSQBRACKET);
                        break;
                    case ']':
                        emit_token(TOKEN_RSQBRACKET);
                        break;
                    case '{':
                        emit_token(TOKEN_LBRACE);
                        break;
                    case '}':
                        emit_token(TOKEN_RBRACE);
                        break;
                    case '>':
                        lex_state = LEX_GT;
                        break;
                    case '<':
                        lex_state = LEX_LT;
                        break;
                    case ',':
                        emit_token(TOKEN_COMMA);
                        break;
                    case ';':
                        emit_token(TOKEN_SEMICOLON);
                        break;
                    case '=':
                        emit_token(TOKEN_EQ);
                        break;
                    default:
                        throw TokenErr("Unexpected character", line_char, current_line);
                        break;
                }
                break;
        }

        if(lex_state == LEX_KWID) {
            token_buffer[token_buf_pos] = current_char;
            token_buf_pos++;
        }

        whitespace = consume_char();
        kwid_char  = is_kwid_char(current_char);

        if(lex_state == LEX_KWID) {
            if(whitespace || !kwid_char) {
                if(seen_match) {
                    emit_token(token_mapping_table[current_match].type);
                } else {
                    emit_token(TOKEN_ID);
                }
                
                lex_state = kwid_char ? LEX_KWID : LEX_NON_KWID;

                return !eof;
            }
        } else {
            lex_state = kwid_char ? LEX_KWID : LEX_NON_KWID;

            return  !eof;
        }

    }
}

void VLogLexer::do_things() {
    consume_char();
    lex_state = is_kwid_char(current_char) ? LEX_KWID : LEX_NON_KWID;

    if(eof)
        return;

    while(next_token());
}

};
