#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

namespace circular_buffer{

  class CircularBuffer{
  public:
    CircularBuffer(std::size_t size):head_{0},tail_{0},count_{0},size_{size},buffer_(size){}
    void clear(){count_=0;head_=0;tail_=0;}
    void overwrite(int32_t elem);
    int32_t read();

    void write(int32_t elem);

  private:
    size_t head_;
    size_t tail_;
    size_t count_;
    size_t size_;
    std::vector<int32_t> buffer_;
  };

};

#endif


