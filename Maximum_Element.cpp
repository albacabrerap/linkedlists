//
// Created by Ary on 7/09/2026.
//

#include <algorithm>
#include <iostream>


template <typename T>
struct node {
    T data;
    T current_max;
    node<T>* next{nullptr};

    node() = default;
    explicit node(T data, T max_val) : data(data), current_max(max_val), next(nullptr) {}

};


template<typename T>
struct my_stack {
    node<T> *top_node{nullptr};
    int size{0};


    my_stack() = default;

    [[nodiscard]] bool empty() const {
        return top_node == nullptr;
    }

    void push(T element) {

        T new_max = empty() ? element: std::max(top_node->current_max, element);

        auto ne = new node<T>(element, new_max);
        ne->next = top_node;
        top_node = ne;
        size++;
    }

    void pop() {
        if (empty()) return;
        auto temp = top_node;
        top_node = top_node->next;
        delete temp;
        size--;
    }

    [[nodiscard]] T top() const {
        return top_node->data;
    }

    [[nodiscard]] T top_max() const {
        return top_node->current_max;
    }

    ~my_stack() {
        while (!empty()) {
            this->pop();
        }
    }
};


int main () {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);


    my_stack<int> stack;
    int n, ops[2];

    std::cin >> n;
    while (n--) {

        std::cin >> ops[0];
        if (ops[0] == 1) {
            int val;
            std::cin >> val;
            stack.push(val);
        }
        else if (ops[0] == 2) {
            stack.pop();
        }
        else if (ops[0] == 3) {
            if (!stack.empty()) {
                std::cout << stack.top_max() << "\n";
            }
        }
    }



    return EXIT_SUCCESS;
}