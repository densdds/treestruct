#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// ���������
class Container
{
public:
    // ����������� ������, ����� ����������� �����
    virtual void insert(int value) = 0;
    virtual bool exists(int value) = 0;
    virtual void remove(int value) = 0;
    // ��� ����� ������� �� ������������� �������� <<
    virtual void print() = 0;

    // ����������� ����������
    virtual ~Container();
};

Container::~Container() { }

// ���������� ����������
typedef struct tree_element {
    int value;			// Element value
    struct tree_element* left;	// Pointer to next element
    struct tree_element* right;
    struct tree_element* parent;
    unsigned char height;
} tree_element;

class Simpletree: public Container
{
public:
    Simpletree();
    ~Simpletree();
    void insert(int value);
    bool exists(int value);
    void remove(int value);
    void print();

protected:
    int bfactor(tree_element* p);
    unsigned char height(tree_element* p);
    void fixheight(tree_element* p);
    tree_element* rotateright(tree_element* p);
    tree_element* rotateleft(tree_element* q) ;
    tree_element* balance(tree_element* p); // ������������ ���� p
    tree_element* create(int i);
    tree_element* find(int i);
    tree_element* root;
    tree_element* search_by_value(tree_element* s, int value);
    void insert2(tree_element* elem, tree_element* root);
    void print_tree(tree_element* cur_element);
    void del(tree_element* cur_element);
};
Simpletree::Simpletree()
{
    this->root = NULL;
};

Simpletree::~Simpletree()
{
    tree_element* cur_elem = this->root;
    del(cur_elem);
}

// Create new element, set its value to 'i', return pointer to new element
tree_element* Simpletree::create(int value)
{
    tree_element* elem  = (tree_element*)malloc(sizeof(tree_element));
    elem -> value = value;
    elem -> left = NULL;
    elem -> right = NULL;
    elem -> parent = NULL;
    return elem;
}

// Insert element 'elem' into list 'root' (on the 1st position),
// calls 'create' under the hood
void Simpletree::insert(int value)
{
    // ������� ������� ���������
    tree_element* elem = this->create(value);
    this->insert2(elem,root);
}
void Simpletree::insert2(tree_element* elem, tree_element* croot)
{
    if(this->root ==NULL){
    this->root=elem;
    }
    else
    // �������� � ������
    if ((croot->value > elem->value)&&(croot->left == NULL))
    {croot -> left = elem;
     elem->parent = croot;
     return;}
        else if ((croot -> value <= elem -> value)&&(croot -> right == NULL))
        {croot->right = elem;
         elem->parent=croot;
         return;}
            else if ((croot->value > elem -> value)&&(croot->left!= NULL))  insert2(elem, croot->left);
                else if ((croot->value <= elem -> value)&&(croot->right!= NULL))  insert2(elem, croot -> right);

}

bool Simpletree::exists(int value)
{
    tree_element* cur_element = this->find(value);
    return cur_element != NULL;
}

tree_element* Simpletree::find(int value)
{
    if (root!=NULL)
    {
        tree_element* s = this->root;
    return this->search_by_value(s, value);
    }
    else return NULL;
}

tree_element* Simpletree:: search_by_value(tree_element* s, int value)
{
tree_element* t=NULL;
if(s-> value== value)return s;
if (s->left!= NULL)
{
t=search_by_value(s->left, value);
if(t)return t;
}
if (s->right != NULL)return search_by_value(s->right,value);
return NULL;
}

void Simpletree::remove(int value)
{
    if(this->root!=NULL){
    tree_element* elem = this->find(value);

    if(elem == NULL)
    {
        return;
    }
    else
        if ((elem->left==NULL)&&(elem->right==NULL))
        {
            if(elem->parent->right ==elem) elem->parent->right=NULL;
            else elem->parent->left=NULL;
            free(elem);
        }
        else
            if ((elem->right!=NULL)&&(elem->left!=NULL))
        {
            if(elem->parent->right==elem)
            {
            elem->parent->right =elem->right;
            elem->right->left =elem->left;
            free(elem);}
            else
                {
                    elem->parent->left=elem->right ;
                    elem->right->left=elem->left;
                    free(elem);
                }
        }
        else
            if ((elem->left==NULL)&&(elem->right!=NULL))
        {
           if(elem->parent->right==elem)
            elem->parent->right = elem->right;
           else elem->parent->left=elem->right;
           free(elem);
        }
        else
            if ((elem->left!=NULL)&&(elem->right==NULL))
        {
            if(elem->parent->right==elem)
            elem->parent->right=elem->left;
            else elem->parent->left=elem->left;
        }
    }
}

void Simpletree::print()
{
    if (this->root!=NULL){tree_element* cur_element = this->root;
    // Iterate through elements while NULL is not found
    print_tree(cur_element);}
    else cout<<"Soryan pocani";

}
void Simpletree:: print_tree(tree_element* cur_element)
{
if (cur_element-> left != NULL) print_tree(cur_element->left);

cout<<cur_element->value<< endl;

if (cur_element-> right != NULL) print_tree(cur_element->right);
}

void Simpletree::del(tree_element* cur_element)
{
    if(cur_element!=NULL){
if (cur_element-> left != NULL) del(cur_element->left);

if (cur_element-> right != NULL) del(cur_element->right);
free(cur_element);
cout<<"elem deleted"<< endl;}

}


// TODO

int main()
{
    Container* c = new Simpletree();
    c->exists(3);
    c->remove(3);
    c->print();
    delete c;
    return 0;
}
