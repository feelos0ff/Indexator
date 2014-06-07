/*
 * statistics.cpp
 *
 *  Created on: 05 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/statistics.h"

void Statistics::AddArc(unsigned long long nums, unsigned long long bytes){
	_numsInArc += nums;
	_byteInArc += bytes;
}

long double Statistics::GetArcStat(){
	long double res = 0;
	res = (long double)_numsInArc / (long double) _byteInArc;
	return res;
}

void Statistics::AddWord(string word, unsigned long txtNum){
	_wordDict[word]++;
	_txtDict[txtNum]++;
	_wc++;
}

unsigned long Statistics::WordCount(){
	return _wc;
}

bool Statistics::IsStopWord(string word){
	double freq = (double)_wordDict[word] / (double)_wc;
	return (_stopLine < freq);
}

double Statistics::GetAverageLen(){
	return ((double)_wc / (double)_txtDict.size());
}

unsigned long Statistics::GetCountTxt(){
	return _txtDict.size();
}
unsigned long Statistics::GetTxtLen(unsigned long txtNum){
	return _txtDict[txtNum];
}
void Statistics::SetStopLine(double eps){
	if(eps <= 1)
		_stopLine = eps;
}

void Statistics::Dump(string fileName){
	FileWork fw;
	fw.OpenWrite(fileName);

	map <string, unsigned long>::iterator wordIter = _wordDict.begin();
	map <unsigned long, unsigned long>::iterator txtIter = _txtDict.begin();
	///< toDo исправить на нормальную запись в файл
	fw.WriteLine(Parser::UITS(_wordDict.size()),_txtDict.size());

	for(;wordIter != _wordDict.end(); wordIter++)
		fw.WriteLine(wordIter->first, wordIter->second);

	for(;txtIter != _txtDict.end(); txtIter++)
		fw.WriteLine(Parser::UITS(txtIter->first), txtIter->second);

	fw.CloseWrite();
}

void Statistics::Load(string fileName){
	FileWork fw;
	///< toDo исправить на нормальную запись в файл
	pair<string, unsigned long> data;

	data = fw.ReadLine();

	unsigned long wordLen = Parser::STUI(data.first);
	unsigned long txtLen = data.second;

	for(;wordLen; wordLen--){
		data =fw.ReadLine();
		_wordDict.insert(data);
		_wc += data.second;
	}
	for(;txtLen; txtLen++){
		data =fw.ReadLine();
		_txtDict[Parser::STUI(data.first)] = data.second;
	}
}

