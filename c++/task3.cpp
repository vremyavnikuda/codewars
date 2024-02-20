#include<iostream>
using namespace std;


///Лабораторная работа №3 "Бинарные деревья"
/*
Варианты заданий 

- Определить максимальную глубину непустого дерева Т, то есть число ветвей в самом длинном из путей от корня дерева до листьев.
*/

/*
Этот код определяет структуру Node для узлов дерева и функцию maxDepth для вычисления максимальной глубины. 
Функция maxDepth использует рекурсию для обхода всех узлов дерева и возвращает максимальную глубину. 
Если дерево пустое, функция возвращает 0. 
Пожалуйста, учтите, что вам нужно создать дерево и вызвать функцию maxDepth в функции main.
*/
struct Node{
    int data;
    Node* left;
    Node* right;
};

//Строим ноды дерева 
Node* newNode(int data){
    Node* node= new Node();
    if (!node){
        cout << "Memory error\n";
        return NULL;
    }
    node ->data = data;
    node ->left = node->right=NULL;
    return node;
}

//Шарим дерево
int maxDepth(Node* node){
    if (node==NULL){
        return 0;
    }
    else{
        //вычисление глубины каждого дерева
        int ldepth = maxDepth(node->left);
        int rdepth = maxDepth(node->right);

        //возвращение максимальной глубины
        if (ldepth>rdepth){
            return(ldepth+1);
        }
        else{
            return(rdepth+1);
        }
    }
}

//Вода == мокрая 
int main() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    cout << "Height of tree is " << maxDepth(root);
    return 0;
}