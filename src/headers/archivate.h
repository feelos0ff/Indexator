#ifndef ARCHIVATE_H
#define ARCHIVATE_H
#include "definesincludes.h"

class Archivate{
public:
    static list<int> Encode(string);
    static string Decode(list<int>);
};

#endif // ARCHIVATE_H
