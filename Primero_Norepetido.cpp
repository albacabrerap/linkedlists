#include <iostream>
#include <unordered_map>
#include <vector>


int main() {

    int n;
    std::cin >> n;
    std::vector <int> v;
    v.reserve(n);
    std::unordered_map<int, int> map;
    map.reserve(n);
    int m = n;
    while (n--) {
        int e;
        std::cin >> e;
        v.push_back(e);
        map[e]++;
    }

    int result = -1;
    for (int i = 0; i<m ; i++) {
        if (map[v[i]] == 1) {
            std::cout << v[i];
            return 0;
        }

    }

    std::cout << result;
    return 0;

}
