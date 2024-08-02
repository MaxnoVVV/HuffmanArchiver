#include "HuffmanTrieNode.hpp"
#include "HuffmanException.hpp"

HuffmanTrieNode :: HuffmanTrieNode() 
{
    kids[0] = nullptr;
    kids[1] = nullptr;
    _is_end = false;
    _has_char = false;
}
void HuffmanTrieNode :: make_end()
{
    _is_end = true;
}

bool HuffmanTrieNode :: is_end() 
{
    return _is_end;
}

void HuffmanTrieNode :: add_char(unsigned char c)
{
    _char = c;
    _has_char = true;
}

unsigned char HuffmanTrieNode :: get_char()
{
    if(_has_char)
    {
        return _char;
    }
    else
    {
        throw HuffmanException("No char in node");
    }
}
void HuffmanTrieNode :: make_child_node(int i)
{
    if(i < 0 || i > 1)
    {
        throw HuffmanException("Invalid index of node's child");
    }
    else if(kids[i] != nullptr)
    {
       
    }
    else
    {
        kids[i] = new HuffmanTrieNode();
    }
}
HuffmanTrieNode* HuffmanTrieNode :: get_child(int i)
{
    if(i < 0 || i > 1)
    {
        throw HuffmanException("Invalid index of node's child");
    }
    else 
    {
        return kids[i];
    }
}