#pragma once
#include <iostream>
#include <string>

using namespace std;

// Класс исключений для BST-дерева
class BSTException
{
  string message;

public:
  BSTException(string msg) : message(msg) {}
  string What() { return message; }
};

// Шаблонный класс BST-дерево
template <class TKey, class TData>
class BST
{
protected:
  // Внутренний класс для узла дерева
  class Node
  {
  public:
    TKey key;
    TData data;
    Node *left;
    Node *right;
    // Критерий сбалансированности
    int balance;
    Node(TKey k, TData d)
        : key(k), data(d), left(nullptr), right(nullptr), balance(0) {}
  };
  Node *root;
  int count;
  // Вспомогательные рекурсивные методы
  Node *InsertRec(Node *t, TKey k, TData data, bool &inserted);
  Node *DeleteRec(Node *t, TKey k, bool &deleted);
  Node *Del(Node *t, Node *t0);
  TData SearchRec(Node *t, TKey k);
  void ClearRec(Node *t);
  void TraverseInOrder(Node *t);
  void ShowRec(Node *t, int level);
  int CalcHeight(Node *t);
  void CalcBalance(Node *t);
  Node *CopyRec(Node *t);

public:
  BST();
  BST(const BST<TKey, TData> &tree);
  ~BST();
  // Основные операции АТД
  int Size() const { return count; }
  void Clear();
  bool IsEmpty() const { return count == 0; }
  TData Search(TKey k);
  bool Insert(TKey k, TData data);
  bool Delete(TKey k);
  void Traverse();
  void Show();
  // Дополнительная операция
  void UpdateBalance();
  // Внутренний класс итератора
  class Iterator
  {
  private:
    BST<TKey, TData> *owner;
    Node **stack;
    int stackSize;
    int top;
    Node *current;
    void PushLeftPath(Node *node);

  public:
    Iterator(BST<TKey, TData> *owner);
    ~Iterator();
    void Begin();
    void Next();
    bool IsOff();
    TData &operator*();
    bool operator==(const Iterator &other);
    Iterator &operator++();
  };
};

// Конструктор
template <class TKey, class TData>
BST<TKey, TData>::BST()
{
  root = nullptr;
  count = 0;
}

// Конструктор копирования
template <class TKey, class TData>
BST<TKey, TData>::BST(const BST<TKey, TData> &tree)
{
  root = CopyRec(tree.root);
  count = tree.count;
}

// Рекурсивное копирование дерева
template <class TKey, class TData>
typename BST<TKey, TData>::Node *BST<TKey, TData>::CopyRec(Node *t)
{
  if (t == nullptr)
    return nullptr;
  Node *newNode = new Node(t->key, t->data);
  newNode->balance = t->balance;
  newNode->left = CopyRec(t->left);
  newNode->right = CopyRec(t->right);

  return newNode;
}

// Деструктор
template <class TKey, class TData>
BST<TKey, TData>::~BST() { Clear(); }

// Очистка дерева
template <class TKey, class TData>
void BST<TKey, TData>::Clear()
{
  ClearRec(root);
  root = nullptr;
  count = 0;
}

template <class TKey, class TData>
void BST<TKey, TData>::ClearRec(Node *t)
{
  if (t == nullptr)
    return;
  ClearRec(t->left);
  ClearRec(t->right);
  delete t;
}

// Рекурсивная вставка
template <class TKey, class TData>
bool BST<TKey, TData>::Insert(TKey k, TData data)
{
  bool inserted = false;
  root = InsertRec(root, k, data, inserted);
  if (inserted)
    count++;
  return inserted;
}

template <class TKey, class TData>
typename BST<TKey, TData>::Node *
BST<TKey, TData>::InsertRec(Node *t, TKey k, TData data, bool &inserted)
{
  if (t == nullptr)
  {
    inserted = true;
    return new Node(k, data);
  }
  if (k == t->key)
  {
    inserted = false;
    return t;
  }
  if (k < t->key)
    t->left = InsertRec(t->left, k, data, inserted);
  else
    t->right = InsertRec(t->right, k, data, inserted);
  return t;
}

// Рекурсивный поиск
template <class TKey, class TData>
TData BST<TKey, TData>::Search(TKey k)
{
  return SearchRec(root, k);
}

template <class TKey, class TData>
TData BST<TKey, TData>::SearchRec(Node *t, TKey k)
{
  if (t == nullptr)
    throw BSTException("Ключ не найден");
  if (k == t->key)
    return t->data;
  if (k < t->key)
    return SearchRec(t->left, k);
  else
    return SearchRec(t->right, k);
}

// Рекурсивное удаление
template <class TKey, class TData>
bool BST<TKey, TData>::Delete(TKey k)
{
  bool deleted = false;
  root = DeleteRec(root, k, deleted);
  if (deleted)
    count--;
  return deleted;
}

