#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tree.hpp"

using std::cout;
using std::endl;


Container::~Container() { }

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
tree_element* Simpletree::create(int val)
{
    tree_element* elem  = (tree_element*)malloc(sizeof(tree_element));
    elem -> value = val;
    elem -> left = NULL;
    elem -> right = NULL;
    elem -> parent = NULL;
    return elem;
}

// Insert element 'elem' into list 'root' (on the 1st position),
// calls 'create' under the hood
void Simpletree::insert(int value)
{
    // Создали элемент физически
    tree_element* elem = this->create(value);
    this->insert2(elem,root);
}
void Simpletree::insert2(tree_element* elem, tree_element* croot)
{
    if(this->root ==NULL){
    this->root=elem;
    }
    else
    // Вставили в список
    if ((croot->value > elem->value)&&(croot->left == NULL))
    {croot -> left = elem;
     elem->parent = croot;
     balance(croot);}
        else if ((croot -> value <= elem -> value)&&(croot -> right == NULL))
        {croot->right = elem;
         elem->parent=croot;
         balance(croot);}
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
    tree_element* s = this->root;
    return this->search_by_value(s, value);
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


void Simpletree::print()
{
    tree_element* cur_element = this->root;
    // Iterate through elements while NULL is not found
    print_tree(cur_element);

}
void Simpletree:: print_tree(tree_element* cur_element)
{
if (cur_element-> left != NULL) print_tree(cur_element->left);

cout<<cur_element->value<< endl;

if (cur_element-> right != NULL) print_tree(cur_element->right);
}



unsigned char Simpletree:: height(tree_element* p)
{
    return p?p->height:0;
}

int Simpletree:: bfactor(tree_element* p)
{
    return height(p->right)-height(p->left);
}

void Simpletree::fixheight(tree_element* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

tree_element* Simpletree::rotateright(tree_element* p) // правый поворот вокруг p
{
    tree_element* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}
tree_element* Simpletree::rotateleft(tree_element* q) // левый поворот вокруг q
{
    tree_element* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

tree_element* Simpletree:: balance(tree_element* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

tree_element* Simpletree::findmin(tree_element* p) // поиск узла с минимальным ключом в дереве p
{
    return p->left?findmin(p->left):p;
}

tree_element* Simpletree:: removemin(tree_element* p) // удаление узла с минимальным ключом из дерева p
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

tree_element* Simpletree::  remover(tree_element* p, int k) // удаление ключа k из дерева p
{
    if( !p ) return 0;
    if( k < p->value )
        p->left = remover(p->left,k);
    else if( k > p->value )
        p->right = remover(p->right,k);
    else //  k == p->value
    {
        tree_element* q = p->left;
        tree_element* r = p->right;
        delete p;
        if( !r ) return q;
        tree_element* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void Simpletree:: remove (int k)
{
  tree_element*p = this -> root;
  remover(p,k);
}

void Simpletree::del(tree_element* cur_element)
{
if (cur_element-> left != NULL) del(cur_element->left);

if (cur_element-> right != NULL) del(cur_element->right);
free(cur_element);
cout<<"elem deleted"<< endl;
}
