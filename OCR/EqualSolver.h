#ifndef EQUAL_SOLVER
#define EQUAL_SOLVER

#include <OCR/AbstractSolver.h>
#include <gsl/gsl_poly.h>
#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, double> Polynomial;

class CEqualSolver : public IAbstractSolver
{
public:
	CEqualSolver(Polynomial &eq);
	CEqualSolver(const std::string &eq);
	~CEqualSolver();
	std::vector<double> solve();
	std::string solveAndToStr();

private:
	void init(Polynomial &eq);
	double *m_eq; 
	gsl_poly_complex_workspace * m_workspace;
	int m_degree;
};

#endif

