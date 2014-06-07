#include "../headers/index.h"

using namespace std;

void Index::CreateIndex(int stIdx, int endIdx){
    int len = _db.GetCountTxt();

    if(!endIdx)
    	endIdx = len;

    for(int i = stIdx; i < endIdx; i += _maxCountOfText)
        AddToIndex(i, min(i + _maxCountOfText, endIdx));

    system("iconv -f cp1251 -t utf-8 *.dict | sort -t ' ' -h | iconv -f utf-8 -t cp1251 > dict.dict");
    system("rm *_tmp.dict");

    Merge("dict.dict");
    _stat.Dump("index.stat");
}


void Index::AddToIndex(int stIdx, int endIdx){
    FileWork fwIdx;

    string fileName = Parser::UITS(stIdx);

    _fw.OpenWrite(fileName + "_tmp.dict");
    map<string, map<unsigned int,list<int> > > dictionary;

    for(int txtNum = stIdx; txtNum < endIdx; txtNum++){
        int pos = 0;

        vector<string> processedText = Parser::NormalizeMeta(_db.GetMetaData(txtNum));
        int len = processedText.size();

        for(int wordNum = 0; wordNum < len; ++wordNum){
        	if(processedText[wordNum] == "")
        		continue;
            dictionary[ processedText[wordNum] ][txtNum].push_back(-1);
            _stat.AddWord(processedText[wordNum], txtNum);
        }

        processedText = Parser::NormalizeText(_db.GetNewsText(txtNum));
        len = processedText.size();

        for(int wordNum = 0; wordNum < len; ++wordNum){
           	if(processedText[wordNum] == "")
            	continue;

        	dictionary[ processedText[wordNum] ][txtNum].push_back(pos);
            pos += processedText[wordNum].length() + 1;

            _stat.AddWord(processedText[wordNum], txtNum);
        }

        _db.SetPrepText(processedText, txtNum);
    }
    map<string, map<unsigned int,list<int> > >::iterator wordIter = dictionary.begin();
    unsigned long long pos = 0;

    for(; wordIter != dictionary.end(); wordIter++){
    	map<unsigned int,list<int> >::iterator docIter = wordIter->second.begin();
    	PostingList posts;

    	for(;docIter != wordIter->second.end(); docIter++)
    		posts.Add(docIter->first, docIter->second);

    	pos = posts.Dump("index_tmp.idx");
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

        if(targetLine.first == "")
        	continue;

        if(currentLine.first == targetLine.first)
        	currentPosts.Merge(targetLine.second, "index_tmp.idx");

        else{
        	if(currentLine.first != "" ){
        		_fw.WriteLine(currentLine.first,pos);
        		pos = currentPosts.Dump("index.idx");
        	}
            currentLine = targetLine;
            currentPosts.Load(currentLine.second, "index_tmp.idx");
       }
    }
    if(currentLine.first != "" ){
    	_fw.WriteLine(currentLine.first,pos);
    	pos = currentPosts.Dump("index.idx");
    }

    _fw.CloseRead();
    _fw.CloseWrite();

 //   system("rm index_tmp.idx dict.dict");
}


void IndexTable::LoadIndex(string fileName){
	_stat.Load("index.stat");
	FileWork fw;
    fw.OpenRead(fileName);
    while(!fw.IsEOF())
        _tbl.insert(fw.ReadLine());

    fw.CloseRead();
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
