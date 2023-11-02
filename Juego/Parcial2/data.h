#ifndef DATA_H
#define DATA_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace::std;

class Data
{
public:
    Data(string);

    void NewData(string, string, int, int);
    void Winner_Historial();
    void WriteData();

    void DeleteLast();
    string GetField(string, string);
    ~Data();

private:
    string File, Name;
};

#endif // DATA_H
