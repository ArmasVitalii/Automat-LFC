#pragma once
#include "DeterministicFiniteAutomaton.h"
#include <vector>
#include <set>
#include <queue>
class Transformer
{
private:
	DeterministicFiniteAutomaton m_nfa;
	std::vector<std::set<std::string>> m_transformer;
	char										lambda = '~';

	std::set<std::string> generateLambdaClosed(const std::set<std::string>& states, char simbol);
	std::set<std::string> computeFinalStates(const std::set<std::string>& initialStates, char symbol);

public:
	Transformer(const DeterministicFiniteAutomaton& nfa);
	DeterministicFiniteAutomaton transformToDFA();
};

