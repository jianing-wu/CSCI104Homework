#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
#include <iostream>
using namespace std;

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


void ULListStr::push_back(const std::string& val) {
  // if the tail is null (tail == null) 
  // or there is no room after last element in tail (tail_->first == 0)
  if (tail_ == NULL || tail_->last == ARRSIZE) {
    // Creates new item
    Item* item = new Item();
    // Assign the val to the first cell in item 
    item->first = 0;
    item->val[item->first] = val;
    item->last = 1;
    
    // tail <- item
    item->prev = tail_;
    // tail -> item
    if (tail_ != NULL)
      tail_->next = item;
    // item becomes new tail
    tail_ = item;

    if (head_ == NULL) {
      head_ = item;
    }
  } else {
    // when there is room after last element
    // insert after last element
    tail_->val[tail_->last ++] = val;
  }
  size_ ++;
}

void ULListStr::pop_back() {
  if (tail_ == NULL) {
    return;
  }

  // Last element in tail or the real last element overall
  if (size_ == 1 || tail_->last == 1) {
    Item* prev = tail_->prev;
    // No more prev -> tail
    if (prev != NULL) {
      prev->next = NULL;
    }
    // Reassign head when its last item
    if (head_ == tail_) {
      head_ = NULL;
    }
    // Reassign tail
    delete tail_;
    tail_ = prev;
    
  } else {
    tail_->val[-- (tail_->last)] = "";
  }
  size_ --;
}

void ULListStr::push_front(const std::string& val){
  // if the list is empty (head == null) 
  // or there is no room before first element in head(head_->first == 0)
  if (head_ == NULL || head_->first == 0) {
    // Creates new item
    Item* item = new Item();
    // Assign the val to the last cell in item 
    item->first = ARRSIZE - 1;
    item->last = ARRSIZE;
    item->val[item->first] = val;

    // item  -> head
    item->next = head_;
    // item <- head
    if (head_ != NULL)
      head_->prev = item;
    // item becomes new head
    head_ = item;

    if (tail_ == NULL) {
      tail_ = item;
    }
  } else { 
    // there is room before first elemnt in head
    // insert before first element
    head_->val[-- (head_->first)] = val;
  }
  size_ ++;
}

void ULListStr::pop_front() {
  if (head_ == NULL) {
    return;
  }

  // Last element in head or the real last element overall
  if (size_ == 1 || head_->first == ARRSIZE - 1 ) {
    Item* next = head_->next;

    // No more head <- next
    if (next != NULL) {
      next->prev = NULL;
    }

    // Reassign tail when it's last item
    if (tail_ == head_) {
      tail_ = NULL;
    }
    
    // Reassign head
    delete head_;
    head_ = next;
  } else {
    head_->val[head_->first ++] = "";
  }
  size_ --;
}


std::string const & ULListStr::back() const {
  return tail_->val[tail_->last - 1];
}


std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}


std::string* ULListStr::getValAtLoc(size_t loc) const {
  if (loc < 0 || loc >= size_) {
    return NULL;
  }
  Item* cur = head_;
  
  while(cur && loc + 1 > cur->last - cur->first) {
    loc -= (cur->last - cur->first);
    cur = cur->next;
  }
  return cur ? &(cur->val[cur->first + loc]) : NULL;
}
