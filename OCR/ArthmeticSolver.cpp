#include<OCR/Evaluator.h>
#include<OCR/ArthmeticSolver.h>
#include<boost/lexical_cast.hpp>
#include<iostream>

CArthmeticSolver::CArthmeticSolver(const std::string &eq)
{
	CEvaluator ev;
	m_evResult = ev(eq);
}

std::string CArthmeticSolver::solveAndToStr()
{
	std::string result;
	for(auto &el : m_evResult)
	{
		std::map<char, int> symMap;
		for(auto &character : el.first)
		{
			if( symMap.end() == symMap.find(character) )
			{
				symMap[character] = 1;	
			}
			else
			{
				symMap[character] += 1;
			}

		}

		result += boost::lexical_cast<std::string>(el.second);	

		for(auto &pair : symMap)
		{
			result += std::string("*") + pair.first;
			if(1 < pair.second) 
			{
				result += std::string("^") + 
					boost::lexical_cast<std::string>(pair.second);
			}
		}
		result += "+";
	}

	result.erase(result.end()-1);
	return result;
}