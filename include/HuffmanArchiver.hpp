#pragma once
#include "HuffmanArchiver.hpp"
#include <iostream>
#include "HuffmanTree.hpp"
#include <vector>
#include <memory>
#include "tables.hpp"

class HuffmanArchiver {
public:
    HuffmanArchiver();
    ~HuffmanArchiver();
    void read_data(std::istream& is);
    void write_data(std::ostream& os);

private:
    void write_table(std::ostream& os);
    std::shared_ptr<struct table_frequencies_struct> shared_ptr_table_frequencies = std::make_shared<struct table_frequencies_struct>();
    std::shared_ptr<struct table_codes> table_codes;
    std::vector<unsigned char> data;
    int READ_BUFFER_SIZE;
    int WRITE_BUFFER_SIZE;

    int meta_size;
    int input_size;
    int output_size;

};

class Buffer{
public:
    Buffer();
    ~Buffer();
    void add_byte(unsigned char byte,std::ostream& os);
    void add_bits(unsigned char byte,int num_of_bits,std::ostream& os);
    void add_all_bits(unsigned char* bytes,int num_of_bits,std::ostream& os);
    void flush(std::ostream& os);
    
private:
    int BUFFER_SIZE;
    unsigned char* buffer;
    int byte_pointer;
    int bit_pointer;
};

