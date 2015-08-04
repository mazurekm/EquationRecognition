#ifndef EQUAL_SOLVER
#define EQUAL_SOLVER

#include <gsl/gsl_poly.h>
#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, double> Polynomial;

class CEqualSolver
{
public:
	CEqualSolver(Polynomial &eq);
	~CEqualSolver();
	std::vector<double> solve();

private:
	double *m_eq; 
	gsl_poly_complex_workspace * m_workspace;
	int m_degree;
};

#endif

