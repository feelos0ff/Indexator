/*
 * pipework.h
 *
 *  Created on: 08 июня 2014 г.
 *      Author: feelosoff
 */

#ifndef PIPEWORK_H_
#define PIPEWORK_H_
#include "definesincludes.h"
#include "posting.h"
#include "parser.h"

class PipeWork{

	char _buf[BUFSIZE];

public:

	string ReadQuery();
	void WriteQuery(PostingList*, vector<string>&);

};


#endif /* PIPEWORK_H_ */
