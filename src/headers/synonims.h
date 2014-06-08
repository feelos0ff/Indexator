/*
 * synonims.h
 *
 *  Created on: 08 июня 2014 г.
 *      Author: feelosoff
 */

#ifndef SYNONIMS_H_
#define SYNONIMS_H_
#include "definesincludes.h"
#include "parser.h"
#include "filework.h"

class Synonims{

	vector< vector<string> > _synonims;
	map<string, int> _tbl;

	string _fileName;

public:
	Synonims();
	vector<string>* GetSynonims(string);
};




#endif /* SYNONIMS_H_ */
