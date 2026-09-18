/*#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <stdexcept>

template <typename K, typename V>
class BSTree {
    struct node {
        K key;
        V value;
        node* child[2] = {nullptr, nullptr}; // [0] left | [1] right

        node(const K& k, const V& v) : key(k), value(v) {}
    };

    node* root = nullptr;
    size_t sz = 0;

public:
    BSTree() = default;

    // using queue
    ~BSTree() {
        clear();
    }

    void clear() {
        if (!root) return;
        std::queue<node*> q;
        q.push(root);
        while (!q.empty()) {
            node* curr = q.front();
            q.pop();
            if (curr->child[0]) q.push(curr->child[0]);
            if (curr->child[1]) q.push(curr->child[1]);
            delete curr;
        }
        root = nullptr;
        sz = 0;
    }

    // copy
    BSTree(const BSTree& other) {
        if (!other.root) return;

        root = new node(other.root->key, other.root->value);
        std::queue<std::pair<const node*, node*>> q;
        q.push({other.root, root});

        while (!q.empty()) {
            auto pair = q.front();
            const node* src = pair.first;
            node* dst = pair.second;
            q.pop();

            for (int i = 0; i < 2; ++i) {
                if (src->child[i]) {
                    dst->child[i] = new node(src->child[i]->key, src->child[i]->value);
                    q.push({src->child[i], dst->child[i]});
                }
            }
        }
        sz = other.sz;
    }

    // move
    BSTree(BSTree&& other) noexcept : root(other.root), sz(other.sz) {
        other.root = nullptr;
        other.sz = 0;
    }

    // copy
    BSTree& operator=(const BSTree& other) {
        if (this != &other) {
            clear();
            if (other.root) {
                root = new node(other.root->key, other.root->value);
                std::queue<std::pair<const node*, node*>> q;
                q.push({other.root, root});

                while (!q.empty()) {
                    auto pair = q.front();
                    const node* src = pair.first;
                    node* dst = pair.second;
                    q.pop();

                    for (int i = 0; i < 2; ++i) {
                        if (src->child[i]) {
                            dst->child[i] = new node(src->child[i]->key, src->child[i]->value);
                            q.push({src->child[i], dst->child[i]});
                        }
                    }
                }
                sz = other.sz;
            }
        }
        return *this;
    }

    // move
    BSTree& operator=(BSTree&& other) noexcept {
        if (this != &other) {
            clear();
            root = other.root;
            sz = other.sz;
            other.root = nullptr;
            other.sz = 0;
        }
        return *this;
    }

    node* search(const K& key) const {
        node* curr = root;
        while (curr) {
            if (curr->key == key) return curr;
            curr = curr->child[key > curr->key];
        }
        return nullptr;
    }

    bool contains(const K& key) const {
        return search(key) != nullptr;
    }

    bool insert(const K& key, const V& value) {
        node** p = &root;
        while (*p) {
            if ((*p)->key == key) {
                (*p)->value = value; // Key exists -> update value
                return false;
            }
            p = &((*p)->child[key > (*p)->key]);
        }
        *p = new node(key, value);
        sz++;
        return true;
    }
    V& operator[](const K& key) {
        node** p = &root;
        while (*p) {
            if ((*p)->key == key) {
                return (*p)->value;
            }
            p = &((*p)->child[key > (*p)->key]);
        }
        *p = new node(key, V());
        sz++;
        return (*p)->value;
    }
    bool remove(const K& key) {
        node** p = &root;
        while (*p && (*p)->key != key) {
            p = &((*p)->child[key > (*p)->key]);
        }
        if (!*p) return false;

        node* target = *p;

        // node has 0 or one child
        if (!target->child[0] || !target->child[1]) {
            int child_idx = (target->child[0] == nullptr) ? 1 : 0;
            *p = target->child[child_idx];
            delete target;
        }
        // has two childs
        else {
            node** succ = &(target->child[1]);
            while ((*succ)->child[0]) {
                succ = &((*succ)->child[0]);
            }

            target->key = (*succ)->key;
            target->value = (*succ)->value;

            node* temp = *succ;
            *succ = temp->child[1];
            delete temp;
        }
        sz--;
        return true;
    }

    node* successor(const K& key) const {
        node* curr = root;
        node* succ = nullptr;
        while (curr) {
            if (key < curr->key) {
                succ = curr;
                curr = curr->child[0];
            } else if (key > curr->key) {
                curr = curr->child[1];
            } else {
                if (curr->child[1]) {
                    node* temp = curr->child[1];
                    while (temp->child[0]) temp = temp->child[0];
                    succ = temp;
                }
                break;
            }
        }
        return succ;
    }

    node* predecessor(const K& key) const {
        node* curr = root;
        node* pred = nullptr;
        while (curr) {
            if (key > curr->key) {
                pred = curr;
                curr = curr->child[1];
            } else if (key < curr->key) {
                curr = curr->child[0];
            } else {
                if (curr->child[0]) {
                    node* temp = curr->child[0];
                    while (temp->child[1]) temp = temp->child[1];
                    pred = temp;
                }
                break;
            }
        }
        return pred;
    }

    void inorder() const {
        std::stack<node*> st;
        node* curr = root;
        while (curr || !st.empty()) {
            while (curr) {
                st.push(curr);
                curr = curr->child[0];
            }
            curr = st.top();
            st.pop();
            std::cout << "[" << curr->key << ": " << curr->value << "] ";
            curr = curr->child[1];
        }
        std::cout << "\n";
    }

    void preorder() const {
        if (!root) {
            std::cout << "\n";
            return;
        }
        std::stack<node*> st;
        st.push(root);
        while (!st.empty()) {
            node* curr = st.top();
            st.pop();
            std::cout << "[" << curr->key << ": " << curr->value << "] ";
            if (curr->child[1]) st.push(curr->child[1]);
            if (curr->child[0]) st.push(curr->child[0]);
        }
        std::cout << "\n";
    }

    void postorder() const {
        if (!root) {
            std::cout << "\n";
            return;
        }
        std::stack<node*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            node* curr = s1.top();
            s1.pop();
            s2.push(curr);
            if (curr->child[0]) s1.push(curr->child[0]);
            if (curr->child[1]) s1.push(curr->child[1]);
        }
        while (!s2.empty()) {
            node* curr = s2.top();
            s2.pop();
            std::cout << "[" << curr->key << ": " << curr->value << "] ";
        }
        std::cout << "\n";
    }

    void level_order() const {
        if (!root) return;
        std::queue<node*> q;
        q.push(root);
        while (!q.empty()) {
            node* curr = q.front();
            q.pop();
            std::cout << "[" << curr->key << ": " << curr->value << "] ";
            if (curr->child[0]) q.push(curr->child[0]);
            if (curr->child[1]) q.push(curr->child[1]);
        }
        std::cout << "\n";
    }

    /*
     * recursive
    Node* searchNode(Node* root, int key)
    {
        if (root == nullptr || root->val == key) {
            return root;
        }
        return root->val < key ? searchNode(root->right, key): searchNode(root->left, key);
    }


    Node* deleteNode(Node* root, int data)
    {
        if (root == nullptr)
            return root;
        if (data < root->val) {
            root->left = deleteNode(root->left, data);
        }
        else if (data > root->val) {
            root->right = deleteNode(root->right, data);
        }
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = minValueNode(root->right);

            root->val = temp->val;

            root->right = deleteNode(root->right, temp->val);
        }
        return root;
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            printf("%d ", root->val);
            inorder(root->right);
        }
    }

    void preorder(Node* root) {
        if (root != nullptr) {
            printf("%d ", root->val);
            preorder(root->left);
            preorder(root->right);
        }
    }

    void postorder(Node* root) {
        if (root != nullptr) {
    postorder(root->left);
            postorder(root->right);
            printf("%d ", root->val);
        }
    }#1#

    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }

    class iterator {
        std::vector<node*> st;

        void push_left(node* n) {
            while (n) {
                st.push_back(n);
                n = n->child[0];
            }
        }

    public:
        explicit iterator(node* root_node = nullptr) {
            push_left(root_node);
        }

        node& operator*() const {
            return *st.back();
        }

        node* operator->() const {
            return st.back();
        }

        iterator& operator++() {
            node* curr = st.back();
            st.pop_back();
            if (curr->child[1]) {
                push_left(curr->child[1]);
            }
            return *this;
        }

        bool operator!=(const iterator& other) const {
            if (st.empty() && other.st.empty()) return false;
            if (st.empty() || other.st.empty()) return true;
            return st.back() != other.st.back();
        }

        bool operator==(const iterator& other) const {
            return !(*this != other);
        }
    };

    iterator begin() const { return iterator(root); }
    iterator end() const { return iterator(nullptr); }
};

int main() {
    BSTree<int, std::string> tree;

    tree.insert(50, "Root");
    tree.insert(30, "Thirty");
    tree.insert(70, "Seventy");
    tree.insert(20, "Twenty");
    tree.insert(40, "Forty");
    tree.insert(60, "Sixty");
    tree.insert(80, "Eighty");
    tree[25] = "TwentyFive";
    std::cout << "In-order:    "; tree.inorder();
    std::cout << "Pre-order:   "; tree.preorder();
    std::cout << "Post-order:  "; tree.postorder();
    std::cout << "Level-order: "; tree.level_order();
    for (auto &e : tree) {
        std::cout << e.key << " -> " << e.value << "\n";
    }

    auto* pred = tree.predecessor(50);
    auto* succ = tree.successor(50);
    if (pred) std::cout << "Predecessor of 50: " << pred->key << " (" << pred->value << ")\n";
    if (succ) std::cout << "Successor of 50:   " << succ->key << " (" << succ->value << ")\n";

    tree.remove(30);
    std::cout << "In-order after removal of 30: "; tree.inorder();

    return 0;
}*/