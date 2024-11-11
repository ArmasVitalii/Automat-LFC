/****
Alphabet - set
Make States be strings to display equivalance
Refactor in classes

Make 2nd class AFD? so AFN -> AFN

Make functions for |, * , . and char


***********************************************/

#include <iostream>
#include <vector>
#include <Stack>

constexpr auto lambda = '~';

struct Transition
{
	int initial;
	char simbol;
	int final;
};

int power(char op)
{
	switch (op)
	{
	case '(':
		return 0;
	case '|':
		return 1;
	case '.':
		return 2;
	case '*':
		return 3;
	}
}
std::string toPolish(const std::string& expression)
{
	std::string polish;
	std::stack<char>op_stack;
	for (const auto& x : expression)
	{
		if (std::isalnum(x))
		{
			polish += x;
		}
		else if (x == '(')
		{
			op_stack.push(x);
		}
		else if (x == ')')
		{
			while (!op_stack.empty() && op_stack.top() != '(')
			{
				polish += op_stack.top();
				op_stack.pop();
			}
			if (!op_stack.empty())
			{
				op_stack.pop();
			}
		}
		else
		{
			while (!op_stack.empty() && power(op_stack.top()) >= power(x))
			{
				polish += op_stack.top();
				op_stack.pop();
			}
			op_stack.push(x);
		}



	}
	while (!op_stack.empty())
	{
		polish += op_stack.top();
		op_stack.pop();
	}
	return polish;
}
std::string addConcatenate(const std::string& expression)
{
	std::string newExpression;
	for (size_t i = 0; i < expression.size() - 1; i++)
	{
		newExpression += expression[i];
		if (expression[i] == ')' && !std::isalnum(expression[i + 1]))
			continue;

		if (expression[i] == '(' || expression[i] == '|')
			continue;
		if (expression[i + 1] != '|' && expression[i + 1] != ')')
			newExpression += '.';

	}
	if (expression[expression.size() - 1] != ')')
		newExpression += expression[expression.size() - 1];

	return newExpression;
}

class AFN
{
private:
	std::vector<int> states;
	std::vector<char> alphabet;
	std::vector<Transition> transitions;
	int initial;
	int final;
public:
	AFN() = default;
	void assignStates(std::vector<int>states)
	{
		this->states = states;
	}
	void assignAlphabet(std::vector<char>alphabet)
	{
		this->alphabet = alphabet;
	}
	void assignTransition(std::vector<Transition> trans)
	{
		this->transitions = trans;
	}
	void assignInital(int ini)
	{
		this->initial = ini;
	}
	void assignFinal(int fin)
	{
		this->final = fin;
	}


	const std::vector<int>& getStates() const {
		return states;
	}
	const std::vector<char>& getAlphabet() const {
		return alphabet;
	}
	std::vector<Transition>& getTransitions()
	{
		return transitions;
	}
	int getInitial() const {
		return initial;
	}
	int getFinal() const {
		return final;
	}

	void addTransition(std::vector<Transition> a)
	{
		for (auto& x : a)
		{
			transitions.push_back(x);
		}
	}
	void addStates(std::vector<int> a)
	{
		for (auto& x : a)
		{
			states.push_back(x);
		}
	}
};

std::vector<int>addIntVectors(std::vector<int> v1, std::vector<int> v2)
{
	std::vector<int> v3;
	v3.insert(v3.end(), v1.begin(), v1.end());
	v3.insert(v3.end(), v2.begin(), v2.end());
	return v3;
}

std::vector<char>addCharVectors(std::vector<char> v1, std::vector<char> v2)
{
	std::vector<char> v3;
	v3.insert(v3.end(), v1.begin(), v1.end());
	v3.insert(v3.end(), v2.begin(), v2.end());
	return v3;
}

std::vector<Transition> three(AFN a, AFN b)
{
	std::vector<Transition> c;
	c.insert(c.end(), a.getTransitions().begin(), a.getTransitions().end());

	for (auto& x : b.getTransitions())
	{
		if (x.initial == b.getInitial()) x.initial = a.getFinal();
	}
	c.insert(c.end(), b.getTransitions().begin(), b.getTransitions().end());
	return c;

}



