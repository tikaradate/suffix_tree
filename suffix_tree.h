#include <map>
#include <string>

struct Node;

struct Edge{
    int start, *end;
    Node* dest;
};

struct Node{
    std::map<char, Edge*> next;
    Node* suffix_link;
};

struct ActivePoint{
    Node* active_node;
    int active_edge_pos;
    int active_length;
};

class SuffixTree{
    public:
        SuffixTree(const std::string &s);
        void build();
        void print_tree();
    
    private:
        std::string text;
        Node*       root;
        int*        global_end;
        ActivePoint active_point;
        int         remainder;
        Node*       last_new_internal;
        
        void print_node(Node *node, int indent = 0);
};

