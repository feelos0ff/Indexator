/*
 * statistics.cpp
 *
 *  Created on: 05 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/statistics.h"

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

