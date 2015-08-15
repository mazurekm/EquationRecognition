#ifndef ARTHMETIC_SOLVER
#define ARTHMETIC_SOLVER

#include<OCR/AbstractSolver.h>

class CArthmeticSolver : public IAbstractSolver
{
public:
	CArthmeticSolver(const std::string &eq);
	std::string solveAndToStr();
	~CArthmeticSolver()
	{

	}

private:
	Polynomial m_evResult;
};

#endif