#ifndef SOLVER_FACTORY
#define SOLVER_FACTORY

#include <memory>
#include <OCR/AbstractSolver.h>

class CSolverFactory
{
public:
	IAbstractSolver* create(const std::string &str);
private:
	std::string parse(const std::string &eq);
};

#endif