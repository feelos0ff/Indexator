/*
 * synonims.cpp
 *
 *  Created on: 08 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/synonims.h"


Synonims::Synonims(){
	FileWork fw;
	fw.OpenRead("synonims.txt");

	while(!fw.IsEOF()){
		string line = fw.GetLine();
		vector<string> words = Parser::ParseSyn(line);

		_synonims.push_back(words);
		int len = words.size();

		for(int i = 0; i < len; ++i)
			_tbl[words[i]] = _synonims.size() - 1;
	}
	fw.CloseRead();
}

vector<string>* Synonims::GetSynonims(string word){
	return &_synonims[ _tbl[word] ];
}



