#include <iostream>
#include <vector>
#include <utility>
#include <functional>

template<typename ktype, typename T>
struct hash_table {
    int val;
    std::vector<std::vector<std::pair<ktype, T>>> chains;

    hash_table(int val) : val(val) {
        chains.resize(val);
    }

    int _hash(const ktype &key) const {
        std::hash<ktype> hasher;
        size_t h = hasher(key);
        return h % val;
    }

    T& operator [] (const ktype &key) {
        int chain_position = _hash(key);
        for (auto &pair : chains[chain_position]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
      chains[chain_position].emplace_back(key, T());
        return chains[chain_position].back().second;
    }

    bool has_key (const ktype &key) const {
        int chain_position = _hash(key);
        for (const auto &pair : chains[chain_position]) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    // Inserts a key-value pair. Returns true if a new key was added, false if updated.
    bool insert(const ktype &key, const T &value) {
        int chain_position = _hash(key);
        for (auto &pair : chains[chain_position]) {
            if (pair.first == key) {
                pair.second = value; // Key already exists -> update value
                return false;
            }
        }
        // Key doesn't exist -> append new pair
        chains[chain_position].emplace_back(key, value);
        return true;
    }

    bool remove(const ktype &key) {
        int chain_position = _hash(key);
        auto &chain = chains[chain_position];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                chain.erase(it);
                return true;
            }
        }
        return false;
    }

    void print() const {
        for (int i = 0; i < val; ++i) {
            std::cout << "Bucket " << i << ":\n";
            for (const auto &e : chains[i]) {
                std::cout << "  " << e.first << " --> " << e.second << "\n";
            }
        }
    }
};

int main() {
    hash_table<std::string, int> ht(5);

    // insert
    ht.insert("apple", 100);
    ht.insert("banana", 200);
    ht.insert("cherry", 300);

    std::cout << "After initial inserts\n";
    ht.print();

    // insert update on existing key
    ht.insert("banana", 250);
    std::cout << "\nAfter updating 'banana' to 250\n";
    ht.print();

    // remove
    std::cout << "\nRemoving 'apple': " << (ht.remove("apple") ? "found" : "Not found") << "\n";
    std::cout << "Removing 'grape': " << (ht.remove("grape") ? "found" : "Not found") << "\n";

    std::cout << "\nAfter removing 'apple'\n";
    ht.print();

    return 0;
}

