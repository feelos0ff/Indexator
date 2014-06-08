#include <iostream>
#include "../headers/definesincludes.h"
#include "../headers/query.h"
#include "../headers/index.h"

using namespace std;

int main()
{

	if(! setlocale (LC_CTYPE , "ru_RU.cp1251")){
		cout << "locale problems" << endl;
		exit(0);
	}

	Index idx;
	idx.CreateIndex(1, 200);
	IndexTable tbl;
	time_t st = time(NULL);
	tbl.LoadIndex("index.dict");

	cout << "Archivates: " <<tbl.GetStat()->GetArcStat() << endl;
	cout << "Load Time: " << (time(NULL) - st)  << endl;

	while(true){
		cout << '>' ;
		string q;
		cin >> q;
		PostingList *p = tbl.FindPos(q);
		if(p)
			cout << p->Length() << endl;
		else
			cout << 0 << endl;
	}
	return 0;
}

