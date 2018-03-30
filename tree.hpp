#ifndef TREE_H
#define TREE_H

using namespace std;

class Container
{
public:
    // Виртуальные методы, будут реализованы далее
    virtual void insert(int value) = 0;
    virtual bool exists(int value) = 0;
    virtual void remove(int value) = 0;
    // Это потом заменим на перегруженный оператор <<
    virtual void print() = 0;

    // Виртуальный деструктор
    virtual ~Container();
};
typedef struct tree_element {
    int value;			// Element value
    struct tree_element* left;	// Pointer to next element
    struct tree_element* right;
    struct tree_element* parent;
    unsigned char height;
} tree_element;
class Simpletree: public Container
{
protected:
    tree_element* create(int i);
    tree_element* find(int i);
    tree_element* root;
    tree_element* search_by_value(tree_element* s, int value);
    void insert2(tree_element* elem, tree_element* root);
    void print_tree(tree_element* cur_element);
    unsigned char  height(tree_element* p);
    int bfactor(tree_element* p);
    void fixheight(tree_element* p);
    tree_element* rotateright(tree_element* p);
    tree_element* rotateleft(tree_element* q);
    tree_element*  balance(tree_element* p) ;
    tree_element* findmin(tree_element* p) ;
    tree_element*  removemin(tree_element* p);
    tree_element*  remover(tree_element* p, int k);
    void del(tree_element* cur);

public:
     Simpletree();
    ~Simpletree();
    void insert(int value);
    bool exists(int value);
    void remove(int value);
    void print();

    // Все эти методы будут доступны в дочерних классах
};

#endif
