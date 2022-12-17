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
void BinaryPrint(int decimal)
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

  cout << "BinaryPrint out : " << binary << endl;
}

/*
2. Напишите функцию, удаляющую последовательно дублирующиеся символы в строке: void RemoveDups(char* str);
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

/*3. Реализуйте функции сериализации и десериализации двусвязного списка. Данные должны быть записаны в бинарном
формате. Ожидаемая алгоритмическая сложность – меньше квадратичной.*/
// структуру ListNode модифицировать нельзя
struct ListNode
{
  ListNode *prev = nullptr; // указатель на предыдущий элемент списка, либо `nullptr ` в случае начала списка
  ListNode *next = nullptr;
  ListNode *rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr`
  std::string data; //произвольные пользов ательские данные
};
struct SerializeNode // структура для серилизации
{
  ListNode *prev = nullptr;
  ListNode *next = nullptr;
  ListNode *rand = nullptr;
  int str_size = 0;
  char *str = nullptr;
};

// Cложность сериализации и десериализации O(N)
class List
{
public:
  // ... ваши методы для заполнения списка
  List(int count = 0) : count(count)
  {
    cout << "Сonstructor List(" << count << "). this: " << this << endl;

    ListNode *pNode; //= nullptr;
    if (count > 0)
    {
      head = new ListNode;
      tail = pNode = head;
      head->data = "Head";

      for (int i = 1; i < count; ++i)
      {
        pNode->next = new ListNode;
        pNode->next->prev = pNode;
        pNode = pNode->next;
        pNode->data = to_string(i);

        if (pNode->prev != nullptr)
          pNode->rand = pNode->prev->prev; // pNode->rand указывает на пред предыдущий
      }
      tail = pNode;
      if (count > 1)
        tail->data = "Tail";
    }
  };

  ~List() { CleanList(); }

  void CleanList()
  {
    cout << "CleanList. this:  " << this << endl;
    ListNode *pNode;
    if (head != nullptr)
    {
      for (pNode = head->next; pNode != nullptr; pNode = pNode->next)
        delete pNode->prev;

      delete tail;
      head = nullptr;
      tail = nullptr;
      count = 0;
    }
  }

  void PushFront(const char *str)
  {
    cout << "PushFront: \"" << str << "\"\n";
    if (head == nullptr)
    {
      head = tail = new ListNode;
      head->data = str;
    }
    else
    {
      head->prev = new ListNode;
      head->prev->next = head;

      head = head->prev;
      head->data = str;

      if (head->next != nullptr)
        head->rand = head->next->next;
    }
    ++count;
  }

  void PushBack(const char *str)
  {
    cout << "PushBack: \"" << str << "\"\n";
    if (head == nullptr)
    {
      head = tail = new ListNode;
      head->data = str;
    }
    else
    {
      tail->next = new ListNode;
      tail->next->prev = tail;

      tail = tail->next;
      tail->data = str;

      if (tail->prev != nullptr)
        tail->rand = tail->prev->prev;
    }
    ++count;
  }

  void Serialize(FILE *file) // сохранение списка в файл, файл открыт с помощью `fopen(path, "wb")`
  {
    cout << "Serialize\n";
    ListNode *pNode = head;
    SerializeNode sNode;

    if (file == NULL)
    {
      cout << "List::Serialize: Error opening the file!\n";
      return;
    }
    else if (head == nullptr)
    {
      cout << "List::Serialize: List is empty.\n";
      return;
    }

    do
    {
      sNode.next = pNode->next; // заполняем структуру для серилизации
      sNode.prev = pNode->prev;
      sNode.rand = pNode->rand;
      sNode.str_size = pNode->data.size();
      memcpy(sNode.str = new char[sNode.str_size + 1], pNode->data.c_str(), sNode.str_size + 1); //размер: символы + \0

      size_t n_write = fwrite(&sNode, sizeof(SerializeNode), 1, file);
      n_write += fwrite(sNode.str, sizeof(char), sNode.str_size + 1, file); //размер: символы + \0
      if (n_write != 1 + sNode.str_size + sizeof(char))
      {
        cout << "Error writing SerializeNode to file!\n";
        break;
      }
      cout << "Writing to file:" << n_write << " byte. data:\"" << sNode.str << "\" \n";
      pNode = pNode->next;
    } while (pNode != nullptr);
  }

  void Deserialize(FILE *file) // восстановление списка из файла, файл открыт с помощью `fopen(path, "rb")`
  {
    cout << "Deserialize\n";
    ListNode *fNode = nullptr, *prevNode = nullptr; //текущий узел из файла, предыдущий
    SerializeNode *sNode;
    //;
    map<ListNode *, ListNode *> on_addr; // key - старый адрес,  value - новый адрес для востановления ListNode *rand

    if (file == NULL)
      cout << "List::Deserialize: Error opening the file!\n";
    CleanList();
    size_t n_read;    //возврат fread
    size_t n_read_ok; //ожидаемый возврат fread
    do
    {
      n_read = fread(sNode = new SerializeNode, sizeof(SerializeNode), 1, file); // считываем по 1му узлу
      n_read += fread(sNode->str = new char[sNode->str_size + 1], sizeof(char), sNode->str_size + 1, file);
      n_read_ok = 1 + sNode->str_size + sizeof(char); // 1 узел + кол-во символов + 1 нулбайт

      if (feof(file))
      {
        cout << "End of file.\n";
        break;
      }
      else if (n_read != n_read_ok) //
      {
        if (feof(file))
          cout << "Error: Reaching the end of the file prematurely!\n";
        else
          cout << "Error reading the file. read: " << n_read << "/" << n_read_ok << " Item number: " << count << endl;
        break;
      }
      else
      {
        cout << "Reading file: " << n_read << " byte. data:\"" << sNode->str << "\" \n";
        fNode = new ListNode;
        fNode->next = sNode->next;
        fNode->prev = sNode->prev;
        fNode->rand = sNode->rand;
        fNode->data = sNode->str;

        //строим список
        if (fNode->prev == nullptr) //первый элемент
        {
          head = tail = prevNode = fNode;
        }
        else if (fNode->next != nullptr) // не последний
        {
          on_addr[fNode->prev] = prevNode; //соотносим старый адрес с новым
          fNode->prev = prevNode;
          prevNode->next = fNode;

          prevNode = fNode;
        }
        else if (fNode->next == nullptr) //последний элемент
        {
          on_addr[fNode->prev] = prevNode; //соотносим старый адрес с новым
          on_addr[prevNode->next] = fNode;
          fNode->prev = prevNode;
          prevNode->next = fNode;

          tail = fNode;
        }
        ++count;
      }

      delete[] sNode->str;
      delete sNode;
    } while (fNode->next != nullptr);

    //замена рандомных старых адресов на новые, для восстановления соотношений по рандомным указателям
    for (prevNode = head; prevNode != nullptr; prevNode = prevNode->next)
      prevNode->rand = on_addr[prevNode->rand];
  }

  void Print_list() //печать списка, формат: данные узла(данные по рандомному адресу)
  {
    ListNode *pNode;
    if (count > 0)
    {
      cout << "Print_list(count=" << count << "). Print format: \"node data (random address data)\":\n";
      for (pNode = head; pNode != nullptr; pNode = pNode->next)
        if (pNode->rand != nullptr)
          cout << "  " << pNode->data << "(" << pNode->rand->data << ")";
        else
          cout << "  " << pNode->data << "(null)";
      cout << endl;

      cout << "Print_list reverse:\n";

      for (pNode = tail; pNode != nullptr; pNode = pNode->prev)
        if (pNode->rand != nullptr)
          cout << "  " << pNode->data << "(" << pNode->rand->data << ")";
        else
          cout << "  " << pNode->data << "(null) ";
      cout << endl;
    }
    else
      cout << "Print_list: list is empty!\n";
  };

private:
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  int count = 0;
};

int main()
{
  cout << "Hello Saber!\n";

  cout << "\nTask 1 (decimal to binar):\n";
  vector<int> test_value = {0, -1, 90, -99, 1026, -1248};

  for (auto i : test_value)
  {
    cout << "in: " << i << endl;
    BinaryPrint(i);

    std::bitset<(sizeof(int) * BYTE_SIZE)> check(i);
    cout << "Check bitset out: " << check << endl;
  }

  cout << "\nTask 2 (delete duplicates):\n";

  char data[] = "  AAA BBB AAA  __ qqWWqq  ZzEe     !!!!!!!";
  cout << "in:\"" << data << "\"" << endl;
  RemoveDups(data);
  printf("out:\"%s\"\n", data); // "A B A"

  cout << "\nTask 3 (serialization):\n";
  List mySerialize(3);
  mySerialize.PushFront("PushFront");
  mySerialize.PushBack("PushBack");
  mySerialize.Print_list();
  FILE *writeFile = fopen("file.txt", "wb");
  mySerialize.Serialize(writeFile);
  fclose(writeFile);

  List myDeserialize(0);
  myDeserialize.Print_list();
  FILE *readFile = fopen("file.txt", "rb");
  myDeserialize.Deserialize(readFile);
  fclose(readFile);
  myDeserialize.Print_list();

  return 0;
}
