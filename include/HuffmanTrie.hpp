#pragma once
#include <iostream>
#include <vector>
#include "HuffmanTrieNode.hpp"

class HuffmanTrie {
public:
    HuffmanTrie() ;
    ~HuffmanTrie() ;
    void destructor_dfs(HuffmanTrieNode* node);
    HuffmanTrieNode* get_root();

private:
    HuffmanTrieNode* root;
};