#include <iostream>
#include "./suffix_tree.h"

SuffixTree::SuffixTree(const std::string &s)
    : text(s + "$"),
      remainder(0),
      last_new_internal(nullptr)
{
    root = new Node();
    root->suffix_link = root;
    global_end = new int;
    *global_end = -1;
    active_point = {root, -1, 0};
    build();
}


void SuffixTree::build() {
    for(int pos = 0; pos < (int) text.size(); ++pos){
        *global_end = pos;
        remainder++;
        last_new_internal = nullptr;
        while(remainder > 0){
            if(active_point.active_length == 0){
                active_point.active_edge_pos = pos - remainder + 1;
            }
            
            char current_char = text[active_point.active_edge_pos];
            Node *current_node = active_point.active_node;
            // rule 2
            if(current_node->next.find(current_char) == current_node->next.end()){
                Edge *leaf_edge = new Edge();

                leaf_edge->start = active_point.active_edge_pos;
                leaf_edge->end = global_end;
                leaf_edge->dest = new Node();
                current_node->next[current_char] = leaf_edge;
                if(last_new_internal){
                    last_new_internal->suffix_link = current_node;
                    last_new_internal = nullptr;
                }
                remainder--;
            
                if(current_node == root){
                    active_point.active_edge_pos++;
                    if(active_point.active_length > 0)
                        active_point.active_length--;
                } else {
                    active_point.active_node = current_node->suffix_link;
                }
            // rule 1 and 3
            } else {

            }
        }
    }
}



void SuffixTree::print_tree(){
    print_node(root);
}


void SuffixTree::print_node(Node *node, int indent){
    for (const auto& pair : node->next) {
        Edge* edge = pair.second;

        int start = edge->start;
        int end = *(edge->end);

        for (int i = 0; i < indent; ++i) std::cout << "  ";

        std::cout << "[" << start << ", " << end << "]: ";
        std::cout << text.substr(start, end - start + 1) << std::endl;

        print_node(edge->dest, indent + 1);
    }
}
