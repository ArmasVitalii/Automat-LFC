#pragma once
#include <stack>
#include <iostream>
#include "NondeterministicFiniteAutomaton.h"
class CreateNFA
{
private:
	std::stack<NondeterministicFiniteAutomaton>	automatonStack;
	int											m_contor = 0;
	char										lambda = '~';


	std::set<std::string>						concatenateStates(const std::set<std::string>& first, const std::set<std::string>& second);
	std::set<char>								concatenateAlphabets(const std::set<char>& first, const std::set<char>& second);


	int											power(char op);
	std::string									toPolish(const std::string& expression);
	std::string									addConcatenationOperator(const std::string& regex);
public:
	void										caseCharacter(char character);
	void										caseConcatenation();
	void										caseAlternate();
	void										caseKleeneStar();

	void										printAutomata() const;
	void										start(const std::string& regularExpression);

};

