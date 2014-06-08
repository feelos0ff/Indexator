#include <iostream>
#include "../headers/definesincludes.h"
#include "../headers/query.h"
#include "../headers/index.h"
#include "../headers/pipework.h"
using namespace std;

int main(int argc, char *argv[])
{

	if(! setlocale (LC_CTYPE , "ru_RU.cp1251")){
		cout << "locale problems" << endl;
		exit(0);
	}
	if(argc > 1){
		cout << "Unknown parameters" << endl;
		return 0;
	}

	Index idx;
	IndexTable tbl;

	time_t st = time(NULL);

	if(!argc || argv[1] == "-i"){
		idx.CreateIndex(1, 200);
		return 0;
	}
	else if(argv[1] == "-l"){
		tbl.LoadIndex("index.dict");
	}
	else{
		cout << "Unknown parameters" << endl;
		return 0;
	}

	cout << "Archivates: " <<tbl.GetStat()->GetArcStat() << endl;
	cout << "Load Time: " << (time(NULL) - st)  << endl;

	Query query;
	query.SetTable(&tbl);

	PipeWork pipe;

    while(true){

		PostingList *p = query.ExecQuery(pipe.ReadQuery());

		if(p)
			cout << p->Length() << endl;
		else
			cout << 0 << endl;

		delete p;
	}
	return 0;
}

