#ifndef ABSTRACT_SOLVER
#define ABSTRACT_SOLVER

#include <string>
#include <stdexcept>

class IncorrectExp : public std::runtime_error
{
public:
	IncorrectExp() : std::runtime_error("Incorrect input Expression")
	{

	}
};

class IAbstractSolver
{
	virtual std::string solveAndToStr() = 0;
};

#endif