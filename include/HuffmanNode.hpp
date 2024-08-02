#pragma once
#include <iostream>
class HuffmanNode {
public:
    HuffmanNode();
    ~HuffmanNode();

    void set_freq(int freq);
    int get_freq() const;
    void set_char(char letter);
    
    unsigned char get_char() const;
    void make_end();
    bool is_end();
    void set_child(HuffmanNode* node,int i);
    HuffmanNode* get_child(int i);
    friend bool operator<(const HuffmanNode& l, const HuffmanNode& r);
    
private:
    HuffmanNode* kids[2];
    int freq;
    bool _is_end;
    unsigned char letter;
    
    
};


struct For_compare {
public:
  bool operator()(const HuffmanNode *a, const HuffmanNode *b) {
    return (a->get_freq()) > (b->get_freq());
  }
};


