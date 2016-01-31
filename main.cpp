#include <string>

#include "vlog_lexer.h"
#include "stream.h"

using namespace HWToy;

std::string test_string = "    module always alwaysid begin//with a comment\n"
    " /* and a block comment\n"
    "   that has multiple lines\n"
    " with a tricksy * / not quite finished line // in the middle\n"
    "  see look at them */\n"
    "assign write is a thing output\n"
    "ass ing or or or\n"
    "assign thing = testing [ a ] ;";

int main(void) {
    BasicCharStream stream(test_string);
    VLogLexer lexer(stream);

    lexer.do_things();

    return 0;
}

