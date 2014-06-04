#include "../headers/index.h"

using namespace std;

void Index::CreateIndex(int stIdx, int endIdx){
    int len = _db.GetCountTxt();
    for(int i = 0; i < len; i += _maxCountOfText)
        AddToIndex(i, i + _maxCountOfText - 1);

    system("sort *.dict > dict.dict");
    system("rm *_tmp.dict");

    Merge("dict.dict");
}


void Index::AddToIndex(int stIdx, int endIdx){
    FileWork fwIdx;

    stringstream ss;
    string fileName;

    ss << stIdx;
    ss >> fileName;

    _fw.OpenWrite(fileName + "_tmp.dict");
    map<string, map<unsigned int,list<int> > > dictionary;

    for(int txtNum = stIdx; txtNum < endIdx; txtNum++){
        int pos = 0;

        vector<string> processedText = Parser::NormalizeMeta(_db.GetMetaData(txtNum));
        int len = processedText.size();

        for(int wordNum = 0; wordNum < len; ++wordNum)
            dictionary[ processedText[wordNum] ][txtNum].push_back(-1);

        processedText = Parser::NormalizeText(_db.GetNewsText(txtNum));
        int len = processedText.size();

        for(int wordNum = 0; wordNum < len; ++wordNum){
        	dictionary[ processedText[wordNum] ][txtNum].push_back(pos);
            pos += processedText[wordNum].length() + 1;
        }

        _db.SetPrepText(processedText);
    }
    map<string, map<unsigned int,list<int> > >::iterator wordIter = dictionary.begin();
    unsigned long long pos = 0;

    for(; wordIter != dictionary.end(); wordIter++){
    	map<unsigned int,list<int> >::iterator docIter = wordIter->second.begin();
    	PostingList posts;

    	for(;docIter != wordIter->second.end(); docIter++)
    		posts.Add(docIter->first, docIter->second);

    	pos += posts.Dump("index" + "_tmp.idx");
    	_fw.WriteLine(wordIter->first, pos);
    }

    _fw.CloseWrite();
}


void Index::Merge(string fileName){
    FileWork fwIdx;

    _fw.OpenRead( fileName);
    _fw.OpenWrite("index.dict");

    pair<string, unsigned long long> currentLine = _fw.ReadLine();
    PostingList currentPosts;

    currentPosts.Load(currentLine.second, "index_tmp.idx");

    unsigned long long pos = 0;

    while(!_fw.IsEOF()){
        pair<string, unsigned int> targetLine = _fw.ReadLine();

        if(currentLine.first == targetLine.first)
        	currentPosts.Merge(targetLine.second);

        else{
        	pos += currentPosts.Dump("index.idx");
            _fw.WriteLine(currentLine.first,pos);

            currentLine = targetLine;
            currentPosts.Load(currentLine.second, "index_tmp.idx");
       }
    }

	pos += currentPosts.Dump("index.idx");
    _fw.WriteLine(currentLine.first,pos);

    _fw.CloseRead();
    _fw.CloseWrite();

    system("rm index_tmp.idx dict.dict");
}


void IndexTable::LoadIndex(string fileName){
    FileWork fw;
    fw.OpenRead(fileName);
    while(!fw.IsEOF())
        _tbl.insert(fw.ReadLine());
}


PostingList* IndexTable::FindPos(string word){
	map<string, unsigned long long>::iterator iter = _tbl.find(word);
	PostingList *res = NULL;

	if(iter != _tbl.end()){
		res = new PostingList();
		res->Load(iter->second, "index.idx");
	}

	return res;
}
