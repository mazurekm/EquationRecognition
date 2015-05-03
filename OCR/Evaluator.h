#ifndef EVALUATOR
#define EVALUATOR

#include<string>

class CEvaluator
{
public:
	CEvaluator()
	{
	}

	std::string operator()(const std::string &str);

private:
	std::string transformToOnp(const std::string &str);
	double evaluate(const std::string &exp);


};

#endif