template <class TKey, class TData>
typename BST<TKey, TData>::Node *BST<TKey, TData>::DeleteRec(Node *t, TKey k,
                                                             bool &deleted)
{
  if (t == nullptr)
  {
    deleted = false;
    return t;
  }
  if (k < t->key)
  {
    t->left = DeleteRec(t->left, k, deleted);
    return t;
  }
  if (k > t->key)
  {
    t->right = DeleteRec(t->right, k, deleted);
    return t;
  }
  deleted = true;
  if (t->left == nullptr && t->right == nullptr)
  {
    delete t;
    return nullptr;
  }
  if (t->left == nullptr)
  {
    Node *x = t->right;
    delete t;
    return x;
  }
  if (t->right == nullptr)
  {
    Node *x = t->left;
    delete t;
    return x;
  }
  t->right = Del(t->right, t);
  return t;
}

template <class TKey, class TData>
typename BST<TKey, TData>::Node *BST<TKey, TData>::Del(Node *t, Node *t0)
{
  if (t->left != nullptr)
  {
    t->left = Del(t->left, t0);
    return t;
  }
  t0->key = t->key;
  t0->data = t->data;
  Node *x = t->right;
  delete t;
  return x;
}

// Обход Lt → t → Rt (симметричный)
template <class TKey, class TData>
void BST<TKey, TData>::Traverse()
{
  TraverseInOrder(root);
  cout << endl;
}

template <class TKey, class TData>
void BST<TKey, TData>::TraverseInOrder(Node *t)
{
  if (t == nullptr)
    return;
  TraverseInOrder(t->left);
  cout << t->key << " ";
  TraverseInOrder(t->right);
}

// Вычисление высоты поддерева
template <class TKey, class TData>
int BST<TKey, TData>::CalcHeight(Node *t)
{
  if (t == nullptr)
    return 0;

  int leftHeight = CalcHeight(t->left);
  int rightHeight = CalcHeight(t->right);
  return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Вычисление критерия сбалансированности
template <class TKey, class TData>
void BST<TKey, TData>::CalcBalance(Node *t)
{
  if (t == nullptr)
    return;
  CalcBalance(t->left);
  CalcBalance(t->right);
  int leftHeight = CalcHeight(t->left);
  int rightHeight = CalcHeight(t->right);
  t->balance = rightHeight - leftHeight;
}

// Дополнительная операция: формирование критериев сбалансированности
template <class TKey, class TData>
void BST<TKey, TData>::UpdateBalance()
{
  CalcBalance(root);
}

// Вывод структуры дерева
template <class TKey, class TData>
void BST<TKey, TData>::Show()
{
  if (root == nullptr)
  {
    cout << "Дерево пусто" << endl;
    return;
  }
  ShowRec(root, 0);
}

template <class TKey, class TData>
void BST<TKey, TData>::ShowRec(Node *t, int level)
{
  if (t == nullptr)
    return;
  ShowRec(t->right, level + 1);
  for (int i = 0; i < 3 * level; i++)
    cout << " ";
  cout << t->data << endl;
  ShowRec(t->left, level + 1);
}

// Реализация итератора
template <class TKey, class TData>
BST<TKey, TData>::Iterator::Iterator(BST<TKey, TData> *owner)
{
  this->owner = owner;
  stackSize = owner->count + 1;
  stack = new Node *[stackSize];
  top = -1;
  current = nullptr;
}

template <class TKey, class TData>
BST<TKey, TData>::Iterator::~Iterator()
{
  delete[] stack;
}

template <class TKey, class TData>
void BST<TKey, TData>::Iterator::PushLeftPath(Node *node)
{
  while (node != nullptr)
  {
    stack[++top] = node;
    node = node->left;
  }
}

template <class TKey, class TData>
void BST<TKey, TData>::Iterator::Begin()
{
  top = -1;
  current = nullptr;
  if (owner->root != nullptr)
  {
    PushLeftPath(owner->root);
    if (top >= 0)
    {
      current = stack[top];
      top--;
    }
  }
}

template <class TKey, class TData>
void BST<TKey, TData>::Iterator::Next()
{
  if (current == nullptr)
    return;

  if (current->right != nullptr)
    PushLeftPath(current->right);

  if (top >= 0)
  {
    current = stack[top];
    top--;
  }
  else
  {
    current = nullptr;
  }
}

template <class TKey, class TData>
bool BST<TKey, TData>::Iterator::IsOff()
{
  return current == nullptr;
}

template <class TKey, class TData>
TData &BST<TKey, TData>::Iterator::operator*()
{
  if (current == nullptr)
    throw BSTException("Итератор не установлен");
  return current->data;
}

template <class TKey, class TData>
bool BST<TKey, TData>::Iterator::operator==(const Iterator &other)
{
  return current == other.current;
}

template <class TKey, class TData>
typename BST<TKey, TData>::Iterator &BST<TKey, TData>::Iterator::operator++()
{
  Next();
  return *this;
}
