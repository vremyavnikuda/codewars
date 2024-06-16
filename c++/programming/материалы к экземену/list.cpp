struct list
{
    int value;
    struct list *next;
};

list *head //заголовок списка
*ptr, //ссылка на текущий элемент
*pred, //ссылка на предыдущий элемент
