#include <bits/stdc++.h>
#include "./suffix_tree.h"

int main(){
    std::string s;
    std::cin >> s;
    SuffixTree suffix_tree(s);

    suffix_tree.print_tree();

    suffix_tree.traverse([](Node* n, Edge* e, int depth) {
        std::cout << "from " << e->start << " to " << *(e->end) << ", depth = " << depth << std::endl;
    });
}
