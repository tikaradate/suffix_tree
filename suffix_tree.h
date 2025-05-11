#include <map>
#include <string>

struct End{
    int value;
};

struct Edge{
    int start, *end;
    int dest;
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
    
    private:
        std::string text;
        Node*       root;
        End*        global_end;
        ActivePoint active_point;
        int         remainder;
        Node*       last_new_internal;
};

