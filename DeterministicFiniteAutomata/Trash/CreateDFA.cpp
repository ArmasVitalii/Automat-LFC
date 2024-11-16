#include "CreateDFA.h"

std::set<std::string> CreateNFA::concatenateStates(const std::set<std::string>& first, const std::set<std::string>& second)
{
    std::set<std::string> concatenation;
    concatenation.insert(first.begin(), first.end());
    concatenation.insert(second.begin(), second.end());
    return concatenation;
}

std::set<char> CreateNFA::concatenateAlphabets(const std::set<char>& first, const std::set<char>& second)
{
    std::set<char> concatenation;
    concatenation.insert(first.begin(), first.end());
    concatenation.insert(second.begin(), second.end());
    return concatenation;
}

int CreateNFA::power(char op)
{
    switch (op)
    {
    case '(': return 0;
    case '|': return 1;
    case '.': return 2;
    case '*': return 3;
    default: return -1; 
    }
}

std::string CreateNFA::toPolish(const std::string& expression)
{
    std::string polish;
    std::stack<char> op_stack;
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
            if (!op_stack.empty()) op_stack.pop(); // Remove '('
        }
        else // Operator case
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

std::string CreateNFA::addConcatenationOperator(const std::string& regex)
{
    std::string result;
    for (size_t i = 0; i < regex.size(); ++i)
    {
        result += regex[i];

        if (i + 1 < regex.size())
        {
            char currentChar = regex[i];
            char nextChar = regex[i + 1];

            if ((isalnum(currentChar) || currentChar == ')' || currentChar == '*') &&
                (isalnum(nextChar) || nextChar == '('))
            {
                result += '.';
            }
        }
    }

    return result;
}

void CreateNFA::caseCharacter(char character)
{
    std::string initial = std::to_string(m_contor);
    std::string final = std::to_string(m_contor + 1);

    Transition trans(initial, character, final);

    automatonStack.push(
        NondeterministicFiniteAutomaton(
            { initial, final }, // States
            { character },      // Alphabet
            { trans },          // Transitions
            initial,            // Initial state
            final               // Final state
        )
    );

    m_contor += 2;
}

void CreateNFA::caseConcatenation()
{
    NondeterministicFiniteAutomaton b = automatonStack.top();
    automatonStack.pop();
    NondeterministicFiniteAutomaton a = automatonStack.top();
    automatonStack.pop();

    std::set<std::string> states = concatenateStates(a.getStates(), b.getStates());
    std::set<char> alphabet = concatenateAlphabets(a.getAlphabet(), b.getAlphabet());

    std::string collectiveState = '(' + a.getFinalState() + '=' + b.getInitialState() +')';

    std::vector<Transition> transitions;
    for (Transition trans : a.getTransitions())
    {
        if (trans.getFinalState() == a.getFinalState())
        {
            trans.setFinalState(collectiveState);
        }
        transitions.push_back(trans);
    }
    for (Transition trans : b.getTransitions())
    {
        if (trans.getInitialState() == b.getInitialState())
        {
            trans.setInitialState(collectiveState);
        }
        transitions.push_back(trans);
    }

    automatonStack.push(NondeterministicFiniteAutomaton(states, alphabet, transitions, a.getInitialState(), b.getFinalState()));
}

void CreateNFA::caseAlternate()
{
    NondeterministicFiniteAutomaton b = automatonStack.top();
    automatonStack.pop();
    NondeterministicFiniteAutomaton a = automatonStack.top();
    automatonStack.pop();

    std::set<std::string> states = concatenateStates(a.getStates(), b.getStates());
    states.insert(std::to_string(m_contor));
    states.insert(std::to_string(m_contor + 1));

    std::set<char> alphabet = concatenateAlphabets(a.getAlphabet(), b.getAlphabet());

    std::vector<Transition> transitions;

    /*1*/Transition trans(std::to_string(m_contor), lambda, a.getInitialState());
    transitions.push_back(trans);

    /*2*/trans.setFinalState(b.getInitialState());
    transitions.push_back(trans);

    for (const Transition& trans : a.getTransitions())
    {
        transitions.push_back(trans);
    }
    for (const Transition& trans : b.getTransitions())
    {
        transitions.push_back(trans);
    }

    /*3*/trans.setInitialState(a.getFinalState());
    trans.setFinalState(std::to_string(m_contor+1));
    transitions.push_back(trans);

    /*4*/trans.setInitialState(b.getFinalState());
    transitions.push_back(trans);

    automatonStack.push(NondeterministicFiniteAutomaton(states, alphabet, transitions,
        std::to_string(m_contor), std::to_string(m_contor + 1)));

    m_contor += 2;
}

void CreateNFA::caseKleeneStar()
{
    NondeterministicFiniteAutomaton a = automatonStack.top();
    automatonStack.pop();

    std::set<std::string> states{ a.getStates() };
    states.insert(std::to_string(m_contor));
    states.insert(std::to_string(m_contor + 1));

    std::vector<Transition> transitions{ a.getTransitions() };

    /*1*/Transition trans{std::to_string(m_contor), lambda, a.getInitialState()};
    transitions.push_back(trans);

    /*2*/trans.setFinalState(std::to_string(m_contor + 1));
    transitions.push_back(trans);

    /*3*/trans.setInitialState(a.getFinalState());
    transitions.push_back(trans);

    /*4*/trans.setFinalState(a.getInitialState());
    transitions.push_back(trans);

    automatonStack.push(NondeterministicFiniteAutomaton(states, a.getAlphabet(), transitions,
        std::to_string(m_contor), std::to_string(m_contor + 1)));

    m_contor += 2;
}

void CreateNFA::printAutomata() const
{
    NondeterministicFiniteAutomaton a = automatonStack.top();

    std::cout << "States: ";
    for (auto x : a.getStates())
    {
        std::cout << x << " ";
    }
    std::cout << "\nAlphabet: ";
    for (auto x : a.getAlphabet())
    {
        std::cout << x << " ";
    }
    std::cout << "\nTransitions: \n";
    for (auto x : a.getTransitions())
    {
        std::cout << "(" << x.getInitialState() << "," << x.getSimbol() << ") = " << x.getFinalState() << "\n";
    }
    std::cout << "Initial State: " << a.getInitialState();
    std::cout << "\nFinal State: " << a.getFinalState();
}

void CreateNFA::start(const std::string& regularExpression)
{
    std::string expression = toPolish(addConcatenationOperator(regularExpression));
    std::cout << expression << "\n\n";
    for (const auto& ch : expression)
    {
        if (std::isalnum(ch))
        {
            caseCharacter(ch);
        }
        else if (ch == '.')
        {
            caseConcatenation();
        }
        else if (ch == '|')
        {
            caseAlternate();
        }
        else if (ch == '*')
        {
            caseKleeneStar();
        }
    }
    printAutomata();
}
