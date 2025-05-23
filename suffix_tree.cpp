#include <iostream>
#include <functional>
#include <cassert>
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
            
            // rule 2, a new suffix is formed, therefore we need to initialize 
            // the new edge and its leaf, as well adjusting the suffix link that might 
            // exist
            if(current_node->next.find(current_char) == current_node->next.end()){
                Edge *leaf_edge = new Edge{active_point.active_edge_pos, global_end, new Node()};
                current_node->next[current_char] = leaf_edge;
                if(last_new_internal){
                    last_new_internal->suffix_link = current_node;
                    last_new_internal = nullptr;
                }
                remainder--;
            
                if(current_node == root){
                    active_point.active_edge_pos++;
                    if(active_point.active_edge_pos > pos){
                        active_point.active_edge_pos = pos;
                    }
                    if(active_point.active_length > 0)
                        active_point.active_length--;
                } else {
                    active_point.active_node = 
                        current_node->suffix_link ? current_node->suffix_link : root;
                }
                continue;
            }
            
            Edge *current_edge = current_node->next[current_char];
            int edge_length = *(current_edge->end) - current_edge->start + 1;
            // skip count trick
            if(active_point.active_length >= edge_length){
                active_point.active_node = current_edge->dest;
                active_point.active_edge_pos += edge_length;
                active_point.active_length -= edge_length;
                continue;
            }

            // rule 3
            if(text[current_edge->start + active_point.active_length] == text[pos]){
                if(last_new_internal){
                    last_new_internal->suffix_link = current_node;
                    last_new_internal = nullptr;
                }
                active_point.active_length++;
                break;
            }
            
            int split_start = current_edge->start + active_point.active_length;
            // splitting at the start of an edge
            if (split_start == current_edge->start) {
                Edge *leaf_edge = new Edge(pos, global_end, new Node());
                current_node->next[text[pos]] = leaf_edge;
                if (last_new_internal) {
                    last_new_internal->suffix_link = current_node;
                    last_new_internal = nullptr;
                }
                remainder--;
                if (current_node == root) {
                    active_point.active_edge_pos++;
                } else {
                    active_point.active_node = 
                        (current_node->suffix_link ? current_node->suffix_link : root);
                }
                continue;
            }

            // splitting at the middle of an edge
            Node* split_node = new Node();
            Edge* split_edge = new Edge{split_start, current_edge->end, current_edge->dest};

            split_node->next[text[split_start]] = split_edge;

            Edge* new_leaf = new Edge{pos, global_end, new Node()};
            split_node->next[text[pos]] = new_leaf;
            
            current_edge->end = new int(split_start - 1);
            current_edge->dest = split_node;
            current_node->next[current_char] = current_edge;
        
            if(last_new_internal)
                last_new_internal->suffix_link = split_node;
            last_new_internal = split_node;
            remainder--;

            if(active_point.active_node == root) {
                active_point.active_edge_pos++;
                if(active_point.active_edge_pos > pos){
                    active_point.active_edge_pos = pos;
                }
                if (active_point.active_length > 0)
                    active_point.active_length--;
            } else {
                active_point.active_node = 
                    active_point.active_node->suffix_link ? 
                    active_point.active_node->suffix_link : root;
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


void SuffixTree::traverse(std::function<void(Node*, Edge*, int)> visitor) {
    traverse_node(root, visitor, 0);
}


void SuffixTree::traverse_node(Node* node, std::function<void(Node*, Edge*, int)> visitor, int depth) {
    for (auto& [ch, edge] : node->next) {
        int length = (*(edge->end) - edge->start + 1);
        visitor(node, edge, depth + length); 
        traverse_node(edge->dest, visitor, depth + length);
    }
}
