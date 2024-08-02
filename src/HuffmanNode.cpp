#include "HuffmanNode.hpp"

HuffmanNode :: HuffmanNode()
{
    kids[0] = nullptr;
    kids[1] = nullptr;
    _is_end = false;
}

void HuffmanNode :: set_freq(int freq)
{
    this->freq = freq;
}

int HuffmanNode :: get_freq() const
{
  return freq;
}

void HuffmanNode :: set_char(char letter)
{
  this->letter = letter;
}

unsigned char HuffmanNode :: get_char() const
{
  return letter;
}

void HuffmanNode :: make_end()
{
  _is_end = true;
}

bool HuffmanNode :: is_end()
{
  return _is_end;
}

void HuffmanNode :: set_child(HuffmanNode* node,int i) {
    kids[i] = node;
}

HuffmanNode* HuffmanNode :: get_child(int i) {
  return kids[i];
}

bool operator<(const HuffmanNode& l, const HuffmanNode& r)
{
  return l.freq < r.freq;
}
    
HuffmanNode :: ~HuffmanNode()
{

}