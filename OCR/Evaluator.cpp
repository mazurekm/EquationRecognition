#include "Evaluator.h"
#include <sstream>
#include <regex>
#include <stack>
#include <iostream>
#include <algorithm>
#include <iterator>

std::string CEvaluator::operator()(const std::string &str)
{
	if(true == str.empty())
	{
		return std::string();
	}

	std::string noWhiteChars; 
   	std::copy_if(str.begin(), str.end(), std::back_inserter(noWhiteChars), [](char c){return c!='\n'&&c!=' ';} ); 

	std::string buff = transformToOnp('('+noWhiteChars+')');
	double result = evaluate(buff);
		
	std::stringstream sst;
	sst << noWhiteChars << '='  << result;
	
	return sst.str();
}

std::string CEvaluator::transformToOnp(const std::string &str)
{
	std::string letters;
	std::stack<std::stack<char> >symbols;
	std::stringstream sst;
	std::string specialChars = "x+-*/^";

	auto it = str.begin();
	for(;it != str.end();++it)
	{
		if('(' == *it)
		{
			symbols.push(std::stack<char>());
		}
		else if(')' == *it)
		{
			sst << letters + " ";
			while(!symbols.top().empty())
			{
				sst << symbols.top().top();
				symbols.top().pop();
			}
			symbols.pop();
			letters.clear();
		}
		else if(std::string::npos != specialChars.find(*it))
		{
			letters += " ";
			symbols.top().push(*it);
		}
			
		else
		{
			letters += *it;
		}
	}

	return sst.str();
}

double CEvaluator::evaluate(const std::string &exp)
{
	std::stack<double> S;
	std::string tmpNum;

	for(auto iter = exp.begin(); iter != exp.end(); ++iter) 
	{
		if('+' == *iter)
		{
			double a=S.top(); S.pop();
			double b=S.top(); S.pop();
			S.push(a+b);
		}
		else if('-' == *iter) 
		{
			double a=S.top(); S.pop();
			double b=S.top(); S.pop();
			S.push(a-b);
		}
		else if('*' == *iter || 'x' == *iter) 
		{
			double a=S.top(); S.pop();
			double b=S.top(); S.pop();
			S.push(a*b);
		}
		else if('/' == *iter) 
		{
			double a=S.top(); S.pop();
			double b=S.top(); S.pop();
			S.push(a/b);
		}
		else if(' ' == *iter)
		{
			if(false == tmpNum.empty())
			{
				double val;
				std::stringstream sst;
				
				sst << tmpNum;
				sst >> val;
				
				S.push(val);
				tmpNum.clear();
			}
		}
		else
		{
			tmpNum += *iter;	
		}
	}
	return S.top();	
}

