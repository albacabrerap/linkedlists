#include <iostream>



template<typename T>
struct node {
    T data;
    node<T>* left{nullptr};
    node<T>* right{nullptr};

public:
    node() : data(0), left(nullptr), right(nullptr) {}
    node(T data) : data(data), left(nullptr), right(nullptr) {}
    node(T data, node<T> *left, node<T> *right) : data(data), left(left), right(right) {}

    void insert(const T &data_insertar) {

        if (this->data > data_insertar) {
            if (this->left == nullptr) {
                this->left = new node<T>(data_insertar);
            }else {
                this->left->insert(data_insertar);
            }
        }
        else if (this->data < data_insertar) {
            if (this->right == nullptr) {
                this->right = new node<T>(data_insertar);
            }else {
                this->right->insert(data_insertar);
            }
        }
    }
};

void preorder(node<int>* root) {
    if (root == nullptr) {return;}
    std::cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(node<int>* root) {
    if (root == nullptr) {return;}
    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);

}

void postorder(node<int>* root) {
    if (root == nullptr) {return;}
    postorder(root->left);
    postorder(root->right);
    std::cout << root->data << " ";
}



int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    int x;
    std::cin >> x;
    n--;
    node<int>* head = new node<int>(x);
    while (n--) {

        std::cin >> x;
        head->insert(x);
    }

    preorder(head);
    std::cout << "\n";
    inorder(head);
    std::cout << "\n";
    postorder(head);
    return 0;
}
