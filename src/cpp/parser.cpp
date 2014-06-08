/*
 * parser.cpp
 *
 *  Created on: 05 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/parser.h"


string Parser::NormalizeWord ( string word ) {
    unsigned long len = word.length();

    for ( int i = 0; i < len; ++i ) {
        if ( isspace ( ( unsigned char ) word[i] ) )
            word[i] = '_';

        if ( isalpha ( ( unsigned char ) word[i] ) )
            word[i] = tolower ( ( unsigned char ) word[i] );
    }

    string tmp = word;
    char *res = DrawStem ( word.c_str() );

    if ( !res )
        return word;

    word = res;
    free ( res );
    int pos = word.find ( '|' );

    if ( pos < 0 )
        pos = word.length();

//	cout << tmp <<" " << word << " " << word.length() << " " << pos << endl;
    return word.substr ( 0, pos );
}

vector<string> Parser::NormalizeText ( string txt ) {
    unsigned long len = txt.length();

    vector<string> result;
    string word = "";

    for ( int i = 0; i < len; ++i ) {
        if ( isalnum ( ( unsigned char ) txt[i] ) )
            word += txt[i];

        else if ( !word.empty() ) {
            result.push_back ( NormalizeWord ( word ) );
            word = "";
        }
    }

    if ( !word.empty() )
        result.push_back ( NormalizeWord ( word ) );

    return result;
}
vector<string> Parser::NormalizeMeta ( string txt ) {
    long posB = 0, posE = 0;
    vector<string> result;
    string title = "title\":\"";

    while ( true ) {
        posB = txt.find ( ":\"", posE );

        if ( posB < 0 || posB == txt.length() )
            break;

        posB += 2;
        posE = txt.find ( "\"", posB );

        string word = txt.substr ( posB, posE - posB );
        unsigned long len = word.length();

        for ( int i = 0; i < len; ++i ) {
            if ( isspace ( word[i] ) )
                word[i] = '_';

            if ( isalpha ( word[i] ) )
                word[i] = tolower ( word[i] );
        }

        result.push_back ( word );
    }

    return result;
}

string Parser::UITS ( unsigned long num ) {
    stringstream ss;
    string result;

    ss << num;
    ss >> result;

    return result;
}

unsigned long Parser::STUI ( string num ) {
    stringstream ss;
    unsigned int result;

    ss << num;
    ss >> result;

    return result;
}



