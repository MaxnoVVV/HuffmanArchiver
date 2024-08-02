#include "HuffmanArchiver.hpp"
#include "HuffmanDearchiver.hpp"
#include "HuffmanException.hpp"
#include <iostream>
#include <cstring>
#include <fstream>

int main(int argc, char* argv[])
{
    char* input_file = nullptr;
    char* output_file = nullptr;
    char* command = nullptr;

    try
    {

    if(argc != 6)
    {
        throw HuffmanInputException("Invalid number of arguments");
    }

    for(int i = 0;i<argc;i++) 
    {
        if(strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
        {
            input_file = argv[i+1];
        }
        else if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
        {
            output_file = argv[i+1];
        }
    }

    if(input_file == nullptr || output_file == nullptr) throw HuffmanInputException("No input or output file");

    for(int i = 0;i<argc;i++) 
    {
        if(strcmp(argv[i], "-c") == 0)
        {
            command = argv[i];
        }
        else if(strcmp(argv[i], "-u") == 0)
        {
            if(command != nullptr)
            {
                throw HuffmanInputException("Ambigious arguments");
            }
            else 
            {
                command = argv[i];
            }
        }
    }

    if(strcmp(command, "-c") == 0)
    {
        HuffmanArchiver huffman;

        std::ifstream is;
        is.open(input_file);

        if(!is.is_open())
        {
            throw HuffmanInputException("Input file not found");
        }

        huffman.read_data(is);
        is.close();

        std::ofstream os;
        os.open(output_file);
        huffman.write_data(os);
        os.close();
    }
    else if(strcmp(command, "-u") == 0)
    {
        HuffmanDearchiver huffman;
        
        std::ifstream is;
        is.open(input_file);

        if(!is.is_open())
        {
            throw HuffmanInputException("Input file not found");
        }

        huffman.read_data(is);
        is.close();

        std::ofstream os;
        os.open(output_file);
        huffman.write_data(os);
        os.close();

    }
    else
    {
        throw HuffmanInputException("No mode flag");
    }

    }
    catch(std::exception& e)
    {
       std::cout << "ERROR: " << e.what() << std::endl;
    }
}