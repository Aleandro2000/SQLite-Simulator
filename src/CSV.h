//Realized by Aleandro 2000

#ifndef SRC_FILE
#define SRC_FILE

#include <bits/stdc++.h>

using namespace std;

class CSV
{
    vector<vector<string>> array;
    size_t lines=0;
public:
    ~CSV();
    void CSVreader(string);
    vector<vector<string>> getArray();
    size_t getLines();
};

CSV::~CSV()
{}

void CSV::CSVreader(string file)
{
    ifstream in(file);
    string line, field;

    vector<string> v;
	this->lines=0;

    this->array.clear();

    while (getline(in, line))
    {
        v.clear();
        stringstream ss(line);
		++this->lines;
        while (getline(ss, field, ','))
            v.push_back(field);
        this->array.push_back(v);
    }
	in.close();
}

size_t CSV::getLines()
{
    return this->lines;
}

#endif