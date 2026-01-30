#include "circular_buffer.hpp"

#include <algorithm>
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <utility>


namespace circular_buffer {
  void CircularBuffer::clear(){
    head_=0;
    tail_=0;
    size_=0;
    capacity_=0;

  };

  void CircularBuffer::overwrite(int32_t elem){
    if(size_==capacity_){
      head_=elem;
      head_=(head_+1)%capacity_;
    }
  };
  void CircularBuffer::write(int32_t elem){};

  CircularBuffer::~CircularBuffer(){delete[] buffer_;};
}
