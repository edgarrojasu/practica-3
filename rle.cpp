#include <iostream>
using namespace std;

string rleCompress(const string& input)
{
    string result = "";
    int count = 1;
    for (int i = 0; i < input.length(); i++)
    {
        if (i + 1 < input.length() && input[i] == input[i + 1])
        {
            count++;
        }
        else
        {
            result += input[i];
            result += to_string(count);
            count = 1;
        }
    }
    return result;
}

string rleCompressPtr(const char* input)
{
    string result = "";
    int count = 1;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == input[i + 1])
        {
            count++;
        }
        else
        {
            result += to_string(count); // número primero
            result += input[i];         // carácter después
            count = 1;
        }
    }
    return result;
}

string rleDecompress(const string& input)
{
    string result = "";
    int i = 0;
    while (i < input.length())
    {
        // Leer el número
        int count = 0;
        while (i < input.length() && input[i] >= '0' && input[i] <= '9')
        {
            count = count * 10 + (input[i] - '0');
            i++;
        }
        // Leer el carácter
        if (i < input.length())
        {
            for (int j = 0; j < count; j++)
            {
                result += input[i];
            }
            i++;
        }
    }
    return result;
}

string rleDecompressPtr(const char* input)
{
    string result = "";
    int i = 0;
    while (input[i] != '\0')
    {
        // Leer el número
        int count = 0;
        while (input[i] >= '0' && input[i] <= '9')
        {
            count = count * 10 + (input[i] - '0');
            i++;
        }
        // Leer el carácter
        if (input[i] != '\0')
        {
            for (int j = 0; j < count; j++)
            {
                result += input[i];
            }
            i++;
        }
    }
    return result;
}
