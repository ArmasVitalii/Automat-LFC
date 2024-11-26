#include "Transformer.h"
#include <iostream>
#include <iomanip>

Transformer::Transformer(const DeterministicFiniteAutomaton& nfa) : m_nfa{ nfa }
{
}

std::set<std::string> Transformer::generateLambdaClosed(const std::set<std::string>& states, char simbol)
{
    std::set<std::string> lambdaClosed;
    std::queue<std::string> stateQueue;

    for (const auto& state : states)
    {
        lambdaClosed.insert(state);
        stateQueue.push(state);
    }

    while (!stateQueue.empty())
    {
        std::string currentState = stateQueue.front();
        stateQueue.pop();

        for (const auto& transition : m_nfa.getTransitions())
        {
            if (transition.getInitialState() == currentState && transition.getSimbol() == simbol)
            {
                std::string nextState = transition.getFinalState();

                if (lambdaClosed.find(nextState) == lambdaClosed.end())
                {
                    lambdaClosed.insert(nextState);
                    stateQueue.push(nextState);
                }
            }
        }
    }

    return lambdaClosed;
}

std::set<std::string> Transformer::computeFinalStates(const std::set<std::string>& initialStates, char simbol)
{
    std::set<std::string> finalStates;

    for (const auto& initialState : initialStates) 
    {
        for (const auto& transition : m_nfa.getTransitions()) 
        {
            if (transition.getInitialState() == initialState && transition.getSimbol() == simbol)
            {
                finalStates.insert(transition.getFinalState());
            }
        }
    }

    return finalStates;
}

DeterministicFiniteAutomaton Transformer::transformToDFA()
{
    DeterministicFiniteAutomaton dfa;
    dfa.assignAlphabet(m_nfa.getAlphabet());
    dfa.assignInitial("0");


    bool foundALambdaClose = true;
    std::vector<std::set<std::string>> lambdaClosedVector;

    std::set<std::string> lambdaClosed = generateLambdaClosed({ m_nfa.getInitialState() }, lambda);
    lambdaClosedVector.push_back(lambdaClosed);

    while (foundALambdaClose)
    {
        foundALambdaClose = false;

        for (size_t i = 0; i < lambdaClosedVector.size(); ++i)
        {
            for (const auto& ch : m_nfa.getAlphabet())
            {
                std::set<std::string> toClose = computeFinalStates(lambdaClosedVector[i], ch);

                std::set<std::string> lambdaClosedForFinalStates = generateLambdaClosed(toClose, lambda);

                if (!lambdaClosedForFinalStates.empty() && 
                    std::find(lambdaClosedVector.begin(), lambdaClosedVector.end(), lambdaClosedForFinalStates) == lambdaClosedVector.end())
                {
                    lambdaClosedVector.push_back(lambdaClosedForFinalStates);
                    foundALambdaClose = true;
                }
            }
        }
    }

    for (size_t i = 0; i < lambdaClosedVector.size(); i++)
    {
        dfa.extendStates({std::to_string(i)});
    }
  
    dfa.assignTransition({});
    dfa.assignFinal(std::to_string(lambdaClosedVector.size()-1));

    std::cout << "\n\nTransition diagram for the DFA:" << std::endl;

    std::cout << "   ";
    for (const auto& ch : m_nfa.getAlphabet())
    {
        std::cout << "  " << ch << "  ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < lambdaClosedVector.size(); i++)
    {
        std::cout << i << ": ";

        for (const auto& ch : m_nfa.getAlphabet())
        {
            std::set<std::string> toClose = computeFinalStates(lambdaClosedVector[i], ch);

            std::set<std::string> lambdaClosedForFinalStates = generateLambdaClosed(toClose, lambda);

            if (lambdaClosedForFinalStates.empty())
            {
                std::cout << "  -  ";
            }
            else
            {
                bool found = false;
                for (size_t j = 0; j < lambdaClosedVector.size(); j++)
                {
                    if (lambdaClosedVector[j] == lambdaClosedForFinalStates)
                    {
                        std::cout << "  " << j << "  ";
                        dfa.addTransition({ std::to_string(i), ch, std::to_string(j)});
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    std::cout << "  -  ";
                }
            }
        }
        std::cout << std::endl;
    }

    std::cout << '\n' << "Where the transitions are as follows:\n";

    for (size_t i = 0; i < lambdaClosedVector.size(); i++)
    {
        std::cout << i << ": { ";
        for (const auto& state : lambdaClosedVector[i])
        {
            std::cout << state << " ";
        }
        std::cout << "}" << std::endl;
    }

    return dfa;
}