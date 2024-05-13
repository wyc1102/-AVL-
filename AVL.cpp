#include<iostream>
#include<vector>
using std::vector;
using std::cout;
using std::cin;
using std::endl;
template<class T>
class AVL
{
private:
    struct Node
    {
        T date;
        Node* lchild;
        Node* rchild;
        int bl;
    };
    Node *first;
    int count;
    bool istaller;
    void r_rotate(Node* &t);
    void l_rotate(Node* &t);
    void leftbalecnce(Node* &t);
    void rightbalence(Node* &t);
    bool AVLinsert(Node* &t,T a);
    bool AVLsearch(Node* &t,T a);
    void AVLpreorder(Node* &t,vector<T> &ans);
    void AVLinorder(Node* &t,vector<T> &ans);
public:
    AVL();
    AVL(T date);
    ~AVL(){};
    bool search(T a);
    bool insert(T a);
    vector<T> preorder();
    vector<T> inorder();
};
template<class T>
AVL<T>::AVL()
{
    first = new Node;
    first->bl = 0;
    first->lchild = nullptr;
    first->rchild = nullptr;
    count = 0;
}
template<class T>
AVL<T>::AVL(T a)
{
    first = new Node;
    first->date = a;
    first->lchild = nullptr;
    first->rchild = nullptr;
    count = 1;
    first->bl = 0;
}
template<class T>
bool AVL<T>::AVLsearch(Node* &t,T a)
{
    if(t==nullptr)
    {
        return false;
    }
    else
    {
        if(a==t->date)
        {
            return true;
        }
        else if(a<t->date)
        {
            return AVLsearch(t->lchild,a);
        }
        else
        {
            return AVLsearch(t->rchild,a);
        }
    }
}
template<class T>
bool AVL<T>::AVLinsert(Node* &t,T a)
{
    if(t==nullptr)
    {
        Node* temp = new Node;
        temp->date=a;
        temp->bl=0;
        temp->lchild=nullptr;
        temp->rchild=nullptr;
        t=temp;
        istaller=true;
        count++;
    }
    else
    {
        if(a==t->date)
        {
            return false;
        }
        else if(a<t->date)
        {
            if(!AVLinsert(t->lchild,a))
            {
                return false;
            }
            else if(istaller)
            {
                switch(t->bl)
                {
                    case 1:leftbalecnce(t);istaller=false;break;
                    case 0:t->bl = 1;istaller=true;break;
                    case -1:t->bl=0;istaller=false;break;
                }
            }
        }
        else
        {
            if(!AVLinsert(t->rchild,a))
            {
                return false;
            }
            else if(istaller)
            {
                switch(t->bl)
                {
                    case 1:t->bl=0;istaller=false;break;
                    case 0:t->bl=-1;istaller=true;break;
                    case -1:rightbalence(t);istaller=false;break;
                }
            }
        }
    }
    return true;
}
template<class T>
void AVL<T>::rightbalence(Node* &t)
{
    Node *r,*rl;
    r=t->rchild;
    rl=r->lchild;
    if(r->bl<0)
    {
        t->bl = 0;
        r->bl = 0;
        l_rotate(t);
    }
    else
    {
        switch(rl->bl)
        {
            case 1:rl->bl=0;t->bl=0;r->bl=-1;break;
            case 0:rl->bl=0;t->bl=0;r->bl=0;break;
            case -1:rl->bl=0;t->bl=1;r->bl=0;break;
        }
        r_rotate(r);
        l_rotate(t);
    }
}
template<class T>
void AVL<T>::leftbalecnce(Node* &t)
{
    Node *l,*lr;
    l=t->lchild;
    lr=l->rchild;
    if(l->bl>0)
    {
        t->bl = 0;
        l->bl = 0;
        r_rotate(t);
    }
    else
    {
        switch(lr->bl)
        {
            case 1:lr->bl=0;t->bl=-1;l->bl=0;break;
            case 0:lr->bl=0;t->bl=0;l->bl=0;break;
            case -1:lr->bl=0;t->bl=0;l->bl=1;break;
        }
        l_rotate(l);
        r_rotate(t);
    }
}
template<class T>
void AVL<T>::l_rotate(Node* &t)
{
    Node* r = t->rchild;
    t->rchild = r->lchild;
    r->lchild = t;
    t = r;
}
template<class T>
void AVL<T>::r_rotate(Node* &t)
{
    Node* l = t->lchild;
    t->lchild = l->rchild;
    l->rchild = t;
    t = l;
}
template<class T>
bool AVL<T>::insert(T a)
{
    return AVLinsert(first,a);
}
template<class T>
bool AVL<T>::search(T a)
{
    return AVLsearch(first,a);
}
template<class T>
vector<T> AVL<T>::inorder()
{
    vector<T> ans;
    AVLinorder(first,ans);
    return ans;
}
template<class T>
vector<T> AVL<T>::preorder()
{
    vector<T> ans;
    AVLpreorder(first,ans);
    return ans;
}
template<class T>
void AVL<T>::AVLinorder(Node* &t,vector<T> &ans)
{
    if(t==nullptr)
    {
        return;
    }
    AVLinorder(t->lchild,ans);
    ans.push_back(t->date);
    AVLinorder(t->rchild,ans);
}
template<class T>
void AVL<T>::AVLpreorder(Node* &t,vector<T> &ans)
{
    if(t==nullptr)
    {
        return;
    }
    ans.push_back(t->date);
    AVLpreorder(t->lchild,ans);
    AVLpreorder(t->rchild,ans);
}
int main()
{
    AVL<int> a(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.insert(5);
    a.insert(6);
    a.insert(7);
    a.insert(8);
    a.insert(9);
    a.insert(10);
    a.insert(11);
    vector<int> pre = a.preorder();
    vector<int> in = a.inorder();
    for(int x:pre)
    {
        cout<<x<<' ';
    }
    cout<<endl;
    for(auto x:in)
    {
        cout<<x<<' ';
    }
    cout<<endl<<a.search(10)<<endl;
}