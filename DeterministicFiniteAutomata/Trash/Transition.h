#pragma once
#include <string>
class Transition
{
private:
	std::string m_inital;
	char		m_simbol;
	std::string m_final;
public:
	Transition(const std::string& initial, char simbol,const std::string& final);
	const std::string		getInitialState()	const;
	const char				getSimbol()			const;
	const std::string		getFinalState()		const;

	void					setInitialState(const std::string& initial);
	void					setSimbol(char simbol);
	void					setFinalState(const std::string& final);

};

