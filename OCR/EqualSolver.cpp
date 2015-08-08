#include "EqualSolver.h"
#include <iterator>
#include <algorithm>
#include <OCR/Evaluator.h>
#include <boost/lexical_cast.hpp>

CEqualSolver::CEqualSolver(Polynomial &eq)
{
	init(eq);
}

void CEqualSolver::init(Polynomial &eq)
{
	auto lastEl = eq.end();
	m_degree = (--lastEl)->first.size(); 
	m_eq = new double [ m_degree + 1 ];
	m_workspace = gsl_poly_complex_workspace_alloc( m_degree + 1 );

	for(int i = 0; i<m_degree+1; ++i)
	{
		m_eq[i] = 0;
	}

	for(auto & iter : eq)
	{
		m_eq[iter.first.size()] = iter.second;	
	}	
}


CEqualSolver::CEqualSolver(const std::string &eq)
{
	CEvaluator eval;
	auto resultOfeval = eval(eq);
	init(resultOfeval);
}

std::vector<double> CEqualSolver::solve()
{
	double *solution = new double [m_degree * 2];
	gsl_poly_complex_solve(m_eq, m_degree+1, m_workspace, solution);

	std::vector<double> result;
	std::copy(solution, solution + m_degree*2, std::back_inserter(result));

	delete [] solution;
	return result;
}

std::string CEqualSolver::solveAndToStr()
{
	auto res = solve();
	std::string asString;

	std::string re, im;
	for(size_t i=0; i<res.size(); i+=2)
	{
		re = boost::lexical_cast<std::string>(res[i]);

		if(0 != res[i+1])
		{
			im = boost::lexical_cast<std::string>(res[i+1]) + "j";
		}

		asString += re + " " + im + "\n";
	}

	return asString;
}

CEqualSolver::~CEqualSolver()
{
	if(nullptr != m_workspace)
	{
		gsl_poly_complex_workspace_free(m_workspace);		
	}
	
	delete [] m_eq;

}
