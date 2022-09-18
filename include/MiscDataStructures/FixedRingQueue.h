#pragma once
#include <vector>

/*
The Ring Queue data structure, which essentially is the queue interface with circular array implementation
*/

template <class T>
class RingQueue {

public:

  RingQueue(int sizeP) {
    capacity = sizeP;
    arr = std::vector<T>(sizeP);
  }

   // Push to queue. If at capacity, pop.
  bool push(T value) {
    sum += value; // append to sum

    if (size < capacity) {
      arr[size] = value;
      size++;

      return false;

    } else {
      sum -= arr[firstElementIndex]; // since popping last element, subtract from sum
      arr[firstElement] = value;
      firstElement = (firstElement + 1) % capacity;

      return true;
    }
  }

  // Get the average value of all the elements in the queue
  float getAverage() {

    if (size == 0) return 0; 
    return sum / size;
  }

  // Get the value given an index
  T get(int index) {
    return arr[(firstElementIndex + index) % capacity];
  }

  // Get the size of the queue
  int getSize() {
    return size;
  }

private:
  std::vector<T> arr;
  int capacity;
  int size = 0;
  float sum = 0;
  int firstElementIndex = 0;
};