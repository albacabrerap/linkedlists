//
// Created by Ary on 18/09/2026.
//

#include <iostream>
#include <vector>
int main() {

    int r = 0;
    std::vector <bool> v(256, false);


    std::string J, S;
    std::cin >> J >> S;

    for (char x: J) {
        v[x] = true;
    }

    for (char x: S) {
        if (v[x]) {
            r++;
        }
    }

    std::cout << r << std::endl;
    return 0;
}