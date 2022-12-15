/*Тестовое задание Saber
https://saber.games/
https://hh.ru/vacancy/68361352*/

#include <algorithm>
#include <bitset>
#include <cstring>
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
  std::string data; //произвольные пользов ательские данные
  // int data;
};
struct SerializeNode
{
  ListNode *prev = nullptr; // указатель на предыдущий элемент списка, либо `nullptr ` в случае начала списка
  ListNode *next = nullptr;
  ListNode *rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr`
  int str_size = 0;
  const char *str = nullptr;
};

class List
{
public:
  void Serialize(FILE *file);

  void Deserialize(FILE *file);
  // ... ваши методы для заполнения списка
  List(int count = 0) : head(NULL), tail(NULL), count(count)
  {
    ListNode *pNode; //= nullptr;
    if (count > 0)
    {
      head = new ListNode;
      tail = pNode = head;
      head->data = "00";

      for (int i = 1; i < count; ++i)
      {
        pNode->next = new ListNode;
        pNode->next->prev = pNode;
        pNode = pNode->next;
        pNode->data = to_string(i) + to_string(i); // i;

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
    ListNode *pNode; //= nullptr;
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
  ListNode *head; //= nullptr;
  ListNode *tail; //= nullptr;
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

void List::Serialize(FILE *file) // сохранение списка в файл, файл открыт с помощью `fopen(path, "wb")`
{
  ListNode *pNode; //= nullptr;
  SerializeNode sNode;

  if (file == NULL)
  {
    cout << "List::Serialize: Ошибка при открытии файла.\n";
    return;
  }

  for (pNode = head; pNode != nullptr; pNode = pNode->next)
  {
    sNode.next = pNode->next;
    sNode.prev = pNode->prev;
    sNode.rand = pNode->rand;
    sNode.str_size = pNode->data.size();
    sNode.str = pNode->data.c_str();
    // memcpy((void *)sNode.str, (const void *)pNode->data.c_str(), pNode->data.size());

    if (fwrite(&sNode, sizeof(SerializeNode), 1, file) != 1)
      cout << "Ошибка при записи файла.\n";
    if (fwrite(sNode.str, sizeof(char), pNode->data.size() + 1, file) != 1)
      cout << "Ошибка при записи файла.\n";
    cout << sizeof(*pNode) << " " << sizeof(pNode) << " " << sNode.str << " Size.\n";
  }
}

void List::Deserialize(FILE *file) // восстановление списка из файла, файл открыт с помощью `fopen(path, "rb")`
{
  ListNode *fNode, *pNode;             //= nullptr= nullptr
  SerializeNode *sNode;                //= nullptr;
  char *p = NULL;                      //;
  map<ListNode *, ListNode *> on_addr; // key - старый адрес,  value - новый адрес

  if (file == NULL)
    cout << "List::Deserialize: Ошибка при открытии файла.\n";

  for (count = 0;; ++count) // fNode->next != nullptr
  {
    size_t result = fread(sNode = new SerializeNode, sizeof(SerializeNode), 1, file); // считываем узел в буфер
    result += fread(p = new char[sNode->str_size + 1], sizeof(char), sNode->str_size + sizeof(char),
                    file); // считываем строку + \0

    if (feof(file))
      break;
    else if (result != (1 + sNode->str_size + 1))
    {
      if (feof(file))
        cout << "Преждевременное достижение конца файла.\n";
      else
        cout << "Ошибка при чтении файла. result: " << result << " Номер элемента: " << count << endl;
      break;
    }
    else
    {
      fNode = new ListNode;
      fNode->next = sNode->next;
      fNode->prev = sNode->prev;
      fNode->rand = sNode->rand;
      fNode->data = p;
      cout << "Чтении файла. result: " << result << " Номер/data элемента: " << count << "/" << fNode->data << endl;

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
    delete[] p;
  }

  //замена рандомных старых адресов на новые по словарю
  for (pNode = head; pNode != nullptr; pNode = pNode->next)
    pNode->rand = on_addr[pNode->rand];

  // tail = fNode;  pNode->prev->next;
}
