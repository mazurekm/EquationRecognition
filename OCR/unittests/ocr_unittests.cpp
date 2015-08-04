#define BOOST_TEST_MODULE OCR

#include <boost/test/unit_test.hpp>
#include <OCR/Evaluator.h>
#include <OCR/EqualSolver.h>
#include <iostream>
#include <set>

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
}

BOOST_AUTO_TEST_CASE(Ev_test)
{
	std::string eq = "((a+b)*(c+d)*(e+f))+2";
	CEvaluator ev;

	auto onp = ev.transformToOnp("("+eq+")");
	BOOST_CHECK_EQUAL(onp, "a b + c d + e f + ** 2 +");
	
	auto res = ev.evaluate(onp);

	BOOST_CHECK_EQUAL(res["eca"], 1);
	BOOST_CHECK_EQUAL(res["fca"], 1);
	BOOST_CHECK_EQUAL(res["eda"], 1);
	BOOST_CHECK_EQUAL(res["fda"], 1);
	BOOST_CHECK_EQUAL(res["ecb"], 1);
	BOOST_CHECK_EQUAL(res["fcb"], 1);
	BOOST_CHECK_EQUAL(res["edb"], 1);
	BOOST_CHECK_EQUAL(res["fdb"], 1);
	BOOST_CHECK_EQUAL(res[""], 2);



	eq = "(2*5)+4+(4/2)";
	onp =  ev.transformToOnp("("+eq+")");
	res = ev.evaluate(onp);
	BOOST_CHECK_EQUAL(res[""] ,16);
}

BOOST_AUTO_TEST_CASE(Eq_solver)
{
	std::map<std::string, double> test;
	test[""] = -1;
	test["xxxxx"] = 1;

	CEqualSolver solver(test);
	auto res = solver.solve();
	
	for(auto &iter : res)
	{
		//std::cout << iter << std::endl;
	}
}
