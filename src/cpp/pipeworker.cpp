/*
 * pipeworker.cpp
 *
 *  Created on: 08 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/pipework.h"

string PipeWork::ReadQuery() {
    if ( mkfifo ( INPUT_NAME, 0777 ) ) {
        perror ( "mkfifo" );
        return "";
    }

    printf ( "%s is created\n", INPUT_NAME );

    int fd = 0;

    /* Read input JSON */
    if ( ( fd = open ( INPUT_NAME, O_RDONLY ) ) <= 0 ) {
        perror ( "open" );
        return "";
    }

    printf ( "%s is opened\n", INPUT_NAME );

    memset ( _buf, '\0', BUFSIZE );
    read ( fd, _buf, BUFSIZE - 1 );

    perror ( "read" );
    close ( fd );

    remove ( INPUT_NAME );

    return string ( _buf );
}

void PipeWork::WriteQuery ( PostingList *p, vector<string> &words ) {
    string res;

    res = "[[";
    int len = words.size();

    for ( int i = 0; i < len; ++i ) {
        if ( i )
            res += ',';

        res += words[i];
    }

    res += "]";

    list<unsigned long> *docId = p->GetPostingList();
    list<unsigned long>::iterator iter = docId->begin();

    for ( ; iter != docId->end(); iter++ ) {
        res += ',';
        res += Parser::UITS ( *iter );
        res += ",[-1]";
    }

    res += ']';

    int fd = 0;
    /* Discard old snippets */
    FILE* f = fopen ( OUTPUT_NAME, "w" );
    fclose ( f );

    /* Write output JSON */
    if ( ( fd = open ( OUTPUT_NAME, O_WRONLY ) ) <= 0 ) {
        perror ( "open" );
    }

    write ( fd, res.c_str(), res.length() );
    perror ( "write" );
    close ( fd );
}



