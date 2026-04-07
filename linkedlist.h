#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node *next;

    Node(T data) {
      this->data = data;
      this->next = nullptr;
    }

    Node(T data, Node *next) {
      this->data = data;
      this->next = next;
    }
  };

  size_t list_size;
  Node *list_front;

 public:
  /**
   * Default constructor. Creates an empty `LinkedList`.
   */
  LinkedList() {
    list_front = nullptr;
    list_size = 0;
  }

  /**
   * Returns whether the `LinkedList` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return list_size == 0;
  }

  /**
   * Returns the number of elements in the `LinkedList`.
   */
  size_t size() const {
    return list_size;
  }

  /**
   * Adds the given `T` to the front of the `LinkedList`.
   */
  void push_front(const T& data) {
    Node* newNode = new Node(data, list_front);
    list_front = newNode;
    list_size++;
  }

  /**
   * Adds the given `T` to the back of the `LinkedList`.
   */
  void push_back(T data) {
    Node* newNode = new Node(data);
    if (empty()) {
      list_front = newNode;
    }
    else {
      Node* curr = list_front;
      while (curr->next != nullptr) {
        curr = curr->next;
      }
      curr->next = newNode;
    }
    list_size++;
  }

  /**
   * Removes the element at the front of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (empty()) {
      throw runtime_error("list empty");
    }
    Node* temp = list_front;
    T value = temp->data;
    list_front = list_front->next;
    delete temp;
    list_size--;
    return value;
  }

  /**
   * Removes the element at the back of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if(empty()) {
      throw runtime_error("list empty");
    }
    Node* curr  = list_front;
    if (curr->next == nullptr) {
      T value = curr->data;
      delete curr;
      list_front = nullptr;
      list_size--;
      return value;
    }
    
    while (curr->next->next != nullptr) {
      curr = curr->next;
    }

    Node* last = curr->next;
    T value = last->data;
    delete last;
    curr-> next = nullptr;
    list_size--;
    return value;
  }

  /**
   * Empties the `LinkedList`, releasing all allocated memory, and resetting
   * member variables appropriately.
   */
  void clear() {
    while(!empty()) {
      pop_front();
    }
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~LinkedList() {
    clear();
  }

  /**
   * Returns the element at the given index in the `LinkedList`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T &at(size_t index) const {
    if (index >= list_size) {
      throw out_of_range("index out of range");
    }
    Node* curr = list_front;
    for(size_t i = 0 ; i < index; i++) {
      curr = curr->next;
    }
    return curr->data;
  }

  /**
   * Copy constructor. Creates a deep copy of the given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList(const LinkedList &other) {
    list_front = nullptr;
    list_size = 0;


    Node* curr = other.list_front;
    Node* end = nullptr;

    while(curr != nullptr) {
      Node* node = new Node(curr->data);

      if(list_front == nullptr) {
        list_front = node;
        end = node;
      }
      else {
        end->next = node;
        end = node;
      }
      curr = curr->next;
      list_size++;
    }
  }
  

  /**
   * Assignment operator. Sets the current `LinkedList` to a deep copy of the
   * given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList &operator=(const LinkedList &other) {
    if (this == &other) {
      return *this;
    }
    clear();

    Node* curr = other.list_front;
    Node* end = nullptr;

    while(curr != nullptr) {
      Node* node = new Node(curr->data);

      if(list_front == nullptr) {
        list_front = node;
        end = node;
      }
      else {
        end->next = node;
        end = node;
      }
      curr = curr->next;
      list_size++;
    }
    return *this;
  }

  /**
   * Converts the `LinkedList` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    string value = "[";
    Node* curr = list_front;

    while(curr != nullptr) {
      value += std::to_string(curr->data);
      if(curr->next != nullptr) {
        value += ", ";
      }
      curr = curr->next;
    }
    value += "]";
    return value;
  }

  /**
   * Searches the `LinkedList` for the first matching element, and returns its
   * index. If no match is found, returns "-1".
   */
  size_t find(const T &data) {
    Node* curr = list_front;
    size_t index = 0;

    while(curr != nullptr) {
      if(curr->data == data) {
        return index;
      }
      curr = curr->next;
      index++;
    }
    return -1;
  }

  /**
   * Removes the last occurrence of the given value from the `LinkedList`.
   *
   * For example, if a list was `[0, 1, 2, 1, 0, 1, 8]`, then a call to 
   * `remove_last(1)` should change the list to be [0, 1, 2, 1, 0, 8]`.
   * 
   * If the given value is not found on the `LinkedList`, throws an 
   * `invalid_argument` exception.
   */
  void remove_last(const T& value) {
    Node* curr = list_front;
    Node* prev = nullptr;
    Node* lastMatch = nullptr;
    Node* lastPrev = nullptr;

    while(curr != nullptr) {
      if(curr->data == value) {
        lastMatch = curr;
        lastPrev = prev;
      }
      prev = curr;
      curr = curr->next;
    }
    if(lastMatch == nullptr) {
      throw invalid_argument("value is not found");
    }
    if(lastPrev == nullptr) {
      pop_front();
      return;
    }
    lastPrev->next = lastMatch->next;
    delete lastMatch;
    list_size--;
  }

  /**
   * Inserts the given `T` as a new element in the `LinkedList` before
   * the element currently stored in the given index. If the index is not 
   * a current valid index in the list, throws `out_of_range`.
   */
  void insert_before(size_t index, T elem) {
    if (index >= list_size) {
      throw out_of_range("index is invalid");
    }

    if(index == 0) {
      push_front(elem);
      return;
    }

    Node* curr = list_front;
    for (size_t i =0; i < index -1; i++) {
      curr = curr->next;
    }

    Node* newNode = new Node(elem, curr->next);
    curr->next = newNode;
    list_size++;
  }

  /**
   * Remove every other element (alternating) from the
   * `LinkedList`, starting at index 1. Must run in O(N).
   *
   * For example, if a list was `[0, 1, 2, 3, 4]`, removing every other element
   * would change the list to `[0, 2, 4]`.
   */
  void remove_every_other() {
    if(list_front == nullptr) {
      return;
    }

    Node* curr = list_front;

    while(curr != nullptr && curr->next != nullptr) {
      Node* temp = curr->next;
      curr->next = temp->next;
      delete temp;
      list_size--;
      curr = curr->next;
    }
  }

  /**
   * Returns a pointer to the node at the front of the `LinkedList`. For
   * autograder testing purposes only.
   */
  void *front() const {
    return this->list_front;
  }
};