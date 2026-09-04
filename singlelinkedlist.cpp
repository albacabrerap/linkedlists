//
// Created by LENOVO on 31/08/2026.
//

#include <iostream>

template <class T>
class linked_list
{
    struct node
    {
        T dato;
        node * next = nullptr;
    };
    node * head = nullptr;
    node * tail = nullptr;
    size_t size = 0;
public:
    ~linked_list() {
        node * curr = head;
        node * next = curr;
        while (curr) {
            delete next;
            curr = curr->next;
            next = curr;
        }
    }
    linked_list() = default;
    void push_front(const T & d)
    {
        if (size == 0 && tail == nullptr)
            tail = new node (d, nullptr);
        else
            head = new node(d, head);
        size++;
    }
    node ** search(const T & d){
        node ** n = &head;
        while(*n && (*n)->dato != d)
            n = &(*n)->next;
        return n;
    }
    node ** remove(node ** n){
        node * nt = *n;
        *n = nt->next;
        delete nt;
        return n;
    }
    node ** insert(node ** n, const T & d){
        *n = new node(d, *n);
        return n;
    }
    friend std::ostream & operator << (std::ostream & os, const
    linked_list<T> & ll){
        os << "head -> ";
        for(node * n = ll.head; n; n = n->next)
            os << n->dato << " -> ";
        return os;
    }

    void reverse(){
        node * current=head;
        node * temp=nullptr;
        while (current!= nullptr) {
            node * next = current->next;
            current->next = temp;
            temp = current;

            current = next;
        }
        head = temp;
    }

    node **front() {
        return &head;
    }
    node * reverseRc(node* &head) {
        if (head->next) {
            return head;
        }
        node * prev = nullptr;
        node * curr = head;
        node * next= curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        reverseRc(curr);

    }



};


