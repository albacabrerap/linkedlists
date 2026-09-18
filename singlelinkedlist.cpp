#include <iostream>

template <class T>
class linked_list
{
    struct node
    {
        T dato;
        node * next = nullptr;

        // node constructor
        node(const T & d, node * n = nullptr) : dato(d), next(n) {}
    };

    node * head = nullptr;
    node * tail = nullptr;
    size_t size = 0;

    // private reverse
    node* reverseRc(node* curr) {
        //empty list or reached the last node
        if (!curr || !curr->next) {
            return curr;
        }
        // recurse to tail
        node* newHead = reverseRc(curr->next);

        // reverse the link
        curr->next->next = curr;
        curr->next = nullptr;

        return newHead;
    }

public:
    linked_list() = default;

    // destructor
    ~linked_list() {
        clear();
    }

    void clear() {
        node * curr = head;
        while (curr) {
            node * next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // copy constructor
    linked_list(const linked_list & other) {
        for (node * n = other.head; n; n = n->next) {
            push_back(n->dato);
        }
    }

    // move constructor
    linked_list(linked_list && other) noexcept
        : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    // copy operator
    linked_list & operator=(const linked_list & other) {
        if (this != &other) {
            clear();
            for (node * n = other.head; n; n = n->next) {
                push_back(n->dato);
            }
        }
        return *this;
    }

    // move operator
    linked_list & operator=(linked_list && other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void push_front(const T & d) {
        head = new node(d, head);
        if (size == 0) {
            tail = head;
        }
        size++;
    }

    void push_back(const T & d) {
        node * n = new node(d);
        if (size == 0) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        size++;
    }

    node ** search(const T & d) {
        node ** n = &head;
        while (*n && (*n)->dato != d)
            n = &(*n)->next;
        return n;
    }

    node ** remove(node ** n) {
        if (!n || !*n) return n;

        node * nt = *n;
        if (nt == tail) {
            // udating
            tail = nullptr;
        }
        *n = nt->next;
        delete nt;
        size--;
        return n;
    }

    node ** insert(node ** n, const T & d) {
        *n = new node(d, *n);
        if ((*n)->next == nullptr) {
            tail = *n;
        }
        size++;
        return n;
    }

    // access pointer-to-pointer to head
    node ** front() {
        return &head;
    }

    // I
    // iterative reverse
    void reverse() {
        tail = head;
        node * current = head;
        node * temp = nullptr;

        while (current != nullptr) {
            node * next = current->next;
            current->next = temp;
            temp = current;
            current = next;
        }
        head = temp;
    }

    // recursive reverse made public
    void reverseRcp() {
        if (!head) return;
        tail = head;
        head = reverseRc(head); // privately sets the new head
    }

    size_t get_size() const {
        return size;
    }

    friend std::ostream & operator << (std::ostream & os, const linked_list<T> & ll) {
        os << "head -> ";
        for (node * n = ll.head; n; n = n->next)
            os << n->dato << " -> ";
        os << "nullptr";
        return os;
    }
};

int main()
{
    linked_list<int> ll;
    for (int i = 1; i <= 5; ++i)
        ll.push_front(i);

    std::cout << "Original list:\n" << ll << "\n\n";

    // front pointer-to-pointer access
    std::cout << "First node" << (*ll.front())->dato << "\n\n";

    // iterative reverse
    ll.reverse();
    std::cout << "Reverse:\n" << ll << "\n\n";

    // recursive reverse
    ll.reverseRcp();

    


    return 0;
}