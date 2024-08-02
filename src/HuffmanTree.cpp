#include "HuffmanTree.hpp"
#include "HuffmanArchiver.hpp"
#include "HuffmanException.hpp"
#include <queue>

HuffmanTree :: HuffmanTree(std::shared_ptr<struct table_frequencies_struct> table_frequencies)
{
    this->table_frequencies = table_frequencies;
    make_tree();
}

unsigned char* vector_to_bytes(std::vector<unsigned char>& v) {
    unsigned char* bytes = new unsigned char[1 + (v.size()+7)/8];
    bytes[0] = v.size();
    int pointer = 1;
    unsigned char byte = 0;

    for(size_t i = 0;i<v.size();i++) {
        byte += (1<<(7-(i%8)))*v[i];

        if(i%8 == 7) 
        {
            bytes[pointer++] = byte;
            byte = 0;
        }
    }

    if(pointer < (1 + ((int)v.size() + 7)/8)) 
    {
        bytes[pointer] = byte;
    }
    
    return bytes;
}

std::shared_ptr<struct table_codes> HuffmanTree :: get_table() 
{
    std::vector<unsigned char> current_code;
    huffman_tree_dfs(current_code,root);

    return this->table_codes;
}

void HuffmanTree :: make_tree()
{
    std::priority_queue<HuffmanNode*,std::vector<HuffmanNode*>,For_compare> queue;

    for(int i = 0;i<256;i++)
    {
        if((*table_frequencies)[i] != 0)
        {
            HuffmanNode* node = new HuffmanNode();

            node->make_end();
            node->set_char((unsigned char)i);
            node->set_freq((*table_frequencies)[i]);
            all_nodes.push_back(node);
            queue.push(node);
        }
        else
        {
            (*table_codes)[i] = new unsigned char[1];
            (*table_codes)[i][0] = (unsigned char) 0;
        }
    }


    if(queue.size() == 1) 
    {
        HuffmanNode* node = queue.top();
        queue.pop();

        root = new HuffmanNode();
        root->set_child(node,0);
        all_nodes.push_back(root);
    }
    else if(queue.size() > 1)
    {
         while(queue.size() > 1)
        {
            HuffmanNode* first = queue.top();
            queue.pop();
            HuffmanNode* second = queue.top();
            queue.pop();
            HuffmanNode* new_node = new HuffmanNode();
            new_node->set_freq((first->get_freq()) + (second->get_freq()));

            new_node->set_child(first,0);
            new_node->set_child(second,1);

            queue.push(new_node);
            all_nodes.push_back(new_node);
        }

        root = queue.top();
        queue.pop();
    }
    else
    {
        throw HuffmanException("Frequency table is empty");
    }

}

void HuffmanTree :: huffman_tree_dfs(std::vector<unsigned char>& current_code,HuffmanNode* node)
{
    
    if(node->is_end())
    {
        (*table_codes)[node->get_char()] = vector_to_bytes(current_code);
    }
    else
    {
        for(size_t i = 0;i<2;i++)
        {
            if(node->get_child(i) != nullptr)
            {
                current_code.push_back((unsigned char)i);
                huffman_tree_dfs(current_code,node->get_child(i));
            }
        }
    }
    if(!current_code.empty())
    {
        current_code.pop_back();
    }
}

HuffmanTree :: ~HuffmanTree()
{
    for(HuffmanNode* node : all_nodes)
    {
        delete node;
    }
}