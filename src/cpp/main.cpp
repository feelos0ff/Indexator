#include <iostream>
#include "../headers/definesincludes.h"
#include "../headers/query.h"
#include "../headers/index.h"

using namespace std;

int main()
{
	std::locale::global( std::locale( "ru_RU.cp1251" ) );

	Index idx;
	idx.CreateIndex(1, 2);

    return 0;
}

