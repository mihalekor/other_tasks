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
  ListNode *prev = nullptr; // указатель на предыдущий элемент списка, либо `nullptr ` в случае начала списка
  ListNode *next = nullptr;
  ListNode *rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr`
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
      tail->data = "Tail";
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

  void Serialize(FILE *file);

  void Deserialize(FILE *file);

  void Print_list()
  {
    ListNode *pNode; //= nullptr;
    if (count > 0)
    {
      cout << "Print_list: Head -> Tail\n";
      for (pNode = head; pNode != nullptr; pNode = pNode->next)
        if (pNode->rand != nullptr)
          cout << "  " << pNode->data << "(rnd:" << pNode->rand->data << ") ";
        else
          cout << "  " << pNode->data << "(rnd:null) ";
      cout << endl;

      cout << "Print_list: Tail -> Head\n";

      for (pNode = tail; pNode != nullptr; pNode = pNode->prev)
        if (pNode->rand != nullptr)
          cout << "  " << pNode->data << "(rnd:" << pNode->rand->data << ") ";
        else
          cout << "  " << pNode->data << "(rnd:null) ";
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
  cout << "Hello Saber!\n";

  cout << "\nЗадание 1(дубли):\n";
  vector<int> test_value = {0, 1, 90, -99, 1026, -1248};

  for (auto i : test_value)
  {
    cout << "in: " << i << endl;
    binaryPrint(i);

    std::bitset<(sizeof(int) * BYTE_SIZE)> check(i);
    cout << "Check bitset out: " << check << endl;
  }

  cout << "\nЗадание 2(дубли):\n";

  char data[] = "  AAA BBB AAA   asdaff  ";
  cout << "in:\"" << data << "\"" << endl;
  RemoveDups(data);
  printf("out:\"%s\"\n", data); // "A B A"

  cout << "\nЗадание 3(сериализация):\n";
  List myList(2);
  FILE *writeFile = fopen("file.txt", "wb");
  myList.Serialize(writeFile);
  fclose(writeFile);
  myList.Print_list();

  List myList2(0);
  FILE *readFile = fopen("file.txt", "rb");
  myList2.Deserialize(readFile);
  fclose(readFile);
  myList2.Print_list();

  return 0;
}

void List::Serialize(FILE *file) // сохранение списка в файл, файл открыт с помощью `fopen(path, "wb")`
{
  ListNode *pNode = head; //= nullptr;
  SerializeNode sNode;

  if (file == NULL)
  {
    cout << "List::Serialize: Ошибка при открытии файла.\n";
    return;
  }
  else if (head == nullptr)
  {
    cout << "List::Serialize: Список пуст.\n";
    return;
  }

  do
  {
    sNode.next = pNode->next; // заполняем структуру для серилизации
    sNode.prev = pNode->prev;
    sNode.rand = pNode->rand;
    sNode.str_size = pNode->data.size();
    memcpy(sNode.str = new char[sNode.str_size + 1], pNode->data.c_str(),
           sNode.str_size + 1); //размер: символы + \0

    size_t n_write = fwrite(&sNode, sizeof(SerializeNode), 1, file);
    n_write += fwrite(sNode.str, sizeof(char), sNode.str_size + 1,
                      file); //размер: символы + \0
    if (n_write != 1 + sNode.str_size + sizeof(char))
    {
      cout << "Ошибка при записи SerializeNode в файл.\n";
      return;
    }
    cout << "Запись файла:" << n_write << " байт data:\"" << sNode.str << "\" \n";
    pNode = pNode->next;
  } while (pNode != nullptr);
}

void List::Deserialize(FILE *file) // восстановление списка из файла, файл открыт с помощью `fopen(path, "rb")`
{
  ListNode *fNode, *prevNode; //= nullptr= nullptr
  SerializeNode *sNode;       //= nullptr;
  //;
  map<ListNode *, ListNode *> on_addr; // key - старый адрес,  value - новый адрес для востановления ListNode *rand

  if (file == NULL)
    cout << "List::Deserialize: Ошибка при открытии файла.\n";

  do // fNode->next != nullptr
  {
    size_t n_read = fread(sNode = new SerializeNode, sizeof(SerializeNode), 1,
                          file); // считываем узел
    n_read += fread(sNode->str = new char[sNode->str_size + 1], sizeof(char), sNode->str_size + 1, file);

    if (feof(file))
    {
      cout << "Конец файла.\n";
      break;
    }
    else if (n_read != (1 + sNode->str_size + sizeof(char))) // 1шт(SerializeNode) + кол-во символов + 1 нулбайт
    {
      if (feof(file))
        cout << "Преждевременное достижение конца файла.\n";
      else
        cout << "Ошибка при чтении файла. result: " << n_read << " Номер элемента: " << count << endl;
      break;
    }
    else
    {
      cout << "Чтение файла: " << n_read << " байт data:\"" << sNode->str << "\" \n";
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
      else if (fNode->next != nullptr)
      {
        on_addr[fNode->prev] = prevNode; //соотносим старый адрес с новым адресом
        fNode->prev = prevNode;
        prevNode->next = fNode;

        prevNode = fNode;
      }
      else if (fNode->next == nullptr) //последний элемент
      {
        on_addr[fNode->prev] = prevNode; //соотносим старый адрес с новым адресом
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

  //замена рандомных старых адресов на новые по словарю
  for (prevNode = head; prevNode != nullptr; prevNode = prevNode->next)
    prevNode->rand = on_addr[prevNode->rand];
}
