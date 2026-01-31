#include "circular_buffer.hpp"

#include <algorithm>
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>


namespace circular_buffer {

  int32_t CircularBuffer::read(){
    if(count_==0){throw std::domain_error("empty");}
    int32_t a = buffer_[head_];
    head_=(head_+1)%size_;
    count_--;
    return a;
  }
  void CircularBuffer::overwrite(int32_t elem){
    if(count_<size_){CircularBuffer::write(elem);}else{
    buffer_[head_]=elem;
    tail_=(head_+1)%size_;
    head_=(head_+1)%size_;}
  };
  void CircularBuffer::write(int32_t elem){
    if(count_==size_){throw std::domain_error("full");}
    buffer_[tail_]=elem;
    tail_=(tail_+1)%size_;
    count_++;
  };
}
