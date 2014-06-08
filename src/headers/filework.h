#ifndef FILEWORK_H
#define FILEWORK_H
#include "definesincludes.h"

class FileWork {

    ifstream _fin;
    ofstream _fout;

public:

    void OpenRead ( string );
    void OpenWrite ( string fileName, bool append = false );

    bool IsEOF();

    unsigned long long GetPos();
    void SetPos ( unsigned long long );

    void CloseRead();
    void CloseWrite();

    void WriteLine ( string, unsigned long long );
    pair<string, unsigned long long> ReadLine();

    void WriteIdxLine ( string& );
    string ReadIdxLine ( unsigned long long );
};

#endif // FILEWORK_H
