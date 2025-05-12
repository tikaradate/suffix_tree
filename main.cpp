#include <bits/stdc++.h>
#include "./suffix_tree.h"

int main(){
    std::string s;
    std::cin >> s;
    SuffixTree suffix_tree(s);

    suffix_tree.print_tree();
}
