#ifndef FILEWORK_H
#define FILEWORK_H
#include "definesincludes.h"

class FileWork{
public:

    void OpenRead(string);
    void OpenWrite(string);

    bool IsEOF();

    unsigned int GetPos();
    void SetPos(unsigned long long);

    void CloseRead();
    void CloseWrite();

    void WriteLine(string, unsigned int);
    pair<string, unsigned int> ReadLine();

    void WriteIdxLine(string);
    string ReadIdxLine(unsigned long long);


};

#endif // FILEWORK_H
