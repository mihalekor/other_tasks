/*Тестовое задание Saber
https://saber.games/
https://hh.ru/vacancy/68361352*/

#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

/*
1. Напишите функцию, которая принимает на вход знаковое целое число и печатает его двоичное представление.
*/

// Cложность алгоритма O(N)
void binaryPrint(int decimal)
{
  string binary;

  if (decimal)
  {
    //битова маска для decimal<0 : "0111...11"
    int quantity_bit = sizeof(decimal) * 8;
    int bitmask = ~(1 << (quantity_bit - 1));

    while (decimal)
    {
      if (decimal & 1)
        binary.append("1");
      else
        binary.append("0");

      // decimal >>= 1;
      // decimal &= bitmask;
      decimal = (decimal >> 1) & bitmask;
    }
    reverse(binary.begin(), binary.end());
  }
  else
    binary = "0";

  cout << "binaryPrint out: " << binary << endl;
}

/*
2. Напишите функцию, удаляющую последовательно дублирующиеся символы в строке:
void RemoveDups(char* str);
// пример использования
char data[] = "AAA BBB AAA";
RemoveDups(data);
printf("%s\n", data); // "A B A"
*/

// Cложность алгоритма O(N)
void RemoveDups(char in[])
{
  if (in[0] == '\0')
    return;

  int size_in = 0;
  int size_out = 1;

  //подсчёт входящей длины
  for (int i = 0; in[i] != '\0'; ++i)
    ++size_in;

  char *out = new char[size_in]{in[0]};

  //удаление повторов
  for (int i = 0; in[i] != '\0'; ++i)
    if (out[size_out - 1] != in[i])
      out[size_out++] = in[i];

  //копируем out в in
  for (int i = 0; i <= size_out; ++i)
    in[i] = out[i];
}

/*3. Реализуйте функции сериализации и десериализации двусвязного списка. Данные должны
быть записаны в бинарном формате. Ожидаемая алгоритмическая сложность – меньше квадратичной.*/
// структуру ListNode модифицировать нельзя
struct ListNode
{
  ListNode *prev = nullptr; // указатель на предыдущий элемент списка, либо `nullptr ` в случае начала списка
  ListNode *next = nullptr;
  ListNode *rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr` std::string data; //
                            // произвольные пользов ательские данные
};
class List
{
public:
  void Serialize(FILE *file); // сохранение списка в файл, файл открыт с помощью `fopen(path, "wb")`
  void Deserialize(FILE *file); // восстановление списка из файла, файл открыт с помощью `fopen(path, "rb")`
  // ... ваши методы для заполнения списка
  List(int count = 0) : count(count){};

private:
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  int count = 0;
};

int main()
{
  cout << "Hello Saber!\n" << endl;

  vector<int> test_value = {0, 1, 99, -99};

  for (auto i : test_value)
  {
    cout << "in: " << i << endl;
    binaryPrint(i);

    std::bitset<8> check(i);
    cout << "Check bitset out: " << check << endl;
  }

  char data[] = "  AAA BBB AAA   asdaff  ";
  RemoveDups(data);
  printf("%s\n", data); // "A B A"
  return 0;
}
