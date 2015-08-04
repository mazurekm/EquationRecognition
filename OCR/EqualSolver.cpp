#include "EqualSolver.h"
#include <iterator>
#include <algorithm>

CEqualSolver::CEqualSolver(Polynomial &eq)
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


std::vector<double> CEqualSolver::solve()
{
	double *solution = new double [m_degree * 2];
	gsl_poly_complex_solve(m_eq, m_degree+1, m_workspace, solution);

	std::vector<double> result;
	std::copy(solution, solution + m_degree*2, std::back_inserter(result));

	delete [] solution;
	return result;
}

CEqualSolver::~CEqualSolver()
{
	if(nullptr != m_workspace)
	{
		gsl_poly_complex_workspace_free(m_workspace);		
	}
	
	delete [] m_eq;

}
