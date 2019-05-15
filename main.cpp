#include <iostream>
#include<stdio.h>
#include<ctime>
#include<cstring>
#include<string>
using namespace std;

template<class T>
struct Node
{
    T key;
    Node<T>* p;
    Node<T>* l;
    Node<T>* r;
    Node()
    {
        key=T();
        p=l=r=NULL;
    }
};
template<class T>
class Container
{
public:
    // Виртуальные методы, будут реализованы далее
    virtual void insert(T value) = 0;
    virtual bool exists(T value) = 0;
    virtual void remove(T value) = 0;
    // Это потом заменим на перегруженный оператор <<
    virtual void print() = 0;

    // Виртуальный деструктор
    virtual ~Container(){} ;
};
template<class T>
class SimpleTree:public Container<T>
{
public:
    Node<T>* root;
    SimpleTree()
    {
        root=NULL;
    }
    void insert(T value)
    {
        Node<T>* y=NULL;
        Node<T>* x=this->root;
        while(x!=NULL)
        {
            y=x;
            if(value<=x->key)
                x=x->l;
            else
                x=x->r;
        }
        Node<T>* z=new Node<T>();
        z->key=value;
        z->p=y;
        z->l=z->r=NULL;
        if(y==NULL)
            this->root=z;
        else
        if(value<=y->key)
            y->l=z;
        else
            y->r=z;
    }
    static void sort(Node<T>* x,int k)
    {
        if(x!=NULL)
        {
            sort(x->l,k+1);
            //printf("(%d,%d) ",x->key,k) ;
            cout<<"("<<x->key<<","<<k<<") ";
            sort(x->r,k+1);
        }

        return ;
    }
    void print()
    {
        sort(this->root,0);
    }
    static Node<T>* search(Node<T>* x,T k)
    {

        while(x!=NULL && k!=x->key)
            if(k<x->key)
                x=x->l;
            else
                x=x->r;
        return x;
    }

    bool exists(T value)
    {
        return (search(this->root,value)!=NULL);
    }
    void transplant(Node<T>* u,Node<T>* v)
    {
        if(u->p==NULL)
            this->root=v;
        else
        if(u==u->p->l)
            u->p->l=v;
        else
            u->p->r=v;
        if(v!=NULL)
            v->p=u->p;
    }
    static Node<T>* minimum(Node<T>* x)
    {
        if(x!=NULL)
            while(x->l!=NULL)
                x=x->l;
        return x;
    }
    void Delete(Node<T>* z)
    {
        Node<T>* y;
        if(z->l==NULL)
            this->transplant(z,z->r);
        else
        if(z->r==NULL)
            this->transplant(z,z->l);
        else
        {
            y=minimum(z->r);
            if(y->p!=z)
            {
                this->transplant(y,y->r);
                y->r=z->r;
                y->r->p=y;
                y->l=z->l;
            }
            this->transplant(z,y);
            y->l=z->l;
            y->l->p=y;

        }
    }
    void remove(T value)
    {
        Node<T>* z=search(this->root,value);
        if(z!=NULL)
            Delete(z);
    }
};

int main()
{
    char str[15];
    string s;
    int n=10;
    srand(time(NULL));
    int i,m;
    SimpleTree<string>* ts=new SimpleTree<string>();
    for(i=0;i<n;i++)
    {
        m=rand()%21;
        sprintf(str, "%d", m);
        s=string(str);
        ts->insert(s);
    }
    cout<<"Tree of string's after creation:\n";
    ts->print();
    cout<<"\n";
    cout<<endl;
    string s1="5";
    string s2="7";
    if(ts->exists(s1))
        cout<< "Search for value \"5\": found\n" ;

    if(!ts->exists(s2))
        cout<<"Search for value \"7\": not found\n";

    cout << "Tree after deletion of the element \"5\":\n" << endl;
    ts->remove("5");
    ts->print();
    cout<<"\n";
    delete ts;

    SimpleTree<int>* ti=new SimpleTree<int>();
    for(i=0;i<n;i++)
    {
        m=rand()%21;
        ti->insert(m);
    }
    cout<<"Tree of int's after creation:\n";
    ti->print();
    cout<<"\n";
    cout<<endl;

    if(ti->exists(5))
        cout<< "Search for value 5: found\n" ;

    if(!ti->exists(7))
        cout<<"Search for value 7: not found\n";

    cout << "Tree after deletion of the element 5:\n " << endl;
    ti->remove(5);
    ti->print();
    cout<<"\n";
    delete ti;


    return 0;
}
