#ifndef ABSTRACT_SOLVER
#define ABSTRACT_SOLVER

#include <string>

class IAbstractSolver
{
public:
	virtual std::string solveAndToStr() = 0;
	virtual ~IAbstractSolver()
	{
		
	}
};

#endif