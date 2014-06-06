#ifndef PARSER_H
#define PARSER_H

#include "definesincludes.h"
#include "checkrus.h"
using namespace std;
///< toDo шаблонный класс
class Parser{

public:

    static string NormalizeWord(string);

    static vector<string> NormalizeText(string);
    static vector<string> NormalizeMeta(string);

    static string UITS(unsigned long);
    static unsigned long STUI(string);

};

#endif // PARSER_H
