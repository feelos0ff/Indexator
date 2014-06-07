/*
 * filework.cpp
 *
 *  Created on: 05 июня 2014 г.
 *      Author: feelosoff
 */


#include "../headers/filework.h"

void FileWork::OpenRead(string fileName){
	_fin.open(fileName.c_str(), ios::binary);
}

void FileWork::OpenWrite(string fileName, bool append){
	if(append)
		_fout.open(fileName.c_str(), ios::app | ios::binary);
	else
		_fout.open(fileName.c_str(), ios::binary);
}

bool FileWork::IsEOF(){
	if(_fin)
		return false;
	return true;
}

unsigned long long FileWork::GetPos(){
	return _fout.tellp();
}

void FileWork::SetPos(unsigned long long pos){
	_fin.seekg(pos);
}

void FileWork::CloseRead(){
	_fin.close();
}
void FileWork::CloseWrite(){
	_fout.close();
}

void FileWork::WriteLine(string word, unsigned long long num){

	_fout << word << ' ' << num << endl;
}

pair<string, unsigned long long> FileWork::ReadLine(){
	pair<string, unsigned long long> result;
	_fin >> result.first  >> result.second;
	return result;
}

void FileWork::WriteIdxLine(string &data){
	unsigned int len = data.length();

	_fout.write((char*)&len, sizeof(unsigned int));
	_fout.write(data.c_str(), len);
}
string FileWork::ReadIdxLine(unsigned long long pos){
	string result;
	unsigned int len = 0;

	_fin.seekg(pos);
	_fin.read((char*)&len, sizeof(unsigned int));

	if(!len){
		cout << "WTF " << pos << endl;
		return result;
	}
	char *data = (char*)malloc(sizeof(char) * len);

	_fin.read(data, len);
	result = data;

	free(data);

	return result;
}


