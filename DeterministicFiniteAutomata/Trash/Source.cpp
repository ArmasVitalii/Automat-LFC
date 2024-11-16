#include <iostream>
#include "CreateDFA.h"


int main()
{
	//aba(aa|bb)*c(ab)*
	CreateNFA dfa;
	dfa.start("(aa|b)*bb");


	return 0;
}