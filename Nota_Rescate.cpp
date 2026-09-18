//
// Created by Ary on 18/09/2026.
//

#include <iostream>
#include <unordered_map>

int main() {

    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::string m, r;
    std::cin >> r >> m;

    std::unordered_map<char, int> map;
    for (const char &c : m) {
        map[c]++;
    }


    for (const char &c : r) {
        map[c]--;
    }

    bool resultado = true;
    for (const auto &p : map) {
        if (p.second < 0) {
            resultado = false;
            break;
        }
    }
    resultado ? std::cout << "SI\n" : std::cout << "NO\n";

    return 0;

}