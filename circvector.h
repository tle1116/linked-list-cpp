#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class CircVector {
 private:
  T *data;
  size_t vec_size;
  size_t capacity;
  size_t front_idx;

  // TODO_STUDENT: add private helper functions, such as resize
  // You may also find a "wrapping" function helpful.
void resize(size_t newCapacity) {
  T* newData = new T[newCapacity];
  
  for(size_t i = 0; i < vec_size; i++) {
    newData[i] = at(i);
  }
  delete[] data;

  data = newData;
  capacity = newCapacity;
  front_idx = 0;
}

 public:
  /**
   * Default constructor. Creates an empty `CircVector` with capacity 10.
   */
  CircVector() {
    capacity = 10;
    data = new T[capacity];
    vec_size = 0;
    front_idx = 0;
  }

  /**
   * Creates an empty `CircVector` with given capacity. Capacity must exceed 0.
   */
  CircVector(size_t capacity) {
    if (capacity == 0) {
      throw invalid_argument("capacity need to be greater than 10");
    }

    this->capacity = capacity;
    data = new T[capacity];
    vec_size = 0;
    front_idx = 0;
  }

  /**
   * Returns whether the `CircVector` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return vec_size == 0;
  }

  /**
   * Returns the number of elements in the `CircVector`.
   */
  size_t size() const {
    return vec_size;
  }

  /**
   * Adds the given `T` to the front of the `CircVector`.
   */
  void push_front(T elem) {
    if(vec_size == capacity) {
      resize(capacity * 2);
    }

    front_idx = (front_idx + capacity - 1) % capacity;
    data[front_idx] = elem;
    vec_size++;
  }

  /**
   * Adds the given `T` to the back of the `CircVector`.
   */
  void push_back(T elem) {
    if(vec_size == capacity) {
      resize(capacity * 2);
    }

    size_t pushBack = (front_idx + vec_size) % capacity;
    data[pushBack] = elem;
    vec_size++;
  }

  /**
   * Removes the element at the front of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if(empty()) {
      throw runtime_error("CircVector is empty");
    }
    T value = data[front_idx];
    front_idx = (front_idx + 1) % capacity;
    vec_size--;
    return value;
  }

  /**
   * Removes the element at the back of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if(empty()) {
      throw runtime_error("CircVector is empty");
    }
    size_t pushBack = (front_idx + vec_size - 1) % capacity;
    T value = data[pushBack];
    vec_size--;
    return value;
  }

  /**
   * Removes all elements from the `CircVector`.
   */
  void clear() {
    vec_size = 0;
    front_idx = 0;
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~CircVector() {
    delete[] data;
  }

  /**
   * Returns the element at the given index in the `CircVector`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T& at(size_t index) const {
    if (index >= vec_size) {
      throw out_of_range("index out of range");
    }
    
    size_t given_index = (front_idx + index) % capacity;
    return data[given_index];
  }

  /**
   * Copy constructor. Creates a deep copy of the given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector(const CircVector &other) {
    capacity = other.capacity;
    vec_size = other.vec_size;
    front_idx = other.front_idx;
    data = new T[capacity];

    for(size_t i = 0; i < capacity; i++) {
      data[i] = other.data[i];
    }
  }

  /**
   * Assignment operator. Sets the current `CircVector` to a deep copy of the
   * given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector &operator=(const CircVector &other) {
    if (this == &other) {
      return *this;
    }
    delete[] data;

    capacity = other.capacity;
    vec_size = other.vec_size;
    front_idx = other. front_idx; 
    data = new T[capacity];

    for(size_t i =0; i <capacity; i++) {
      data[i] = other.data[i];
    }
    return *this;
  }

  /**
   * Converts the `CircVector` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    stringstream ss;
    ss << "[";
    for(size_t i = 0; i < vec_size; i++) {
      ss << at(i);
      if(i != vec_size -1) {
        ss << ", ";
      }
    }
    ss << "]";
    return ss.str();
  }

  /**
   * Searches the `CircVector` for the first matching element, and returns its
   * index in the `CircVector`. If no match is found, returns "-1".
   */
  size_t find(const T &target) {
    for(size_t i = 0; i < vec_size; i++) {
      if(at(i) == target) {
        return i;
      }
    }
    return -1;
  }

  /**
   * Removes the last occurrence of the given `value` from the `CircVector`.
   *
   * For example, if a list was `[0, 1, 2, 1, 0, 1, 8]`, then a call to 
   * `remove_last(1)` should change the list to be [0, 1, 2, 1, 0, 8]`.
   * 
   * If the given value is not found on the `CircVector`, throws an 
   * `invalid_argument` exception.
   */
  void remove_last(const T& value) {
    int index = -1;
    
    for(size_t i = 0; i < vec_size; i++) {
      if (at(i)== value) {
        index = i;
      }
    }

    if(index == -1) {
      throw invalid_argument("value is not found");
    }

    for(size_t i = index; i < vec_size - 1; i++) {
      at(i) = at(i + 1);
    }
    vec_size--;
  }

  /**
   * Inserts the given `T` as a new element in the `CircVector` before
   * the element currently stored in the given index. If the index is not 
   * a current valid index in the list, throws `out_of_range`.
   */
  void insert_before(size_t index, T elem) {
    if(index >= vec_size) {
      throw out_of_range("index out of range");
    }
    push_back(elem);

    for(size_t i = vec_size - 1; i > index; i--) {
      at(i) = at(i-1);
    }
    at(index) = elem;
  }

  /**
   * Remove every other element (alternating) from the
   * `CircVector`, starting at index 1. Must run in O(N). May not reallocate.
   *
   * For example, if a list was `[0, 1, 2, 3, 4]`, removing every other element
   * would change the list to `[0, 2, 4]`.
   */
  void remove_every_other() {
    size_t newIndex = 1;

    for(size_t i = 2; i < vec_size; i+=2) {
      at(newIndex) = at(i);
      newIndex++;
    }
    vec_size = newIndex;
  }

  /**
   * Returns a pointer to the underlying memory managed by the `CircVec`.
   * For autograder testing purposes only.
   */
  T *get_data() const {
    return this->data;
  }

  /**
   * Returns the capacity of the underlying memory managed by the `CircVec`. For
   * autograder testing purposes only.
   */
  size_t get_capacity() const {
    return this->capacity;
  }
};