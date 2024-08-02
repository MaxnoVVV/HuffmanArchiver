#pragma once
#include <istream>

class HuffmanTrieNode
{
public:
    HuffmanTrieNode();
    void make_end();
    bool is_end() ;
    void add_char(unsigned char c);
    unsigned char get_char();
    void make_child_node(int i);
    HuffmanTrieNode* get_child(int i);
    
private:
    HuffmanTrieNode* kids[2];
    unsigned char _char;
    bool _is_end;
    bool _has_char;
};