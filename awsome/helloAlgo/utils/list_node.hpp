/**
 * File: list_node.hpp
 */

#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr){};
};

ListNode *vectorToLinkedList(vector<int> list) {
  ListNode *dum = new ListNode(0);
  ListNode *head = dum;
  for (int val : list) {
    head->next = new ListNode(val);
    head = head->next;
  }
  return dum->next;
}

ListNode *getListNode(ListNode *head, int val) {
  while (head != nullptr && head->val != val) {
    head = head->next;
  }
  return head;
}

/* 释放linked list内存 */
void freeMemoryLinkedList(ListNode *curr) {
  ListNode *pre;
  while (curr != nullptr) {
    pre = curr;
    curr = curr->next;
    delete pre;
  }
}
