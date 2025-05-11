#include "./suffix_tree.h"

SuffixTree::SuffixTree(const std::string &s)
    : text(s + "$"),
      remainder(0),
      last_new_internal(nullptr)
{
    root = new Node();
    root->suffix_link = root;
    global_end = new End{-1};
    active_point = {root, -1, 0};
    build();
}


void SuffixTree::build() {
    for(int pos = 0; pos < (int) text.size(); ++pos){
        global_end->value = pos;
        remainder++;
        last_new_internal = nullptr;
    }
}