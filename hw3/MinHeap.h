#include <stdexcept>
#include <exception>
#include <vector>
#include <iostream>

template <class T>
class MinHeap {
  public:
    /* Constructor that builds a d-ary Min Heap
        This should work for any d >= 2,
        but doesn't have to do anything for smaller d.*/
    MinHeap (int d) {
      d_ = d;
    }
    

    ~MinHeap () {

    }
       
    /* adds the item to the heap, with the given priority. */
    void add (T item, int priority) {
      items_.push_back(item);
      priorities_.push_back(priority);
      trickleUp(items_.size() - 1);
    }

    /* returns the element with smallest priority.  
    Break ties however you wish.  
    Throws an exception if the heap is empty. */
    const T & peek () const {
      if (items_.empty()) {
        throw "Heap is empty!";
      }

      return items_[0];
    }
       
    /* removes the element with smallest priority.
    Break ties however you wish.
          Throws an exception if the heap is empty. */
    void remove () {
      if (items_.empty()) {
        throw "Heap is empty!";
      }
      int size = items_.size();
      std::swap(items_[0], items_[size - 1]);
      std::swap(priorities_[0], priorities_[size - 1]);
      items_.pop_back();
      priorities_.pop_back();
      trickleDown(0);
    }

    /* returns true iff there are no elements on the heap. */
    bool isEmpty () {
      return items_.empty();
    }

    void print() {
      for (int i = 0; i < items_.size(); i++) {
        std::cout << items_[i] << " ";
      }
      std::cout << "\n";
    }

    void printPri() {
      for (int i = 0; i < priorities_.size(); i++) {
        std::cout << priorities_[i] << " ";
      }
      std::cout << "\n";
    }
  private:
    // whatever you need to naturally store things.
    // You may also add helper functions here.
    int d_;
    std::vector<T> items_;
    std::vector<int> priorities_;

    void trickleUp(int idx) {
      int parentIdx = (idx - 1) / d_;
      while (parentIdx < idx && priorities_[idx] < priorities_[parentIdx]) {
        std::swap(items_[idx], items_[parentIdx]);
        std::swap(priorities_[idx], priorities_[parentIdx]);
        idx = parentIdx;
        parentIdx = (idx - 1) / d_;
      }
    }

    void trickleDown(int idx) {
      int smallestChildIdx = d_ * idx + 1;
      int size = items_.size();
      if (smallestChildIdx >= size) {
        return;
      }

      for (int i = 1; i < d_; i++) {
        int nextChildIdx = (d_ * idx + 1) + i;
        if (nextChildIdx < size 
          && priorities_[nextChildIdx] < priorities_[smallestChildIdx]) {
          smallestChildIdx = nextChildIdx;
        }
      }

      if (priorities_[idx] > priorities_[smallestChildIdx]) {
        std::swap(items_[idx], items_[smallestChildIdx]);
        std::swap(priorities_[idx], priorities_[smallestChildIdx]);
        trickleDown(smallestChildIdx);
      }
    }
};