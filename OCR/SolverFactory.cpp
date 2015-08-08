#include <OCR/SolverFactory.h>
#include <OCR/EqualSolver.h>
#include <OCR/ArthmeticSolver.h>
#include <boost/algorithm/string.hpp>
#include <vector>

std::unique_ptr<IAbstractSolver> CSolverFactory::create(const std::string &str)
{
	std::vector<std::string> res;
	boost::split(res, str, boost::is_any_of("="));

	if(res.size() > 2)
	{
		throw IncorrectExp();
	}

	return std::unique_ptr<IAbstractSolver>(new CEqualSolver(str));
}

std::string CSolverFactory::parse(const std::string &eq)
{
	return eq;
}