/*
 * parser.cpp
 *
 *  Created on: 05 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/parser.h"
///< toDo запилить стеммер именно сюда
string Parser::NormalizeWord(string word){
	unsigned long len = word.length();

	for(int i = 0; i < len; ++i)
		word[i] = tolower(word[i]);

	return word;
}

vector<string> Parser::NormalizeText(string txt){
	unsigned long len = txt.length();

	vector<string> result;
	string word;

	for(int i = 0; i < len; ++i){
		if(isalnum(txt[i]))
			word += txt[i];

		else if(!word.empty()){
				result.push_back(NormalizeWord(word));

				word = "";
		}
	}
	if(!word.empty())
		result.push_back(NormalizeWord(word));

	return result;
}
vector<string> Parser::NormalizeMeta(string txt){
	long posB = 0, posE = 0;
	vector<string> result;

	while(posB >= 0 && posB != txt.length()){
		posB = txt.find(":\"\"",posE) + 3;
		posE = txt.find("\"", posB);

		vector<string> meta = NormalizeText(txt.substr(posB, posE-posB));

		unsigned long len = meta.size();

		for(int i = 0; i < len; ++i)
			result.push_back(meta[i]);
	}
	return result;
}

string Parser::UITS(unsigned long num){
	stringstream ss;
	string result;

	ss << num;
	result << ss;

	return result;
}

unsigned long Parser::STUI(string num){
	stringstream ss;
	unsigned int result;

	ss << num;
	result << ss;

	return result;
}



