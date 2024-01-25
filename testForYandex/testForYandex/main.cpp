
#include <QCoreApplication>
#include <QDebug>
#include <iostream>

using namespace std;

// поиск непрерывной последовательности суммой равной Х
bool subarray_sum(const vector<int> &non_negative_arr, int X) {
  size_t right = 0;
  int current_sum = 0;
  for (size_t left = 0; left < non_negative_arr.size(); ++left) {
    // пересчитываем сумму
    if (left > 0)
      current_sum -= non_negative_arr[left - 1];

    // при необходимости двигаем правую границу
    while (right < non_negative_arr.size() && current_sum < X) {
      current_sum += non_negative_arr[right];
      ++right;
    }

    if (current_sum == X)
      return true;
  }

  return false;
}

/*
Рассмотрим задачу: дано число N, нужно сгенерировать все правильные скобочные
последовательности из N открывающих и N закрывающих скобок.
*/
// Сигнатура вспомогательной рекурсивной функции
void generate(int left_open, // Сколько открывающих скобок ещё можно поставить
              int left_closed, // Сколько закрывающих скобок ещё можно поставить
              string accum, // Текущая последовательность
              vector<string> *result);

vector<string> generate(int N) {
  // Наша рекурсивная функция ничего не возвращает,
  // вместо этого заполняет результирующий массив
  vector<string> result;

  generate(N, N, "", &result);
  return result;
}

void generate(int left_open, int left_closed, string accum,
              vector<string> *result) {
  if (!left_open && !left_closed) {
    result->push_back(accum);
    return;
  }
  if (left_open)
    generate(left_open - 1, left_closed, accum + "(", result);
  if (left_closed > left_open)
    generate(left_open, left_closed - 1, accum + ")", result);
}

int longest_increasing_subsequence(const vector<int> &arr) {
  vector<int> dp(arr.size(), 1);
  for (size_t i = 1; i < arr.size(); ++i)
    for (size_t j = 0; j < i; ++j)
      if (arr[j] < arr[i])
        dp[i] = max(dp[i], dp[j] + 1);
  return *max_element(dp.begin(), dp.end());
}

#include "lettCode002.cpp"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  vector<int> v1{9, 9, 9, 9, 9, 9, 9}, v2{9, 9, 9, 9};

  ListNode *top1(new ListNode), *top2(new ListNode);
  ListNode *l1 = top1;
  ListNode *l2 = top2;
  for (auto v : v1) {
    l1->next = new ListNode(v);
    l1 = l1->next;
  }
  for (auto v : v2) {
    l2->next = new ListNode(v);
    l2 = l2->next;
  }

  Solution002 sol;
  auto res = sol.addTwoNumbers(top1->next, top2->next);

  while (res != nullptr) {
    cout << res->val;
    res = res->next;
  }

  // delete l1->next, l2->next;
  return a.exec();
}
