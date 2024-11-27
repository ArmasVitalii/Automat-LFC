#include "DeterministicFiniteAutomaton.h"

void DeterministicFiniteAutomaton::assignStates(const std::set<std::string>& states)
{
	m_states = states;
}

void DeterministicFiniteAutomaton::assignAlphabet(const std::set<char>& alphabet)
{
	m_alphabet = alphabet;
}

void DeterministicFiniteAutomaton::assignTransition(const std::vector<Transition>& transitions)
{
	m_transitions = transitions;
}

void DeterministicFiniteAutomaton::assignInitial(const std::string& initial)
{
	m_initialState = initial;
}

void DeterministicFiniteAutomaton::assignFinal(const std::string & final)
{
	m_finalStates.push_back(final);
}

const std::set<std::string>& DeterministicFiniteAutomaton::getStates() const
{
	return m_states;
}

const std::set<char> DeterministicFiniteAutomaton::getAlphabet() const
{
	return m_alphabet;
}

const std::vector<Transition>& DeterministicFiniteAutomaton::getTransitions() const
{
	return m_transitions;
}

const std::string& DeterministicFiniteAutomaton::getInitialState() const
{
	return m_initialState;
}

const std::string& DeterministicFiniteAutomaton::getFinalState() const
{
	return m_finalStates.front();
}

void DeterministicFiniteAutomaton::addState(const std::string& state)
{
	m_states.insert(state);
}

void DeterministicFiniteAutomaton::addTransition(const Transition& transition)
{
	m_transitions.push_back(transition);
}

void DeterministicFiniteAutomaton::extendStates(const std::set<std::string>& newStates)
{
	m_states.insert(newStates.begin(), newStates.end());
}

bool DeterministicFiniteAutomaton::checkInitialState() const
{
	return std::find(m_states.begin(), m_states.end(), m_initialState) != m_states.end();
}

bool DeterministicFiniteAutomaton::checkStatesAndAlphabet() const
{
	for (const auto& x : m_transitions)
	{
		if (x.getInitialState() == m_initialState)
			return true;
	}
	return false;
}

bool DeterministicFiniteAutomaton::checkIfIsDeterministic() const
{
	for (const auto& x : m_transitions)
	{
		if (x.getSimbol() == lambda)
			return false;
	}
	return true;
}

bool DeterministicFiniteAutomaton::checkTransitions() const
{
	for (const auto& x : m_transitions)
	{
		if (std::find(m_alphabet.begin(), m_alphabet.end(), x.getSimbol()) == m_alphabet.end() ||
			std::find(m_states.begin(),m_states.end(),x.getInitialState()) == m_states.end())
			return false;
	}
	return true;
}

bool DeterministicFiniteAutomaton::checkStates() const
{
	return !m_states.empty();
}

bool DeterministicFiniteAutomaton::checkAlphabet() const
{
	return !m_alphabet.empty();
}

void DeterministicFiniteAutomaton::printAutomaton() const
{
	std::cout << "States: ";
	for (const auto& x : m_states)
	{
		std::cout << x << " ";
	}
	std::cout << "\nAlphabet: ";
	for (const auto& x : m_alphabet)
	{
		std::cout << x << " ";
	}
	std::cout << "\nTransitions: \n";
	for (const auto& x : m_transitions)
	{
		std::cout << "(" << x.getInitialState() << "," << x.getSimbol() << ") = " << x.getFinalState() << "\n";
	}
	std::cout << "Initial State: " << m_initialState;
	std::cout << "\nFinal States: ";
	for (const auto& x : m_finalStates)
	{
		std::cout << x << " ";
	}

	std::cout << '\n';
}

bool DeterministicFiniteAutomaton::verifyAutomaton() const
{
	if (!checkStates())
	{
		std::cout << "There are no states!\n";
		return false;
	}

	if (!checkAlphabet())
	{
		std::cout << "There are no simbols in alphabet!\n";
		return false;
	}

	if (!checkInitialState())
	{
		std::cout << "Initial state not in states!\n";
		return false;
	}

	if (!checkIfIsDeterministic())
	{
		std::cout << "The automaton is not deterministic!\n";
		return false;
	}

	if (!checkStatesAndAlphabet())
	{
		std::cout << "States and alphabet have common character!\n";
		return false;
	}

	if (!checkTransitions())
	{
		std::cout << "Transition with invalid state/simbol.\n";
		return false;
	}

	std::cout << "\nAutomaton validated!\n";

	return true;
}

bool DeterministicFiniteAutomaton::checkWord(const std::string& stringToCheck) const
{
	std::string currentState = m_initialState;

	for (size_t i = 0; i < stringToCheck.size(); i++)
	{
		bool wasFound = false;
		for (const auto& x : m_transitions)
		{
			if (x.getInitialState() == currentState && x.getSimbol() == stringToCheck[i])
			{
				currentState = x.getFinalState();
				wasFound = true;
				break;
			}
		}

		if (!wasFound)
			return false;
	}

	if (std::find(m_finalStates.begin(),m_finalStates.end(),currentState) != m_finalStates.end())
		return true;

	return false;
}

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton(const std::set<std::string>& states, const std::set<char>& alphabet, const std::vector<Transition>& transitions, const std::string& initialState, const std::string& finalState)
{
	assignStates(states);
	assignAlphabet(alphabet);
	assignTransition(transitions);
	assignInitial(initialState);
	assignFinal(finalState);
}

std::ostream& operator<<(std::ostream& os, DeterministicFiniteAutomaton automaton)
{
	os << "States: ";
	for (const auto& x : automaton.m_states)
	{
		os << x << " ";
	}
	os << "\nAlphabet: ";
	for (const auto& x : automaton.m_alphabet)
	{
		os << x << " ";
	}
	os << "\nTransitions: \n";
	for (const auto& x : automaton.m_transitions)
	{
		os << "(" << x.getInitialState() << "," << x.getSimbol() << ") = " << x.getFinalState() << "\n";
	}
	os << "Initial State: " << automaton.m_initialState;
	os << "\nFinal States: ";
	for (const auto& x : automaton.m_finalStates)
	{
		os << x << " ";
	}

	os << '\n';
	return os;
}
