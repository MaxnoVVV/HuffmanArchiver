#include "HuffmanArchiver.hpp"
#include <iostream>

HuffmanArchiver :: HuffmanArchiver()
{
    meta_size = 4;
    input_size = 0;
    output_size = 0;

    for(int i = 0;i<256;i++)
    {
        (*shared_ptr_table_frequencies)[i] = 0;
    }

    READ_BUFFER_SIZE = 4096;
    WRITE_BUFFER_SIZE = 4096;
}

HuffmanArchiver :: ~HuffmanArchiver()
{
}

void HuffmanArchiver :: read_data(std::istream& is)
{
    
    unsigned char* buffer = new unsigned char[READ_BUFFER_SIZE];

    while(is.read((char*)buffer,READ_BUFFER_SIZE))
    {
        for(int i = 0;i < is.gcount();i++) {
            data.push_back(buffer[i]);
            (*shared_ptr_table_frequencies)[buffer[i]]++;
        }
    }
    
    

    for(int i = 0;i < is.gcount();i++) {   
            data.push_back(buffer[i]);
            (*shared_ptr_table_frequencies)[buffer[i]]++;
    }

    input_size = data.size();

    delete [] buffer;
}

void HuffmanArchiver :: write_data(std::ostream& os)
{
    if(input_size != 0)
    {

    Buffer buffer;
    int bits_counter = 0;

    HuffmanTree tree(shared_ptr_table_frequencies);
    table_codes = tree.get_table();

    write_table(os);

    int size = (int)data.size();
    os.write(reinterpret_cast<char*>(&size),4);

    for(unsigned char c : data)
    {
        bits_counter += (*table_codes)[c][0];
        buffer.add_all_bits((*table_codes)[c]+1,(*table_codes)[c][0],os);
    }

    output_size = (bits_counter+7)/8;
    buffer.flush(os);
    
    }
    else 
    {
        meta_size = 0;
    }
    std::cout << input_size << std::endl << output_size << std::endl << meta_size << std::endl;
}

void HuffmanArchiver :: write_table(std::ostream& os) {
    for(int i = 0;i<256;i++) {
        unsigned char zero = 0;
        
        if((*table_codes)[i][0] == 0)
        {
            meta_size++;
            os.write((char*)&zero,1);
        }
        else 
        {
            meta_size += 1 + ((*table_codes)[i][0]+7)/8;
            os.write((char*)(*table_codes)[i],1 + ((*table_codes)[i][0]+7)/8);
        }
    }
}

Buffer :: Buffer()
{
    BUFFER_SIZE = 4096;
    byte_pointer = 0;
    bit_pointer = 0;
    buffer = new unsigned char[BUFFER_SIZE];

    for(int i = 0;i<BUFFER_SIZE;i++)
    {
        buffer[i] = 0;
    }
}

void Buffer :: add_all_bits(unsigned char* bytes,int num_of_bits,std::ostream& os) 
{
    for(int i = 0;i<(num_of_bits/8);i++)
    {
        add_byte(bytes[i],os);
    }

    if(num_of_bits%8!=0) {
        add_bits(bytes[num_of_bits/8],num_of_bits%8,os);
    }
    
}

void Buffer :: add_byte(unsigned char byte,std::ostream& os)
{
    buffer[byte_pointer++] += byte>>bit_pointer;
    if(byte_pointer == BUFFER_SIZE) flush(os);
    buffer[byte_pointer] += byte<<(8-bit_pointer);
}

void Buffer :: add_bits(unsigned char byte,int num_of_bits,std::ostream& os)
{
    if(bit_pointer + num_of_bits > 8)
    {
        buffer[byte_pointer++] += byte>>bit_pointer;
        if(byte_pointer == BUFFER_SIZE) flush(os);
        bit_pointer = (num_of_bits + bit_pointer - 8);
        buffer[byte_pointer] += byte<<(num_of_bits-bit_pointer);
        
    }
    else if(bit_pointer + num_of_bits == 8)
    {
        buffer[byte_pointer++] += byte >> bit_pointer;
        if(byte_pointer == BUFFER_SIZE) flush(os);
        bit_pointer = 0;
    }
    else
    {
        buffer[byte_pointer] += byte>>bit_pointer;
        bit_pointer+=num_of_bits;
    }
}

void Buffer :: flush(std::ostream& os)
{
    if(byte_pointer == 0 && bit_pointer == 0) 
    {
        return;
    }

    if(bit_pointer != 0)
    {
        os.write((char*)buffer,std::min(BUFFER_SIZE,byte_pointer+1));
    }
    else
    {
        os.write((char*)buffer,std::min(BUFFER_SIZE,byte_pointer));
    }
    
    delete [] buffer;
    buffer = new unsigned char[BUFFER_SIZE];

    for(int i = 0;i<BUFFER_SIZE;i++)
    {
        buffer[i] = 0;
    }

    byte_pointer = 0;
}

Buffer :: ~Buffer()
{
    delete [] buffer;
}