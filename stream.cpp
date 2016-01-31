#include "stream.h"

namespace HWToy {

BasicCharStream::BasicCharStream(const std::string& str) : stream_str(str), stream_pos(0) {}

char BasicCharStream::get() {
    if(stream_pos == stream_str.length())
        throw StreamEOF();

    return stream_str[stream_pos++];
}

char BasicCharStream::peek() {
    if(stream_pos == stream_str.length())
        throw StreamEOF();
   
    return stream_str[stream_pos];
}

bool BasicCharStream::is_eof() {
    return stream_pos == stream_str.length();
}

};

