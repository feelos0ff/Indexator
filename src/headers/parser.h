#ifndef PARSER_H
#define PARSER_H

#include "definesincludes.h"
using namespace std;

class Parser{

public:

    static string NormalizeWord(string);

    static vector<string> NormalizeText(string);
    static vector<string> NormalizeMeta(string);

};

#endif // PARSER_H
