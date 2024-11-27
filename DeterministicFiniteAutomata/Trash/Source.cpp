#include <iostream>
#include <regex>
#include <fstream>
#include "CreateDFA.h"
#include "Transformer.h"


DeterministicFiniteAutomaton createDFAfrom(const std::string& regularExpression)
{
	std::fstream transitionToDFA("TransitionToDFA.txt"), NFA("NFA.txt");

	CreateNFA nfaCreator;
	auto nfa = nfaCreator.start(regularExpression);
	NFA << nfa;

	Transformer trans(nfa);
	auto dfa = trans.transformToDFA(transitionToDFA);
	

	return dfa;
}

bool isValidRegex(const std::string& pattern)
{
	try 
	{
		std::regex(pattern);
		return true;
	}
	catch (const std::regex_error&) 
	{
		return false;
	}
}


int main()
{
	std::fstream fis("TextIntrare.txt");
	std::string regularExpression;
	fis >> regularExpression;

	int choice;
	if (isValidRegex(regularExpression))
	{
		DeterministicFiniteAutomaton dfa = createDFAfrom(regularExpression);
		do
		{
			std::cout << "\n1. Print Expression!\n";
			std::cout << "2. Print Automaton!\n";
			std::cout << "3. Check Word!\n\n";

			std::cout << "Enter choice: ";
			std::cin >> choice;

			switch (choice)
			{
			case 1:
			{
				std::cout << regularExpression << '\n';
				break;
			}
			case 2:
			{
				std::ofstream fout("DFA.txt");

				std::cout << dfa << '\n';
				fout << dfa;
				break;
			}
			case 3:
			{
				std::string word;
				std::cout << "\nEnter word to check: ";
				std::cin >> word;
				
				if (dfa.checkWord(word) == true)
				{
					std::cout << "Word " << word << " verified!\n";
				}
				else
				{
					std::cout << "Word " << word << " not verified!\n";
				}
				break;
			}
			default:
				choice = 4;
				break;
			}
		} while (choice != 4);
	}
	else
	{
		std::cout << "Expression isn't valid!\n";
	}


	return 0;
}