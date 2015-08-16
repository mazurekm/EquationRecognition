#include <OCR/SolverFactory.h>
#include <OCR/EqualSolver.h>
#include <OCR/Evaluator.h>
#include <OCR/ArthmeticSolver.h>
#include <boost/algorithm/string.hpp>
#include <vector>

IAbstractSolver* CSolverFactory::create(const std::string &str)
{
	std::vector<std::string> res;
	boost::split(res, str, boost::is_any_of("="));
	
	if(res.size() > 2 || true == res.empty() )
	{
		throw IncorrectExp();
	}

	if(1 == res.size() || (2 == res.size() && true == res[1].empty() ) )
	{
		return new CArthmeticSolver(res[0]);
	}

	std::string eq = res[0] + "-" + "(" + res[1] + ")";
	return new CEqualSolver(eq);
}

std::string CSolverFactory::parse(const std::string &eq)
{
	return eq;
}