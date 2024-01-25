

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution002 {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    if (l1 == nullptr)
      return l2;
    if (l2 == nullptr)
      return l1;

    ListNode *res(new ListNode), *top = nullptr;

    ListNode *it1 = l1, *it2 = l2;
    int mind = 0;
    while (it1 != nullptr || it2 != nullptr) {
      int sum;
      if (it1 == nullptr) {
        sum = it2->val + mind;
        mind = sum / 10;
        res->next = new ListNode(sum % 10);
        it2 = it2->next;
      } else if (it2 == nullptr) {
        sum = it1->val + mind;
        mind = sum / 10;
        res->next = new ListNode(sum % 10);
        it2 = it2->next;
      } else {
        sum = it1->val + it2->val + mind;
        mind = sum / 10;
        res->next = new ListNode(sum % 10);
        it1 = it1->next;
        it2 = it2->next;
      }
      if (top == nullptr)
        top = res;
      res = res->next;
    }
    if (mind)
      res->next = new ListNode(mind);
    return top->next;
  }
};
