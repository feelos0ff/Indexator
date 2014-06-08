/*
 * posting.cpp
 *
 *  Created on: 04 июня 2014 г.
 *      Author: feelosoff
 */
#include "../headers/posting.h"

PostingList::PostingList ( Statistics *st ) {
    _st = st;
}

PostingList::~PostingList() {}

void PostingList::Add ( unsigned long docId, unsigned long ent ) {

    _docId.push_back ( docId );

    if ( ent )
        _posts[docId] = ent;
}

void PostingList::Merge ( unsigned long long pos, string fileName ) {
    PostingList * newPosting = new PostingList();

    newPosting->Load ( pos, fileName );
    Merge ( newPosting );

    delete newPosting;
}


void PostingList::Merge ( PostingList *secondPost ) {
    map<unsigned long , unsigned long >::iterator iter = secondPost->_posts.begin();

    for ( ; iter != secondPost->_posts.end(); iter++ ) {
        _posts[iter->first] = iter->second;
        _docId.push_back ( iter->first );
    }
}


unsigned long long PostingList::Dump ( string fileName ) {
    _fw.OpenWrite ( fileName, true );
    unsigned long long pos = _fw.GetPos();

    list<unsigned long long> dataForArchivate;
    map<unsigned long , unsigned long >::iterator iter = _posts.begin();

    unsigned long long lastDocId = 0;
    unsigned long long lastPointEnt = 0;

    for ( ; iter != _posts.end(); iter++ ) {

        for ( int i = 0; i < 2; ++i ) {
            unsigned long long data = 0;

            switch ( i ) {
                case 0:
                    data = iter->first - lastDocId;
                    lastDocId = iter->first;
                    break;

                case 1:
                    data = iter->second;
                    break;
            }

            dataForArchivate.push_back ( data );
        }
    }


    string results = Archivate::Decode ( dataForArchivate );

    if ( _st )
        _st->AddArc ( dataForArchivate.size() * sizeof ( unsigned long ), results.length() );

    _fw.WriteIdxLine ( results );
    _fw.CloseWrite();

    return pos;
}


unsigned long PostingList::Length() {
    return _docId.size();
}


unsigned long PostingList::LengthEnt ( unsigned long docId ) {
    return _posts[docId];
}

void PostingList::Load ( unsigned long long pos, string fName ) {
    _fw.OpenRead ( fName );
    Load ( pos );
    _fw.CloseRead();
}

void PostingList::Load ( unsigned long long pos ) {
    string data = _fw.ReadIdxLine ( pos );

    list<unsigned long long> *rawPost = Archivate::Encode ( data );
    list<unsigned long long>::iterator iter = rawPost->begin();

    unsigned long docId = 0;
    unsigned long  entrance = 0;

    _posts.clear();
    _docId.clear();

    for ( int i = 0; iter != rawPost->end(); iter++, i = ( i + 1 ) % 2 ) {
        switch ( i ) {
            case 0:
                docId += *iter;
                break;

            case 1:
                entrance = *iter;
                break;
        }

        _posts[docId] = entrance;
        _docId.push_back ( docId );
    }

    delete rawPost;
}


bool PostingList::IsExist ( unsigned long docId ) {

    if ( _posts.end() ==  _posts.find ( docId ) )
        return false;

    return true;
}



