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
        void traverse(std::function<void(Node*, Edge*, int depth)> visitor);
    
    private:
        std::string text;
        Node*       root;
        int*        global_end;
        ActivePoint active_point;
        int         remainder;
        Node*       last_new_internal;
        
        void print_node(Node *node, int indent = 0);
        void traverse_node(Node* node, std::function<void(Node*, Edge*, int)> visitor, int depth);
    };

