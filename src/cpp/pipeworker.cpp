/*
 * pipeworker.cpp
 *
 *  Created on: 08 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/pipework.h"

string Convert(const std::string& str, iconv_t conv){
    iconv(conv, 0, 0, 0, 0);

    const size_t buffer_size = 2048;
    char out[buffer_size];

    char* in_buf = (char*)str.c_str();
    size_t in_size = str.size();

    std::string result;

    while (in_size > 0){

        char* out_buf = out;
        size_t out_size = buffer_size;

        int n = iconv(conv, &in_buf, &in_size, &out_buf, &out_size);
        if (n < 0){
            break;
        }
        result.append(out, buffer_size - out_size);
    }
}

string PipeWork::ReadQuery() {
    if ( mkfifo ( INPUT_NAME, 0777 ) ) {
        perror ( "mkfifo" );
        return "";
    }

    printf ( "%s is created\n", INPUT_NAME );

    int fd = 0;

    /* Read input  */
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
	iconv_t conv = iconv_open("CP1251","UTF-8");

    return  Convert( _buf , conv);
}

void PipeWork::WriteQuery ( PostingList *p, vector<string> &words ) {
    string res;

    res = "[[";
    int len = words.size();

    if(!len)
    	words.push_back("asdasfads");


    for ( int i = 0; i < len; ++i ) {
        if ( i )
            res += ',';

        res += words[i];
    }

    res += "]";
    if(!p){
    	res = "empty";
    }
    else{
		list<unsigned long> *docId = p->GetPostingList();
		list<unsigned long>::iterator iter = docId->begin();

		for ( ; iter != docId->end(); iter++ ) {
			res += ',';
			res += Parser::UITS ( *iter );
			res += ",[-1]";
		}

		res += ']';
    }
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



