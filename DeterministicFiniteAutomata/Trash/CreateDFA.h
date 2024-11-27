#pragma once
#include <stack>
#include <iostream>
#include "DeterministicFiniteAutomaton.h"
#include "Transformer.h"
class CreateNFA
{
private:
	std::stack<DeterministicFiniteAutomaton>	m_automatonStack;
	int											m_contor = 0;
	char										lambda = '~';

	struct concatenation
	{
		std::string initial;
		std::string final;
	};

	std::set<std::string>						concatenateStates(const std::set<std::string>& first, const std::set<std::string>& second);
	std::set<char>								concatenateAlphabets(const std::set<char>& first, const std::set<char>& second);


	int											power(char op);
	std::string									toPolish(const std::string& expression);
	std::string									addConcatenationOperator(const std::string& regex);

	std::vector<concatenation>					m_saveConcatenatedStates;


private:
	void										caseCharacter(char character);
	void										caseConcatenation();
	void										caseAlternate();
	void										caseKleeneStar();

public:
	DeterministicFiniteAutomaton				start(const std::string& regularExpression);
};

