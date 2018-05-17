#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void printDictionary(multimap<string, size_t> mapa)
{
    for(multimap<string, size_t>::iterator it = mapa.begin();it!=mapa.end();++it)
    {
        cout<<it->first<<":\t"<<it->second<<endl;
    }
}

multimap<string, size_t> parseStr(string& s)
{
    multimap<string, size_t> Bank;

    for(int i=0;i<s.size();i++)
    {
        if(s[i]==' ' || s[i]=='"' || s[i]=='\n')
        {
            s.erase(i,1);
            i--;
        }
    }
    //cout<<"After erase: "<<s<<endl;

    std::string delimiter = ",";
    size_t pos = 0;
    size_t i=1;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        Bank.insert(pair<string, size_t>(token, i));
        s.erase(0, pos + delimiter.length());
        i++;
    }
    token= s.substr(0, pos);
    Bank.insert(pair<string, size_t>(token, i));
    i=0;

    for(multimap<string, size_t>::iterator it = Bank.begin();it!=Bank.end();++it)
    {
        it->second = ++i;
    }

    return Bank;
}

size_t Calculate(multimap<string, size_t> dictionary, size_t shift)
{
    size_t result=0;
    size_t sum=0;

    for(multimap<string, size_t>::iterator it = dictionary.begin(); it!= dictionary.end();++it)
    {
        for(auto i : it->first)
        {
            sum+=(i-shift);
        }
        sum*=it->second;
        result+=sum;
        sum=0;
    }
    return result;
}

int main()
{
    size_t shiftInASCII = 64;
    string file_content;
    //ifstream file("input_for_calculate.txt");
    //ifstream file("Input.txt");
    ifstream file("names.txt");
    if(!file.is_open())
    {
        cout<<"File wasn't opened"<<endl;
    }
    else
    {
        file_content = { istreambuf_iterator<char>(file), istreambuf_iterator<char>() };
        file.close();
    }

    multimap<string, size_t> dictionary = parseStr(file_content);
    //printDictionary(dictionary);
    size_t result =Calculate(dictionary, shiftInASCII);
    cout<<"THE RESULT IS: "<<result<<endl;
    return 0;
}
