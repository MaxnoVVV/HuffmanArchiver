#pragma once
#include <vector>
#include <iostream>
#include "HuffmanTrie.hpp"
#include "HuffmanTrieNode.hpp"

class HuffmanDearchiver
{
    public:
        HuffmanDearchiver();
        ~HuffmanDearchiver();
        void read_data(std::istream& is);
        void write_data(std::ostream& os);
        
    private:
     void read_table(std::istream& is);

     HuffmanTrie trie;
     std::vector<unsigned char> data;
     int READ_BUFFER_SIZE = 4096;
     int WRITE_BUFFER_SIZE = 4096;

     int input_size;
     int output_size;
     int meta_size;
};