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
            } else {
                this->left->insertar(data);
            }
        }
        else if (this->data < data) {
            if (this->right == nullptr) {
                this->right = new TreeNode<T>(data);
            } else {
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
            } else {
                actual = actual->right;
            }
        }
        return false;
    }
};

// Función auxiliar para obtener el nodo con el valor mínimo (sucesor)
template<typename T>
TreeNode<T>* obtenerMinimo(TreeNode<T>* nodo) {
    TreeNode<T>* actual = nodo;
    while (actual && actual->left != nullptr) {
        actual = actual->left;
    }
    return actual;
}

// Función recursiva para eliminar un nodo del ABB
template<typename T>
TreeNode<T>* eliminar(TreeNode<T>* root, const T &data) {
    if (root == nullptr) return root;

    if (data < root->data) {
        root->left = eliminar(root->left, data);
    } else if (data > root->data) {
        root->right = eliminar(root->right, data);
    } else {
        // Caso 1: Nodo hoja o con un solo hijo
        if (root->left == nullptr) {
            TreeNode<T>* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode<T>* temp = root->left;
            delete root;
            return temp;
        }

        // Caso 2: Nodo con dos hijos
        TreeNode<T>* temp = obtenerMinimo(root->right);
        root->data = temp->data;
        root->right = eliminar(root->right, temp->data);
    }
    return root;
}

void inorder(TreeNode<int> *root) {
    if (root == nullptr) return;
    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int m;
    if (!(std::cin >> m) || m == 0) return 0;

    TreeNode<int>* root = nullptr;
    std::string s;
    int x;

    while (m--) {
        std::cin >> s >> x;
        if (s == "INSERTAR") {
            if (root == nullptr) {
                root = new TreeNode<int>(x);
            } else {
                root->insertar(x);
            }
        }
        else if (s == "EXISTE") {
            if (root != nullptr && root->Buscar(x)) {
                std::cout << "SI\n";
            } else {
                std::cout << "NO\n";
            }
        }
        else if (s == "ELIMINAR") {
            root = eliminar(root, x);
        }
    }

    if (root == nullptr) {
        std::cout << "VACIO\n";
    } else {
        inorder(root);
        std::cout << "\n";
    }

    return 0;
}