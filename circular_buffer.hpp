#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <cstdint>
#include <cstddef>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

namespace circular_buffer{

  class CircularBuffer{
  public:
    CircularBuffer()=default;
    ~CircularBuffer();
    CircularBuffer(std::size_t size){size_=(int32_t)size;}
    void clear();
    void overwrite(int32_t elem);

    int32_t read(){
      if(size_==capacity_){
        throw std::domain_error("full");
      }
      return buffer_[head_];
    };

    void write(int32_t elem);

  private:
    int32_t head_=0;
    int32_t tail_=0;
    int32_t size_=0;
    int32_t capacity_=0;
    int32_t* buffer_ = nullptr;
  };

};

#endif


