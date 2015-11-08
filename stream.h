#ifdef  __STREAM_H__
#define __STREAM_H__

#include <string>

namespace HWToy {

class StreamEOF {};

template<T> struct Stream {
    virtual T    get()    = 0;
    virtual bool is_eof() = 0;
};

class BasicCharStream : Stream<char> {
private:
    const std::string& stream_str;
    uint32_t stream_pos;
public:
    virtual char get();
    virtual bool is_eof();

    BasicCharStream(const std::string& str);
};

};

#endif // __STREAM_H__

