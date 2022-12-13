/*Тестовое задание Saber
https://saber.games/
https://hh.ru/vacancy/68361352*/

#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <vector>

#define BYTE_SIZE 8

using namespace std;

/*
1. Напишите функцию, которая принимает на вход знаковое целое число и печатает его двоичное представление.
*/

// Cложность алгоритма O(N)
void binaryPrint(int decimal)
{
  string binary("");

  if (decimal)
  {
    //битова маска для decimal<0 : "0111...11"
    int quantity_bit = sizeof(decimal) * BYTE_SIZE;
    int bitmask = ~(1 << (quantity_bit - 1));

    while (decimal)
    {
      if (decimal & 1)
        binary.append("1");
      else
        binary.append("0");

      decimal = (decimal >> 1) & (decimal < 0 ? bitmask : ~0);
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

  delete[] out;
}

/*3. Реализуйте функции сериализации и десериализации двусвязного списка. Данные должны
быть записаны в бинарном формате. Ожидаемая алгоритмическая сложность – меньше квадратичной.*/
// структуру ListNode модифицировать нельзя
struct ListNode
{
  ListNode *prev = nullptr; // указатель на предыдущий элемент списка, либо `nullptr ` в случае начала списка
  ListNode *next = nullptr;
  ListNode *rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr`
  // std::string data; //произвольные пользов ательские данные
  int data;
};
class List
{
public:
  void Serialize(FILE *file) // сохранение списка в файл, файл открыт с помощью `fopen(path, "wb")`
  {
    ListNode *pNode = nullptr;

    if (file == NULL)
      cout << "Ошибка при открытии файла.\n";

    for (pNode = head; pNode != nullptr; pNode = pNode->next)
    {
      if (fwrite((void *)pNode, sizeof(ListNode), 1, file) != 1)
        cout << "Ошибка при записи файла.\n";
      cout << sizeof(*pNode) << " " << sizeof(pNode) << " " << sizeof(ListNode) << " Size.\n";
    }
  }

  void Deserialize(FILE *file) // восстановление списка из файла, файл открыт с помощью `fopen(path, "rb")`
  {
    ListNode *fNode = nullptr, *pNode = nullptr;
    map<ListNode *, ListNode *> on_addr; // key - старый адрес,  value - новый адрес

    if (file == NULL)
      cout << "Ошибка при открытии файла.\n";

    /*if (fread(fNode = new ListNode, sizeof(struct ListNode), 1, file) != 1)
    {
      cout << "Ошибка при первом чтении файла.\n";
      return;
    }*/

    for (count = 0;; ++count) // fNode->next != nullptr
    {
      size_t result = fread(fNode = new ListNode, sizeof(ListNode), 1, file); // считываем узел в буфер

      if (feof(file))
        break;
      else if (result != 1)
      {
        if (feof(file))
          cout << "Преждевременное достижение конца файла.";
        else
          cout << "Ошибка при чтении файла. result: " << result << " Номер элемента: " << count << endl;
        break;
      }
      else
      {
        cout << "Чтении файла. result: " << result << " Номер элемента: " << count << endl;

        if (fNode->prev == nullptr) //первый элемент
        {
          head = tail = pNode = fNode;
        }
        else if (fNode->next != nullptr)
        {
          on_addr[fNode->prev] = pNode;
          fNode->prev = pNode;
          pNode->next = fNode;

          pNode = fNode;
        }
        else if (fNode->next == nullptr)
        {
          on_addr[fNode->prev] = pNode;
          on_addr[pNode->next] = fNode;
          fNode->prev = pNode;
          pNode->next = fNode;

          tail = fNode;
        }
      }
    }

    //замена рандомных старых адресов на новые по словарю
    for (pNode = head; pNode != nullptr; pNode = pNode->next)
      pNode->rand = on_addr[pNode->rand];

    // tail = fNode;  pNode->prev->next;
  }
  // ... ваши методы для заполнения списка
  List(int count = 0) : count(count)
  {
    ListNode *pNode = nullptr;
    if (count > 0)
    {
      head = new ListNode;
      tail = pNode = head;
      head->data = 0;

      for (int i = 1; i < count; ++i)
      {
        pNode->next = new ListNode;
        pNode->next->prev = pNode;
        pNode = pNode->next;
        pNode->data = i; // to_string(i) + to_string(i);

        if (pNode->prev != nullptr)
          pNode->rand = pNode->prev->prev;
      }
      tail = pNode;
    }
  };

  ~List()
  {
    ListNode *pNode = nullptr;
    if (count > 0)
    {
      for (pNode = head->next; pNode != nullptr; pNode = pNode->next)
        delete pNode->prev;

      delete tail;
      head = nullptr;
      tail = nullptr;
    }
  }
  void Print()
  {
    ListNode *pNode = nullptr;
    if (count > 0)
    {
      cout << " Head -> Tail\n";
      for (pNode = head; pNode != nullptr; pNode = pNode->next)
        if (pNode->rand != nullptr)
          cout << pNode->data << "(rnd:" << pNode->rand->data << ") ";
        else
          cout << pNode->data << "(rnd:null) ";
      cout << endl;

      cout << " Tail -> Head\n";

      for (pNode = tail; pNode != nullptr; pNode = pNode->prev)
        if (pNode->rand != nullptr)
          cout << pNode->data << "(rnd:" << pNode->rand->data << ") ";
        else
          cout << pNode->data << "(rnd:null) ";
      cout << endl;
    }
  };

private:
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  int count = 0;
};

int main()
{
  cout << "Hello Saber!\n" << endl;

  vector<int> test_value = {0, 1, 90, -99, 1026, -1248};

  for (auto i : test_value)
  {
    cout << "in: " << i << endl;
    binaryPrint(i);

    std::bitset<(sizeof(int) * BYTE_SIZE)> check(i);
    cout << "Check bitset out: " << check << endl;
  }

  char data[] = "  AAA BBB AAA   asdaff  ";
  RemoveDups(data);
  printf("%s\n", data); // "A B A"

  if (0)
  {
    List myList(5);
    FILE *writeFile = fopen("file.txt", "wb");
    myList.Serialize(writeFile);
    fclose(writeFile);
    myList.Print();
  }
  else
  {
    List myList(0);
    FILE *readFile = fopen("file.txt", "rb");
    myList.Deserialize(readFile);
    fclose(readFile);
    myList.Print();
  }

  return 0;
}
