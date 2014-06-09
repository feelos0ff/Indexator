/*
 * archivate.cpp
 *
 *  Created on: 05 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/archivate.h"

list<unsigned long long>* Archivate::Encode ( string &data ) {
    list<unsigned long long> *res = new list<unsigned long long>;

    unsigned long len = data.length();
    unsigned long long val = 0;

    for ( int i = 0; i < len; ++i ) {
        if ( ( ( unsigned char ) data[i] ) > 0x7f ) {
            val += ( (unsigned char )data[i]) & 0x7f;
            val = val << 7;
        }

        else {
            res->push_back ( ( unsigned char ) data[i] + val );
            val = 0;
        }
    }

    return res;
}


string Archivate::Decode ( list<unsigned long long>& data ) {
    list<unsigned long long>::iterator iter = data.begin();
    string res;

    for ( ; iter != data.end(); iter++ ) {
        unsigned long long val = *iter;

        while ( val > 0x7f ) {
            res += char ( 0x80 + ( val & 0x7f ) );
            val = val >> 7;
        }

        res += char ( val );
    }

    return res;
}



