#include <iostream>
#include "DeterministicFiniteAutomaton.h"
#include "CreateDFA.h"
#include "Transformer.h"

DeterministicFiniteAutomaton createDFAfrom(const std::string& regularExpression)
{
	CreateNFA nfaCreator;
	auto nfa = nfaCreator.start(regularExpression);
	std::cout << "\nThe Nondeterministic Finite Automaton is: \n";
	nfa.printAutomaton();

	std::cout << "\n\\====================================================================/";

	Transformer trans(nfa);
	auto dfa = trans.transformToDFA();
	std::cout << "\nThe Deterministic Finite Automaton is: \n";
	dfa.printAutomaton();

	return dfa;
}




int main()
{
	//aba(aa|bb)*c(ab)*

	auto x = createDFAfrom("(aa|b)*bb");
	x.verifyAutomaton();
	
	if (x.checkWord("aabb"))
		std::cout << "Word validated by automaton.\n";
	else
		std::cout << "Word not validated by automation.\n";

   

	return 0;
}