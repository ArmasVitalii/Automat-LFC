#pragma once
#include "Transition.h"
#include <set>
#include <iostream>
#include <string>
#include <vector>
class DeterministicFiniteAutomaton
{
private:
	char							lambda = '~';
	std::set<std::string>			m_states;
	std::set<char>					m_alphabet;
	std::vector<Transition>			m_transitions;
	std::string						m_initialState;
	std::vector<std::string>		m_finalStates;
public:
	void							assignStates(const std::set<std::string>& states);
	void							assignAlphabet(const std::set<char>& alphabet);
	void							assignTransition(const std::vector<Transition>& transitions);
	void							assignInitial(const std::string& initial);
	void							assignFinal(const std::string & final);

	const std::set<std::string>&	getStates() const;
	const std::set<char>			getAlphabet() const;
	const std::vector<Transition>&	getTransitions() const;
	const std::string&				getInitialState() const;
	const std::string&				getFinalState() const;



	void							addState(const std::string& state);
	void							addTransition(const Transition& transition);
	void							extendStates(const std::set<std::string>& newStates);


	void							printAutomaton() const;
	friend std::ostream&			operator<<(std::ostream& os, DeterministicFiniteAutomaton automaton);
	bool							verifyAutomaton() const;
	bool							checkWord(const std::string& stringToCheck) const;




	DeterministicFiniteAutomaton() = default;

	DeterministicFiniteAutomaton(
		const std::set<std::string>&		states,
		const std::set<char>&				alphabet,
		const std::vector<Transition>&		transitions,
		const std::string&					initialState,
		const std::string&					finalState
	);

private:

	bool							checkStates() const;
	bool							checkAlphabet() const;
	bool							checkInitialState() const;
	bool							checkStatesAndAlphabet() const;
	bool							checkIfIsDeterministic() const;
	bool							checkTransitions() const;
};

