#include "vlog_lexer.h"

namespace HWToy {

bool VLogLexer::is_whitespace_char(char c) {
    return (c == '\n') || (c == ' ') || (c == '\t');
}

bool VLogLexer::consume_char() {
    bool found_whitespace        = false;
    bool in_block_comment        = false;
    bool in_line_comment         = false;
    bool begun_comment           = false;
    bool finishing_block_comment = false;

    do {
        if(input_strean.is_eof()) {
            if(in_block_comment)
                throw TokenErr(line_char, current_line, "Unterminated block comment at end of file");

            if(begun_comment)
                throw TokenErr(line_char, current_line, "Unexpected EOF");

            return true;
        }
        
        current_pos++;
        line_char++;
        current_char = input_stream.get();

        if(begun_comment) {
            found_whitespace = true;

            if(current_char == '/') {
                in_line_comment = true;
                begun_comment   = false;
            } else if(current_char == '*') {
                in_block_comment        = true;
                finishing_block_comment = false;
                begun_comment           = false;
            } else {
                throw TokenErr(line_char, current_line, "Unexpected character");
            }
        } else if(in_block_comment) {
            if((current_char == '*') && !finishing_block_comment) {
                finishing_block_comment = true;
            } else if((current_char == '/' && finishing_block_comment) {
                in_block_comment = false;
                continue;
            } else if(finishing_block_comment) {
                finishing_block_comment = false;
            }
        }

        else if(current_char == '/') {
            begun_comment = true;
        }

        if(current_char == '\n') {
            current_line++;
            line_char       = 0;
            in_line_comment = false;
        } 

        if(is_whitespace_char(current_char))
            found_whitespace = true;

    } while (is_whitespace_char(current_char) || in_block_comment || in_line_comment);
        
    return found_whitespace;
}

};
