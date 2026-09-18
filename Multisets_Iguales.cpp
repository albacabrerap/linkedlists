//
// Created by Ary on 8/09/2026.
//
#include <iostream>
#include <unordered_map>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::unordered_map<int, int> map;
    int n;
    std::cin >> n;
    while (n--) {
        int x;
        std::cin >> x;
        if (map.find(x) == map.end()) {
            map[x] = 1;
        }else {
            map[x]++;
        }
    }

    int m;
    std::cin >> m;
    while (m--) {
        int x2;
        std::cin >> x2;
        if (map[x2] == 0) {
            std::cout << "NO";
            return 0;
        }
        map[x2]--;
        }
    std::cout << "SI";

    return 0;
    }
