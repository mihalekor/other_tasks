/*
https://coderun.yandex.ru/problem/knight-move/description?currentPage=1&pageSize=10&rowNumber=4
*/
// 4. Ход конём

#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
// Дана прямоугольная доска N×M (N строк и M столбцов)
unsigned int hourseStep(unsigned int N, unsigned int M) {
  unsigned int curN = 0, curM = 0, res = 0;
  int sOver = 0, sBiSize = 0;
  int over = 0;
  for (unsigned int i = 1;; ++i) {
    std::bitset<10> bi{i};
    std::string sBi = bi.to_string();
    int ii = log2(i) + 1;

    if (sBiSize != ii) {

      if (over >= pow(2, sBiSize - 1)) {
        return res;
      }

      sBiSize = ii;
      over = 0;
    }
    curN = 0;
    curM = 0;
    for (unsigned int i = 0; i < ii; ++i) {

      if (sBi[sBi.size() - i - 1] == '1') {
        curN += 2;
        curM += 1;
      } else {
        curN += 1;
        curM += 2;
      }

      if (curN == N - 1 && curM == M - 1)
        ++res;

      if (curN >= N || curM >= M) {
        ++over;
        break;
      }
    }
  }

  return 0;
}

int main2() {
  /*
       Для чтения входных данных необходимо получить их
       из стандартного потока ввода (stdin).
       Данные во входном потоке соответствуют описанному
       в условии формату. Обычно входные данные состоят
       из нескольких строк.

       Можно использовать несколько функций для чтения из stdin:
       * scanf() -- читает данные из потока;
       * fgets() -- читает строку из потока;
       * gets() -- читает строку из потока до символа '\n'.

       Чтобы прочитать из строки стандартного потока:
       * число -- int var; scanf("%d", &var);
       * строку -- char svar[100]; scanf("%s", svar);
       * массив чисел известной длины --
       int len; scanf("%d", &len);
       int* arr = (int*) malloc(len * sizeof(int));
       for (int i = 0; i < len; ++i)
        scanf("%d", &arr[i]);
       * последовательность слов до конца файла --
       char word[100];
       while (scanf("%s", word) == 1) {
        // do something with word
       }

       Чтобы вывести результат в стандартный поток вывода (stdout),
       можно использовать функцию printf().

       Возможное решение задачи "Вычислите сумму A+B":


       int a, b;
       scanf("%d%d", &a, &b);
       printf("%d\n", a + b);
  */

  std::cout << hourseStep(31, 34);
  return 0;
}
