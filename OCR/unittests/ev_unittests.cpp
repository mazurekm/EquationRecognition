#define BOOST_TEST_MODULE OCR

#include <boost/test/unit_test.hpp>
#include <OCR/Evaluator.h>
#include <OCR/EqualSolver.h>
#include <iostream>
#include <set>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <OCR/ArthmeticSolver.h>
#include <OCR/SolverFactory.h>
#include <typeinfo>

BOOST_AUTO_TEST_CASE(add_mul_test)
{
	CEvaluator ev;
	Polynomial p1, p2;
	p1["a"] = 2;
	p1[""] = 1;
	p2["b"] = 1;
    p2["a"] = 1;
	p2[""] = 2;

	auto res = ev.add(p1, p2);	
	BOOST_CHECK_EQUAL(res["a"], 3);
	BOOST_CHECK_EQUAL(res[""], 3);
	BOOST_CHECK_EQUAL(res["b"], 1);


	auto res2 = ev.mul(p1, p2);
	BOOST_CHECK_EQUAL(res2["a"], 5);
	BOOST_CHECK_EQUAL(res2[""], 2);
	BOOST_CHECK_EQUAL(res2["b"], 1);

	BOOST_CHECK_EQUAL(res2["ab"], 2);
	BOOST_CHECK_EQUAL(res2["aa"], 2);

	p1.clear();
	p2.clear();
	p1["x"] = 1;
	p1[""] = 1;
	p2[""] = 2;

	auto res3 = ev.pow(p1, p2);
	BOOST_CHECK_EQUAL(res3["xx"], 1);
	BOOST_CHECK_EQUAL(res3["x"], 2);
	BOOST_CHECK_EQUAL(res3[""], 1);
}

BOOST_AUTO_TEST_CASE(Ev_test)
{
	std::string eq = "((a+b)*(c+d)*(e+f))+2";
	CEvaluator ev;

	auto onp = ev.transformToOnp("("+eq+")");
	BOOST_CHECK_EQUAL(onp, "a b + c d + e f + ** 2 +");
	
	auto res = ev.evaluate(onp);

	BOOST_CHECK_EQUAL(res["ace"], 1);
	BOOST_CHECK_EQUAL(res["acf"], 1);
	BOOST_CHECK_EQUAL(res["ade"], 1);
	BOOST_CHECK_EQUAL(res["adf"], 1);
	BOOST_CHECK_EQUAL(res["bce"], 1);
	BOOST_CHECK_EQUAL(res["bcf"], 1);
	BOOST_CHECK_EQUAL(res["bde"], 1);
	BOOST_CHECK_EQUAL(res["bdf"], 1);
	BOOST_CHECK_EQUAL(res[""], 2);


	eq = "(2*5)+4+(4/2)";
	onp =  ev.transformToOnp("("+eq+")");
	res = ev.evaluate(onp);
	BOOST_CHECK_EQUAL(res[""] ,16);

	eq = "((-2)*5)+4+(4/2)";
	onp =  ev.transformToOnp("("+eq+")");
	res = ev.evaluate(onp);
	BOOST_CHECK_EQUAL(res[""] ,-4);

}

BOOST_AUTO_TEST_CASE(rg_test)
{
	std::string str = "a*b+c*d*e*f";
	CEvaluator ev;
	std::string res = ev.parseInputStr(str);
	BOOST_CHECK_EQUAL(res, "(a*b)+(c*d*e*f)");
}

BOOST_AUTO_TEST_CASE(full_flow)
{
	std::string eq = "x^2-4";
	CEvaluator ev;
	CEqualSolver s(eq);
	auto res = s.solveAndToStr(); 
	std::cout << res;
}

BOOST_AUTO_TEST_CASE(factory_test)
{
	std::string exp = "a+b";
	CSolverFactory factory;
	std::unique_ptr<IAbstractSolver> ptr(factory.create(exp));
	BOOST_CHECK_EQUAL(typeid(*ptr).name(), "16CArthmeticSolver");

	exp = "x+2=3";
	
	ptr.reset(factory.create(exp));
	BOOST_CHECK_EQUAL(typeid(*ptr).name(), "12CEqualSolver");	
}

BOOST_AUTO_TEST_CASE(arthmetic_test)
{
	std::string str = "(a+b)^2";
	CArthmeticSolver s(str);
	BOOST_CHECK_EQUAL(s.solveAndToStr(), "1*a^2+2*a*b+1*b^2");
}



BOOST_AUTO_TEST_CASE(incorrect_exp_test)
{
	std::string exp = "(^^HGGJ&)+HGGFGJ";
	CSolverFactory factory;
	std::unique_ptr<IAbstractSolver> ptr;

	try
	{
		ptr.reset( factory.create(exp) );
		ptr->solveAndToStr();
		BOOST_CHECK(false);
	}
	catch(std::runtime_error &)
	{
		BOOST_CHECK(true);
	}

	exp = "2aa4";
	try
	{
		ptr.reset( factory.create(exp) );
		std ::cout << ptr->solveAndToStr();
		BOOST_CHECK(false);
	}
	catch(std::runtime_error &)
	{
		BOOST_CHECK(true);
	}

	exp = "5=7";
	try
	{
		ptr.reset( factory.create(exp) );
		BOOST_CHECK(false);
	}
	catch(std::runtime_error &)
	{
		BOOST_CHECK(true);
	}

	exp = "(2)";
	try
	{
		ptr.reset( factory.create(exp) );
		BOOST_CHECK(true);
	}
	catch(std::runtime_error &)
	{
		BOOST_CHECK(false);
	}

}