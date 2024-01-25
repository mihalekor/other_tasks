
/*
23. Merge k Sorted Lists
Hard
Topics
Companies
You are given an array of k linked-lists lists, each linked-list is sorted in
ascending order.

Merge all the linked-lists into one sorted linked-list and return it
*/

#include <map>
#include <set>
#include <vector>
using namespace std;
//  Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    ListNode *list = new ListNode();
    ListNode *tmp = list;

    multiset<int> intMulSet;

    for (auto it : lists) {
      ListNode *ln = it;
      while (ln != nullptr) {
        // cout<<ln->val<<" ";
        intMulSet.insert(ln->val);
        ln = ln->next;
      }
      //  cout<<endl;
    }

    for (auto it : intMulSet) {
      ListNode *ls = new ListNode(it);
      tmp->next = ls;
      tmp = tmp->next;
    }
    list = list->next;
    return list;
  }
};
