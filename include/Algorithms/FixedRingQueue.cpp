#include "FixedRingQueue.h"
#include "math.h"

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

float RingQueue::standardDeviation() {

  if (size == 0) return 0;

  float sum = 0; // recalc sum to avoid drift
  int i = firstElement;
  int count = 0;
  while (count < size) {
    sum += arr[i];
    i = (i + 1) % capacity;
    count++;
  }
  float mean = sum / size;

  float sumsqr = 0; // sum squared
  i = firstElement;
  count = 0;
  while (count < size) {
    float deviation = arr[i] - mean;
    sumsqr += deviation*deviation;
    i = (i + 1) % capacity;
    count++;
  }

  return sqrt(sumsqr / size);
  
}