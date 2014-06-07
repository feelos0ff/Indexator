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
	idx.CreateIndex(1, 1000);

    return 0;
}

