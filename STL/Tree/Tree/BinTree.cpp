#include<iostream>
using namespace std;
template<typename T>
class BinTreeNode {
private:
    template<typename T>
    friend class BinSortTree;
    BinTreeNode<T>* lch;
    BinTreeNode<T>* rch;
    T data;
public:
    BinTreeNode(BinTreeNode* l, BinTreeNode* r, T d) :lch(l), rch(r), data(d) {};
    BinTreeNode() :lch(nullptr), rch(nullptr), data() {};
};
/*二叉排序树（暂定不能有重复元素）*/
template<typename T>
class BinSortTree {
private:
    BinTreeNode<T>* root;
    void destruct(BinTreeNode<T>* p);
    BinTreeNode<T>* current_parent(BinTreeNode<T>* p)const;
    void mid(BinTreeNode<T>* p) const;
public:
    BinSortTree() :root(nullptr) {};
    BinSortTree(BinTreeNode<T>* r) :root(r) {};
    ~BinSortTree();
    bool insert(T a);
    bool erase(T a);
    bool find(T a) const;
    void mid_traverse() const { mid(root); };

};
template<typename T>/*递归析构函数，极简*/
void BinSortTree<T>::destruct(BinTreeNode<T>* p) {
    if (!p) return;
    if (!(p->lch || p->rch)) {
        delete p;
        return;
    }
    destruct(p->lch);
    destruct(p->rch);
    delete p;
}
template<typename T>
BinSortTree<T>::~BinSortTree() {
    auto p = root;
    if (!p) return;
    destruct(p);
}
template<typename T>/*递归函数，极简*/
void BinSortTree<T>::mid(BinTreeNode<T>* ptr) const {
    if (!ptr) return;
    if (ptr->lch) mid(ptr->lch);
    cout << ptr->data << ' ';
    if (ptr->rch) mid(ptr->rch);
}
template<typename T>/*寻找当前节点的双亲（仅用于有序树）*/
BinTreeNode<T>* BinSortTree<T>::current_parent(BinTreeNode<T>* p)const {
    if (!root) return nullptr;//空树
    if (root == p) return nullptr;//p在顶层
    auto t = root;
    while (1) {
        if (t->lch == p || t->rch == p) return t;
        else if (t->data < p->data) {
            if (t->rch)
                t = t->rch;
            else return nullptr;
        }
        else if (t->data > p->data) {
            if (t->lch)
                t = t->lch;
            else return nullptr;
        }
    }
    return nullptr;
}
template<typename T>/*添加新值*/
bool BinSortTree<T>::insert(T a) {
    if (!root) {
        BinTreeNode<T>* np = new BinTreeNode<T>();
        np->data = a;
        np->lch = np->rch = nullptr;
        root = np;
        return true;
    }
    BinTreeNode<T>* p{ root };
    while (1) {
        if (p->data == a) return false;
        else if (p->data < a) {
            if (p->rch)
                p = p->rch;
            else {
                BinTreeNode<T>* np = new BinTreeNode<T>();
                p->rch = np;
                np->data = a;
                np->lch = np->rch = nullptr;
                return true;
            }
        }
        else if (p->data > a) {
            if (p->lch)
                p = p->lch;
            else {
                BinTreeNode<T>* np = new BinTreeNode<T>();
                p->lch = np;
                np->data = a;
                np->lch = np->rch = nullptr;
                return true;
            }
        }
    }
}
template<typename T>/*删除已知值*/
bool BinSortTree<T>::erase(T a) {
    if (!root) return false;//空，返回false
    BinTreeNode<T>* p{ root };
    while (1) {
        if (p->data == a) {
            /*删除p点，用p的左子树最大值做替代*/
            if (p->lch) {
                auto tem = p->lch;
                while (tem->rch)
                    tem = tem->rch;
                BinTreeNode<T>* t = current_parent(tem);
                if (t->data < tem->data) t->rch = nullptr;
                else if (t->data > tem->data) t->lch = nullptr;
                p->data = tem->data;
                delete tem;
                return true;
            }
            /*删除p点，用p的右子树最小值做替代*/
            else if (p->rch) {
                auto tem = p->rch;
                while (tem->lch)
                    tem = tem->lch;
                BinTreeNode<T>* t = current_parent(tem);
                if (t->data < tem->data) t->rch = nullptr;
                else if (t->data > tem->data) t->lch = nullptr;
                p->data = tem->data;
                delete tem;
                return true;
            }
            /*p点是叶子*/
            else {
                BinTreeNode<T>* t = current_parent(p);
                if (t->data < p->data) t->rch = nullptr;
                else if (t->data > p->data) t->lch = nullptr;
                return true;
            }
        }
        else if (p->data < a) {
            if (p->rch) p = p->rch;
            else return false;
        }
        else if (p->data > a) {
            if (p->lch) p = p->lch;
            else return false;
        }
    }

}
template<typename T>/*寻找已知值*/
bool BinSortTree<T>::find(T a)const {
    if (!root) return false;
    auto p{ root };
    while (1) {
        if (p->data == a) return true;
        else if (p->data < a) {
            if (p->rch) p = p->rch;
            else return false;
        }
        else if (p->data > a) {
            if (p->lch) p = p->lch;
            else return false;
        }
    }
}
int main() {
    BinSortTree<int>a;
    a.insert(5);
    a.insert(3);
    a.insert(7);
    a.insert(8);
    a.insert(6);
    a.insert(4);
    a.insert(2);
    a.mid_traverse();
    cout << endl;
    a.erase(3);
    a.erase(2);
    a.mid_traverse();
    cout << endl;

    a.mid_traverse();
    cout << endl;
    cout << "hello world" << endl;
}