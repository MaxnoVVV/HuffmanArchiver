#pragma once
#include <map>
#include <vector>
#include "HuffmanNode.hpp"
#include <memory>
#include "tables.hpp"
class HuffmanTree{
public:
    HuffmanTree(std::shared_ptr<struct table_frequencies_struct> table_frequencies);
    ~HuffmanTree();
    
    std::shared_ptr<struct table_codes> get_table();
    
private:
    void huffman_tree_dfs(std::vector<unsigned char>& current_code,HuffmanNode* node);
    void make_tree();

    HuffmanNode* root;
    std::shared_ptr<struct table_frequencies_struct> table_frequencies;
    std::shared_ptr<struct table_codes> table_codes = std::make_shared<struct table_codes>();
    std::vector<HuffmanNode*> all_nodes;
};