int main() {

	std::string text = toPolish(addConcatenate("a(b|c)*d"));
	std::stack<AFN> sa;
	int contor = 0;

	for (const auto& x : text) {
		if (std::isalnum(x)) {  
		
			AFN a;
			a.assignStates({ contor, contor + 1 });
			a.assignAlphabet({ x });

			Transition trans;
			trans.initial = contor;
			trans.simbol = x;
			trans.final = contor + 1;
			a.assignTransition({ trans });

			a.assignInital(contor);
			a.assignFinal(contor + 1);

			sa.push(a);
			contor += 2;
		}
		else if (x == '.') { 
			AFN a = sa.top(); sa.pop();
			AFN b = sa.top(); sa.pop();

			AFN c;
			c.assignStates(addIntVectors(b.getStates(), a.getStates()));
			c.assignAlphabet(addCharVectors(b.getAlphabet(), a.getAlphabet()));

			
			c.assignTransition(b.getTransitions());
			for (auto trans : a.getTransitions()) {
				if (trans.initial == a.getInitial()) trans.initial = b.getFinal();
				c.addTransition({ trans });
			}

			c.assignInital(b.getInitial());
			c.assignFinal(a.getFinal());
			sa.push(c);
		}
		else if (x == '|') {  
			AFN a = sa.top(); sa.pop();
			AFN b = sa.top(); sa.pop();

			AFN c;
			c.assignStates(addIntVectors(a.getStates(), b.getStates()));
			c.addStates({ contor, contor + 1 });

			c.assignAlphabet(addCharVectors(a.getAlphabet(), b.getAlphabet()));
			c.addTransition(a.getTransitions());
			c.addTransition(b.getTransitions());


			Transition trans;
			trans.initial = contor;
			trans.simbol = lambda;
			trans.final = a.getInitial();
			c.addTransition({ trans });

			trans.initial = contor;
			trans.simbol = lambda;
			trans.final = b.getInitial();
			c.addTransition({ trans });


			trans.initial = a.getFinal();
			trans.simbol = lambda;
			trans.final = contor + 1;
			c.addTransition({ trans });

			trans.initial = b.getFinal();
			trans.simbol = lambda;
			trans.final = contor + 1;
			c.addTransition({ trans });

			c.assignInital(contor);
			c.assignFinal(contor + 1);
			sa.push(c);
			contor += 2;
		}
		else if (x == '*') {  
			AFN a = sa.top(); sa.pop();
			AFN c;

			c.assignStates(a.getStates());
			c.addStates({ contor, contor + 1 });

			c.assignAlphabet(a.getAlphabet());
			c.assignTransition(a.getTransitions());

			
			Transition trans;
			trans.initial = contor;
			trans.simbol = lambda;
			trans.final = a.getInitial();
			c.addTransition({ trans });

			trans.initial = contor;
			trans.simbol = lambda;
			trans.final = contor + 1;
			c.addTransition({ trans });

			trans.initial = a.getFinal();
			trans.simbol = lambda;
			trans.final = contor + 1;
			c.addTransition({ trans });

			trans.initial = a.getFinal();
			trans.simbol = lambda;
			trans.final = a.getInitial();
			c.addTransition({ trans });

			c.assignInital(contor);
			c.assignFinal(contor + 1);
			sa.push(c);
			contor += 2;
		}
	}

	AFN a = sa.top();
	std::cout << "States: ";
	for (auto x : a.getStates()) {
		std::cout << x << " ";
	}
	std::cout << "\nAlphabet: ";
	for (auto x : a.getAlphabet()) {
		std::cout << x << " ";
	}
	std::cout << "\nTransitions: \n";
	for (auto x : a.getTransitions()) {
		printf("(%d,%c) = %d\n", x.initial, x.simbol, x.final);
	}
	std::cout << "Initial State: " << a.getInitial();
	std::cout << "\nFinal State: " << a.getFinal();


	return 0;
}
