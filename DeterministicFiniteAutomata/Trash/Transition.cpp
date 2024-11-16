#include "Transition.h"

Transition::Transition(const std::string& initial, char simbol,const std::string & final) :m_inital{ initial }, m_simbol{ simbol }, m_final{final}
{
}

const std::string Transition::getInitialState() const
{
	return m_inital;
}

const char Transition::getSimbol() const
{
	return m_simbol;
}

const std::string Transition::getFinalState() const
{
	return m_final;
}

void Transition::setInitialState(const std::string& initial)
{
	m_inital = initial;
}

void Transition::setSimbol(char simbol)
{
	m_simbol = simbol;
}

void Transition::setFinalState(const std::string & final)
{
	m_final = final;
}
