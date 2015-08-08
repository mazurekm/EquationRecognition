#include "Evaluator.h"
#include <sstream>
#include <stack>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <list>
#include <sstream>

Polynomial CEvaluator::operator()(const std::string &str)
{
	if(true == str.empty())
	{
		return Polynomial();
	}

	std::string noWhiteChars; 
   	std::copy_if(str.begin(), str.end(), std::back_inserter(noWhiteChars), 
					[](char c){return c!='\n'&&c!=' ';} ); 

	auto buff = parseInputStr(noWhiteChars);
	auto onp = transformToOnp('('+buff+')');
	auto eval = evaluate(onp);
		
	return eval;
}


std::string CEvaluator::parseInputStr(const std::string &eq)
{
	std::string result = eq+"+_";
	std::list<boost::regex> regList;
	boost::sregex_iterator i1;;
	boost::sregex_iterator i2;
	
	regList.push_back(boost::regex("(((\\w)|(\\(.+\\)))[\\^])+((\\w)|(\\(.+\\)))"));
	regList.push_back(boost::regex("(((\\w)|(\\(.+\\)))[*])+((\\w)|(\\(.+\\)))"));
	
	for(auto &reg : regList)
	{
		i1 = boost::sregex_iterator(result.begin(), result.end(), reg);
		while(i1 != i2)
		{
			std::stringstream matched;
			matched << *i1;
			boost::replace_all(result, matched.str(), "("+matched.str()+")");
			++i1;
		}
	}

	return result.substr(0,result.size()-2);
}

std::string CEvaluator::transformToOnp(const std::string &str)
{
	std::string letters;
	std::stack<std::list<char> >symbols;
	std::string result;;
	std::string specialChars = "+-*/^";
	bool isNegative = false;

	auto it = str.begin();
	for(;it != str.end();++it)
	{
		if('(' == *it)
		{
			if( *(it+1) != '-')
			{
				symbols.push(std::list<char>());
			}
			else
			{
				letters += "(";
				isNegative = true;
			}
		}
		else if(')' == *it)
		{
			if(true == isNegative)
			{
				isNegative = false;
				letters += ")";
				continue;
			}

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
			if(false == isNegative)
			{
				letters += " ";
				symbols.top().push_front(*it);
			}
			else
			{
				letters += *it;	
			}
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
	bool isNegative = false;
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
			if(true == isNegative)
			{
				tmpNum += *iter;
			}
			else
			{
				a = S.top(); S.pop();
				b = S.top(); S.pop();
				S.push( minus(b, a) );
			}
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
		else if('^' == *iter)
		{
			a = S.top(); S.pop();
			b = S.top(); S.pop();
			S.push( pow(b,a) );
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
			if('(' == *iter)
			{
				isNegative = true;
			}
			else if(')' == *iter)
			{
				isNegative = false;
			}
			else
			{
				tmpNum += *iter;	
			}
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

	if(true == eq1.empty())
	{
		return eq2;
	}

	if(true == eq2.empty())
	{
		return eq1;
	}

	for(auto &iter1 : eq1)
	{
		for(auto &iter2 : eq2)
		{
			std::string key = iter1.first + iter2.first;
			std::sort(key.begin(), key.end());
			
			if(result.end() !=  result.find(key) )
			{
				result[key] += iter1.second*iter2.second;
			}
			else
			{
				result[key] = iter1.second*iter2.second;
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


Polynomial CEvaluator::pow(Polynomial &el1, Polynomial &exp)
{
	Polynomial res;
	for(int i = 0; i<exp[""]; ++i)
	{
		res = mul(res, el1);
	}
	return res;
}

