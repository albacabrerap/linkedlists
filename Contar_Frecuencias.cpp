//
// Created by Ary on 8/09/2026.
//

#include <iostream>
#include <unordered_map>
int main() {
    std::cin.tie(nullptr);
    std::cin.sync_with_stdio(false);



    int n , q, i;
    std::cin >> n >> q;

    std::unordered_map<int, int> map;
    while (n--) {
        int contador = 1;
        std::cin >> i;
        if (map.find(i) != map.end()) {
            map[i]++;
        }
        else {
            map.insert({i, contador});
        }
    }

    while (q--) {
        int e;
        std::cin >> e;
        std::cout<< map[e] << "\n";
    }

}