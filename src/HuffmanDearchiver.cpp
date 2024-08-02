#include "HuffmanDearchiver.hpp"
#include <istream>

HuffmanDearchiver :: HuffmanDearchiver() 
{
    input_size = 0;
    output_size = 0;
    meta_size = 4;
}

unsigned char get_bit(unsigned char byte,int pos)
{
    return (byte >> (7-pos))%2;
}

void HuffmanDearchiver :: read_table(std::istream& is)
{
    for(int i = 0;i<256;i++)
    {
        HuffmanTrieNode* node = trie.get_root(); 
        char num_of_bits = 0;
        unsigned char bits_readed = 0;
        char byte = 0;
        
        is.read(&num_of_bits,1);

        if(static_cast<unsigned char>(num_of_bits) == 0) 
        {
            meta_size++;
            continue;
        }
        else
        {
            meta_size += 1 + (static_cast<unsigned char>(num_of_bits)+7)/8;
        }

        for(int q = 1;q <= (static_cast<unsigned char>(num_of_bits)+7)/8;q++)
        {
            is.read(&byte,1);

            for(int j = 0;j<=7;j++)
            {
                bits_readed++;
                node->make_child_node(get_bit(static_cast<unsigned char>(byte),j));
                node = node->get_child(get_bit(static_cast<unsigned char>(byte),j));
                
                if(bits_readed == static_cast<unsigned char>(num_of_bits))
                {
                    node->make_end();
                    node->add_char((unsigned char)i);
                    break;
                }
            }
        }
    }

}


void HuffmanDearchiver :: read_data(std::istream& is)
{
    int total_num_of_chars = 0;
    int current_num_of_chars = 0;

    if(is.peek() == EOF) {
        return;
    }

    char* int_buffer = new char[4];

    read_table(is);

    is.read(int_buffer,4);

    total_num_of_chars = static_cast<unsigned char>(int_buffer[0]) + static_cast<unsigned char>(int_buffer[1])*256 + static_cast<unsigned char>(int_buffer[2])*256*256 + static_cast<unsigned char>(int_buffer[3])*256*256*256;
    unsigned char* buffer = new unsigned char[READ_BUFFER_SIZE];
    HuffmanTrieNode* node = trie.get_root();

    bool eof = false;

    while(is.read((char*)buffer,READ_BUFFER_SIZE) && !eof)
    {
        input_size += is.gcount();

        for(int i = 0;i < is.gcount() && !eof;i++) 
        {
            for(int j = 0;j<8 && !eof;j++)
            {
                node = node->get_child(get_bit(buffer[i],j)); 

                if(node->is_end())
                {
                    data.push_back(node->get_char());
                    node = trie.get_root(); 
                    current_num_of_chars++;
                }
                
                if(current_num_of_chars == total_num_of_chars)
                {
                    eof = true;
                    break;
                }
            }
        }
    }

    input_size += is.gcount();

    for(int i = 0;i < is.gcount() && !eof;i++) 
        {
            for(int j = 0;j<8 && !eof;j++)
            {
                node = node->get_child(get_bit(buffer[i],j)); 

                if(node->is_end())
                {
                    data.push_back(node->get_char());
                    node = trie.get_root(); 
                    current_num_of_chars++;
                }
                
                if(current_num_of_chars == total_num_of_chars)
                {
                    eof = true;
                    break;
                }
            }
        }

    delete [] int_buffer;
    delete [] buffer;
}



void HuffmanDearchiver :: write_data(std::ostream& os)
{
    if(input_size != 0) 
    {
        for(int i = 0;i*WRITE_BUFFER_SIZE <(int) data.size();i++)
        {
            output_size += std::min(WRITE_BUFFER_SIZE,(int)data.size() - i*WRITE_BUFFER_SIZE);
            os.write(reinterpret_cast<const char *>(&data[0]+WRITE_BUFFER_SIZE*i),std::min(WRITE_BUFFER_SIZE,(int)data.size() - i*WRITE_BUFFER_SIZE));
        }
    }
    else
    {
        meta_size = 0;
    }

    std::cout << input_size << std::endl << output_size << std::endl << meta_size << std::endl;
}

HuffmanDearchiver :: ~HuffmanDearchiver()
{
    
}