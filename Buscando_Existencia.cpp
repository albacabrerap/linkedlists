//
// Created by Ary on 18/09/2026.
//

#include <iostream>

template<typename T>
struct TreeNode {
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode(T data) : data(data), left(nullptr), right(nullptr) {}

    void insertar(const T &data) {
        if (this->data > data) {
            if (this->left == nullptr) {
                this->left = new TreeNode<T>(data);
            }else {
                this->left->insertar(data);
            }
        }
        else if(this->data < data) {
            if (this->right == nullptr) {
                this->right = new TreeNode<T>(data);
            }else {
                this->right->insertar(data);
            }
        }
    }

    bool Buscar(const T &data) {
        auto actual = this;
        while (actual != nullptr) {
            if (actual->data == data) {
                return true;
            }
            if (data < actual->data) {
                actual = actual->left;
            }else {
                actual = actual->right;
            }
        }
        return false;
    }
};
int main() {

    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n, q, x;
    std::cin >> n >> q;
    std::cin >> x;
    TreeNode<int> *head = new TreeNode<int>(x);
    n--;
    while (n--) {
        std::cin >> x;
        head->insertar(x);
    }

    while (q--) {
        std::cin >> x;
        if (head->Buscar(x)) {
            std::cout << "SI\n";
        }else {
            std::cout << "NO\n";
        }
    }

    return 0;
}