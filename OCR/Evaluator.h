#ifndef EVALUATOR
#define EVALUATOR

#include<string>
#include<vector>
#include<map>

typedef std::map<std::string, double> Polynomial;

class CEvaluator
{
public:
	CEvaluator()
	{
	}

	std::string operator()(const std::string &str);
	Polynomial add(const Polynomial &el1, const Polynomial &el2);
	Polynomial mul(const Polynomial &el1, const Polynomial &el2);
	Polynomial minus(const Polynomial &el1, const Polynomial &el2);
	Polynomial div(Polynomial &el1, Polynomial &el2);

	std::string transformToOnp(const std::string &str);
	Polynomial evaluate(const std::string &exp);

private:

	enum EquationType
	{
		ArtmeticExp,
		PolyEq,
		NoEq	
	};


};

#endif
