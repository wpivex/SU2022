#pragma once
#include "FixedRingQueue.h"

//template <typename T>

RingQueue::RingQueue(int sizeP) {
  capacity = sizeP;
  arr = std::vector<float>(sizeP);
}

// If at capacity, the first element is popped
bool RingQueue::push(float value) {

  sum += value; // append to sum

  if (size < capacity) {
    arr[size] = value;
    size++;
    return false;
  } else {
    sum -= arr[firstElement]; // since popping last element, subtract from sum
    arr[firstElement] = value;
    firstElement = (firstElement + 1) % capacity;
    return true;
  }
}

float RingQueue::getAverage() {

  if (size == 0) return 0; 
  return sum / size;
}

float RingQueue::get(int index) {
  return arr[(firstElement + index) % capacity];
}

int RingQueue::getSize() {
  return size;
}
