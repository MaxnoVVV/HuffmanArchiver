#pragma once
struct table_frequencies_struct
{
    table_frequencies_struct()
    {
        table = new int[256];

        for(int i = 0;i<256;i++)
        {
            table[i] = 0;
        }
    }

    ~table_frequencies_struct()
    {
        delete [] table;
    }

    int& operator[](int idx)
    {
        return table[idx];
    }

    int* table;
};

struct table_codes
{
    ~table_codes()
    {
        for(int i = 0;i<256;i++)
        {
            delete [] table[i];
        }
        delete [] table;
    }
    
    table_codes()
    {
        table = new unsigned char*[256];
    }

    unsigned char*& operator[](int idx)
    {
        return table[idx];
    }

    unsigned char** table;

};