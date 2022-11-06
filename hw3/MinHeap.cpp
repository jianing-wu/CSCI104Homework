#include "MinHeap.h"


class MinHeap {
  public:
    MinHeap (int d);
    /* Constructor that builds a d-ary Min Heap
        This should work for any d >= 2,
        but doesn't have to do anything for smaller d.*/

    ~MinHeap ();

    void add (T item, int priority);
       /* adds the item to the heap, with the given priority. */

    const T & peek () const;
       /* returns the element with smallest priority.  
		Break ties however you wish.  
		Throws an exception if the heap is empty. */

    void remove ();
       /* removes the element with smallest priority.
		Break ties however you wish.
          Throws an exception if the heap is empty. */

    bool isEmpty ();
       /* returns true iff there are no elements on the heap. */

  private:
    // whatever you need to naturally store things.
    // You may also add helper functions here.
    std::vector<T> items_;
    std::vector<int> priorities_;

    void trickleUp(int idx);
    void trickleDown(int idx);
};