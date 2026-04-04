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
            result += input[i];
            result += to_string(count);
            count = 1;
        }
    }
    return result;
}


