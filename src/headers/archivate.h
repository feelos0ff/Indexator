#ifndef ARCHIVATE_H
#define ARCHIVATE_H
#include "definesincludes.h"

class Archivate{
public:
    static list<unsigned long long>* Encode(string&);
    static string Decode(list<unsigned long long>&);
};

#endif // ARCHIVATE_H
