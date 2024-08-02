#include "HuffmanTrie.hpp"
#include "HuffmanTrieNode.hpp"

HuffmanTrie :: ~HuffmanTrie()
{
    destructor_dfs(root);
}

void HuffmanTrie :: destructor_dfs(HuffmanTrieNode* node)
{
    for(int i = 0;i<2;i++)
    {
        if(node->get_child(i) != nullptr)
        {
            destructor_dfs(node->get_child(i));
        }
    }

    delete node;
}

HuffmanTrie :: HuffmanTrie()
{
    root = new HuffmanTrieNode;
}
HuffmanTrieNode* HuffmanTrie :: get_root() 
{
    return root;
}