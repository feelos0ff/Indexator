/*
 * dbworker.cpp
 *
 *  Created on: 05 июня 2014 г.
 *      Author: feelosoff
 */

#include "../headers/dbworker.h"
using namespace std;

DBWorker::DBWorker(){
	const char *conninfo = "dbname = search_db password = search user = feelosoff";
	_conn = PQconnectdb(conninfo);

	if (PQstatus(_conn) != CONNECTION_OK){

		cout <<"Connection to database failed: " << PQerrorMessage(_conn) << endl;
        exit(0);
	}
}

DBWorker::~DBWorker(){
	PQfinish(_conn);
}

string DBWorker::Select(string col, unsigned int num){
	PGresult   *res;
	string result;
	char query[256];

	PQexec(_conn, "set names \'win-1251\';");
	sprintf(query, "SELECT %s FROM news WHERE id = %d", col.c_str(), num);

	res = PQexec(_conn, query);

	int nnews_text = PQntuples(res);

	if(nnews_text)
		result = PQgetvalue(res, 0, 0);

	PQclear(res);
	return result;
}

string DBWorker::GetNewsText(unsigned int num){
	return Select("news_text", num);
}

string DBWorker::GetPrepText(unsigned int num){
	return Select("data_type", num);
}

string DBWorker::GetMetaData(unsigned int num){
	return Select("json", num);
}

unsigned long DBWorker::GetCountTxt(){
	PGresult *res = PQexec(_conn, "select id FROM news");
   	unsigned long rec_count = PQntuples(res);
   	PQclear(res);
   	return rec_count;
}

void DBWorker::SetPrepText(vector<string>& txt, unsigned int num){
	string query;
	stringstream ss;
	string prepTxt = "";
	int len = txt.size();
	for(int i = 0; i < len; ++i){
		prepTxt += txt[i];

		if(i != len -1)
			prepTxt += ' ';
	}
	PQexec(_conn, "set names \'win-1251\';");
	ss << "UPDATE news set data_type = " << prepTxt << " WHERE id = " << num << ");";
	ss >> query;

	PQexec(_conn, query.c_str()) ;
}
