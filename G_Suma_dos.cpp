//
// Created by Ary on 8/09/2026.
//


#include <iostream>
#include <unordered_map>

int main() {
    std::cin.tie(nullptr);
    std::cin.sync_with_stdio(false);

    int n, T;


    std::unordered_map<int, int> map;

    std::cin >> n >> T;
    int arr[n];
    int i = 0;
    int size = n;
    while (n--) {
        std::cin >> arr[i];
        i++;
    }
    int j = 0;
    while ( j < size) {
        int searched = T - arr[j];
        if (map.find(searched) != map.end()) {
            std::cout << "SI" << "\n";
            return 0;
        }
        map.insert({arr[j], j});
        j++;
    }
    std::cout << "NO" << "\n";

}
