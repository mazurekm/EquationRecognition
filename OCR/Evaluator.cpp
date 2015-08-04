#include "Evaluator.h"
#include <sstream>
#include <stack>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <list>

std::string CEvaluator::operator()(const std::string &str)
{
	if(true == str.empty())
	{
		return std::string();
	}

	std::string noWhiteChars; 
   	std::copy_if(str.begin(), str.end(), std::back_inserter(noWhiteChars), 
					[](char c){return c!='\n'&&c!=' ';} ); 

	std::string buff = transformToOnp('('+noWhiteChars+')');
	double result = 0;
		
	std::stringstream sst;
	sst << noWhiteChars << '='  << result;
	
	return sst.str();
}

std::string CEvaluator::transformToOnp(const std::string &str)
{
	std::string letters;
	std::stack<std::list<char> >symbols;
	std::string result;;
	std::string specialChars = "+-*/^";

	auto it = str.begin();
	for(;it != str.end();++it)
	{
		if('(' == *it)
		{
			symbols.push(std::list<char>());
		}
		else if(')' == *it)
		{
			letters += " ";	
			result += letters;

			for(auto &iter : symbols.top())
			{
				result += iter;
			}

			letters.clear();
			symbols.pop();
		}
		else if(std::string::npos != specialChars.find(*it))
		{
			letters += " ";
			symbols.top().push_front(*it);
		}
			
		else
		{
			letters += *it;
		}
	}
	return result;
}

Polynomial CEvaluator::evaluate(const std::string &exp)
{
	std::stack<Polynomial> S;
	std::string tmpNum;
	Polynomial a,b;

	for(auto iter = exp.begin(); iter != exp.end(); ++iter) 
	{
		if('+' == *iter)
		{
			a = S.top(); S.pop();
			b = S.top(); S.pop();
			S.push( add(a,b) );
		}
		else if('-' == *iter) 
		{
			a = S.top(); S.pop();
			b = S.top(); S.pop();
			S.push( minus(b, a) );
		}
		else if('*' == *iter) 
		{
			a = S.top(); S.pop();
			b = S.top(); S.pop();
			S.push( mul(a, b) );
		}
		else if('/' == *iter) 
		{
			a = S.top(); S.pop();
			b = S.top(); S.pop();
			S.push( div(b,a) );
		}
		else if(' ' == *iter)
		{
			if(false == tmpNum.empty())
			{
				Polynomial pol;
				
				try
				{
					double val = boost::lexical_cast<double>(tmpNum);
					pol[""] = val;

				}
				catch(boost::bad_lexical_cast &)
				{
					boost::smatch matched;
					boost::regex reg("([0-9]*)([*]?)([a-zA-Z]*)([0-9]*)");

					if(true == boost::regex_search(tmpNum, matched, reg))
					{
						try
						{
							pol[ matched[3] ] = boost::lexical_cast<double>(matched[1]); 
						}
						catch(boost::bad_lexical_cast &)
						{
							pol[ matched[3] ] = 1;
						}
					}
				}
				
				S.push(pol);
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

Polynomial CEvaluator::add(const Polynomial &eq1, const Polynomial &eq2)
{
	Polynomial result;
	for(auto &it : eq1)
	{
		result[it.first] = it.second;
	}	

	for(auto &it : eq2)
	{
		if(result.end() != result.find(it.first))
		{
			result[it.first] += it.second;
		}
		else
		{
			result[it.first] = it.second;
		}
	}
	return result;
}

Polynomial CEvaluator::mul(const Polynomial &eq1, const Polynomial &eq2)
{
	Polynomial result;
	for(auto &iter1 : eq1)
	{
		for(auto &iter2 : eq2)
		{
			if(result.end() !=  result.find(iter1.first+iter2.first) )
			{
				result[iter1.first+iter2.first] += iter1.second*iter2.second;
			}
			else
			{
				result[iter1.first+iter2.first] = iter1.second*iter2.second;
			}
		}
	}
	
	return result;
}


Polynomial CEvaluator::minus(const Polynomial &eq1, const Polynomial &eq2)
{
	Polynomial tmp;
	for(auto &iter : eq2)
	{
		tmp[iter.first] = -iter.second;
	}

	return add(eq1, tmp);
}


Polynomial CEvaluator::div(Polynomial &eq1, Polynomial &eq2)
{
	Polynomial res;
	double a = eq1[""], b = eq2[""]; 
	res[""] = a/b;
	return res;
}

