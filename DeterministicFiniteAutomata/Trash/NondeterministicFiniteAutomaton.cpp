#include "NondeterministicFiniteAutomaton.h"

void NondeterministicFiniteAutomaton::assignStates(const std::set<std::string>& states)
{
	m_states = states;
}

void NondeterministicFiniteAutomaton::assignAlphabet(const std::set<char>& alphabet)
{
	m_alphabet = alphabet;
}

void NondeterministicFiniteAutomaton::assignTransition(const std::vector<Transition>& transitions)
{
	m_transitions = transitions;
}

void NondeterministicFiniteAutomaton::assignInitial(const std::string& initial)
{
	m_initialState = initial;
}

void NondeterministicFiniteAutomaton::assignFinal(const std::string & final)
{
	m_finalState = final;
}

const std::set<std::string>& NondeterministicFiniteAutomaton::getStates() const
{
	return m_states;
}

const std::set<char> NondeterministicFiniteAutomaton::getAlphabet() const
{
	return m_alphabet;
}

const std::vector<Transition>& NondeterministicFiniteAutomaton::getTransitions() const
{
	return m_transitions;
}

const std::string& NondeterministicFiniteAutomaton::getInitialState() const
{
	return m_initialState;
}

const std::string& NondeterministicFiniteAutomaton::getFinalState() const
{
	return m_finalState;
}

void NondeterministicFiniteAutomaton::addState(const std::string& state)
{
	m_states.insert(state);
}

void NondeterministicFiniteAutomaton::addTransition(const Transition& transition)
{
	m_transitions.push_back(transition);
}

NondeterministicFiniteAutomaton::NondeterministicFiniteAutomaton(const std::set<std::string>& states, const std::set<char>& alphabet, const std::vector<Transition>& transitions, const std::string& initialState, const std::string& finalState)
{
	assignStates(states);
	assignAlphabet(alphabet);
	assignTransition(transitions);
	assignInitial(initialState);
	assignFinal(finalState);
}
