/*!
 *  \file c_combination.cpp
 *  \brief Main source of c_combination test
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */

#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <two.h>


static const std::string k_programName = std::string("c_combination");


void testFunction1()
{
    const int l_number1 = 1;
    const int l_number2 = 2;

    two::C_Combination<int> l_combInt;

    l_combInt.AddElement(0);
    l_combInt.AddElement(l_number1);
    l_combInt.AddElement(l_number1);

    std::cout << " " << l_combInt << "\n";

    l_combInt.AddElement(l_number2);

    std::cout << " " << l_combInt << "\n";

    std::cout << "\n";
}


void testFunction2()
{
    const std::string l_string1("pippo");
    const std::string l_string2("pluto");

    two::C_Combination<std::string> l_combStdString(std::vector<std::string>{l_string1, l_string2});

    std::cout << " " << l_combStdString << "\n";

    l_combStdString.AddElement(std::string("topolino"));

    std::cout << " " << l_combStdString << "\n";

    std::cout << "\n";
}


void testFunction3()
{
    std::list<double> l_list;

    l_list.push_back(0.1);
    l_list.push_back(0.3);
    l_list.push_back(0.2);

    two::C_Combination<double> l_combDouble(l_list);

    std::cout << " " << l_combDouble << "\n";

    std::cout << "\n";
}


void testFunction4()
{
    two::C_Combination<int> l_combInt1(std::vector<int>{1, 3, 2});
    two::C_Combination<int> l_combInt2(std::list<int>{3, 2, 1});
    two::C_Combination<int> l_combInt3(std::vector<int>{5, 10});
    two::C_Combination<int> l_combInt4(std::vector<int>{1, 2});

    std::cout << " " << l_combInt1 << "\t < \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt1 < l_combInt2) << "\n";
    std::cout << " " << l_combInt1 << "\t < \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt1 < l_combInt3) << "\n";
    std::cout << " " << l_combInt1 << "\t < \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt1 < l_combInt4) << "\n";

    std::cout << " " << l_combInt2 << "\t < \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt2 < l_combInt1) << "\n";
    std::cout << " " << l_combInt2 << "\t < \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt2 < l_combInt3) << "\n";
    std::cout << " " << l_combInt2 << "\t < \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt2 < l_combInt4) << "\n";

    std::cout << " " << l_combInt3 << "\t < \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt3 < l_combInt1) << "\n";
    std::cout << " " << l_combInt3 << "\t < \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt3 < l_combInt2) << "\n";
    std::cout << " " << l_combInt3 << "\t < \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt3 < l_combInt4) << "\n";

    std::cout << " " << l_combInt4 << "\t < \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt4 < l_combInt1) << "\n";
    std::cout << " " << l_combInt4 << "\t < \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt4 < l_combInt2) << "\n";
    std::cout << " " << l_combInt4 << "\t < \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt4 < l_combInt3) << "\n";

    std::cout << " " << l_combInt1 << "\t > \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt1 > l_combInt2) << "\n";
    std::cout << " " << l_combInt1 << "\t > \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt1 > l_combInt3) << "\n";
    std::cout << " " << l_combInt1 << "\t > \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt1 > l_combInt4) << "\n";

    std::cout << " " << l_combInt2 << "\t > \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt2 > l_combInt1) << "\n";
    std::cout << " " << l_combInt2 << "\t > \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt2 > l_combInt3) << "\n";
    std::cout << " " << l_combInt2 << "\t > \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt2 > l_combInt4) << "\n";

    std::cout << " " << l_combInt3 << "\t > \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt3 > l_combInt1) << "\n";
    std::cout << " " << l_combInt3 << "\t > \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt3 > l_combInt2) << "\n";
    std::cout << " " << l_combInt3 << "\t > \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt3 > l_combInt4) << "\n";

    std::cout << " " << l_combInt4 << "\t > \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt4 > l_combInt1) << "\n";
    std::cout << " " << l_combInt4 << "\t > \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt4 > l_combInt2) << "\n";
    std::cout << " " << l_combInt4 << "\t > \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt4 > l_combInt3) << "\n";

    std::cout << " " << l_combInt1 << "\t == \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt1 == l_combInt2) << "\n";
    std::cout << " " << l_combInt1 << "\t == \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt1 == l_combInt3) << "\n";
    std::cout << " " << l_combInt1 << "\t == \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt1 == l_combInt4) << "\n";

    std::cout << " " << l_combInt2 << "\t == \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt2 == l_combInt1) << "\n";
    std::cout << " " << l_combInt2 << "\t == \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt2 == l_combInt3) << "\n";
    std::cout << " " << l_combInt2 << "\t == \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt2 == l_combInt4) << "\n";

    std::cout << " " << l_combInt3 << "\t == \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt3 == l_combInt1) << "\n";
    std::cout << " " << l_combInt3 << "\t == \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt3 == l_combInt2) << "\n";
    std::cout << " " << l_combInt3 << "\t == \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt3 == l_combInt4) << "\n";

    std::cout << " " << l_combInt4 << "\t == \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt4 == l_combInt1) << "\n";
    std::cout << " " << l_combInt4 << "\t == \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt4 == l_combInt2) << "\n";
    std::cout << " " << l_combInt4 << "\t == \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt4 == l_combInt3) << "\n";

    std::cout << " " << l_combInt1 << "\t != \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt1 != l_combInt2) << "\n";
    std::cout << " " << l_combInt1 << "\t != \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt1 != l_combInt3) << "\n";
    std::cout << " " << l_combInt1 << "\t != \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt1 != l_combInt4) << "\n";

    std::cout << " " << l_combInt2 << "\t != \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt2 != l_combInt1) << "\n";
    std::cout << " " << l_combInt2 << "\t != \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt2 != l_combInt3) << "\n";
    std::cout << " " << l_combInt2 << "\t != \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt2 != l_combInt4) << "\n";

    std::cout << " " << l_combInt3 << "\t != \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt3 != l_combInt1) << "\n";
    std::cout << " " << l_combInt3 << "\t != \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt3 != l_combInt2) << "\n";
    std::cout << " " << l_combInt3 << "\t != \t" << l_combInt4 << "\t ? \t" << std::boolalpha << (l_combInt3 != l_combInt4) << "\n";

    std::cout << " " << l_combInt4 << "\t != \t" << l_combInt1 << "\t ? \t" << std::boolalpha << (l_combInt4 != l_combInt1) << "\n";
    std::cout << " " << l_combInt4 << "\t != \t" << l_combInt2 << "\t ? \t" << std::boolalpha << (l_combInt4 != l_combInt2) << "\n";
    std::cout << " " << l_combInt4 << "\t != \t" << l_combInt3 << "\t ? \t" << std::boolalpha << (l_combInt4 != l_combInt3) << "\n";

    std::cout << " " << l_combInt1 << "\t + \t" << l_combInt2 << "\t = \t" << std::boolalpha << (l_combInt1 + l_combInt2) << "\n";
    std::cout << " " << l_combInt1 << "\t + \t" << l_combInt3 << "\t = \t" << std::boolalpha << (l_combInt1 + l_combInt3) << "\n";
    std::cout << " " << l_combInt1 << "\t + \t" << l_combInt4 << "\t = \t" << std::boolalpha << (l_combInt1 + l_combInt4) << "\n";

    std::cout << " " << l_combInt2 << "\t + \t" << l_combInt1 << "\t = \t" << std::boolalpha << (l_combInt2 + l_combInt1) << "\n";
    std::cout << " " << l_combInt2 << "\t + \t" << l_combInt3 << "\t = \t" << std::boolalpha << (l_combInt2 + l_combInt3) << "\n";
    std::cout << " " << l_combInt2 << "\t + \t" << l_combInt4 << "\t = \t" << std::boolalpha << (l_combInt2 + l_combInt4) << "\n";

    std::cout << " " << l_combInt3 << "\t + \t" << l_combInt1 << "\t = \t" << std::boolalpha << (l_combInt3 + l_combInt1) << "\n";
    std::cout << " " << l_combInt3 << "\t + \t" << l_combInt2 << "\t = \t" << std::boolalpha << (l_combInt3 + l_combInt2) << "\n";
    std::cout << " " << l_combInt3 << "\t + \t" << l_combInt4 << "\t = \t" << std::boolalpha << (l_combInt3 + l_combInt4) << "\n";

    std::cout << " " << l_combInt4 << "\t + \t" << l_combInt1 << "\t = \t" << std::boolalpha << (l_combInt4 + l_combInt1) << "\n";
    std::cout << " " << l_combInt4 << "\t + \t" << l_combInt2 << "\t = \t" << std::boolalpha << (l_combInt4 + l_combInt2) << "\n";
    std::cout << " " << l_combInt4 << "\t + \t" << l_combInt3 << "\t = \t" << std::boolalpha << (l_combInt4 + l_combInt3) << "\n";

    std::cout << " " << l_combInt1 << "\t - \t" << l_combInt2 << "\t = \t" << std::boolalpha << (l_combInt1 - l_combInt2) << "\n";
    std::cout << " " << l_combInt1 << "\t - \t" << l_combInt3 << "\t = \t" << std::boolalpha << (l_combInt1 - l_combInt3) << "\n";
    std::cout << " " << l_combInt1 << "\t - \t" << l_combInt4 << "\t = \t" << std::boolalpha << (l_combInt1 - l_combInt4) << "\n";

    std::cout << " " << l_combInt2 << "\t - \t" << l_combInt1 << "\t = \t" << std::boolalpha << (l_combInt2 - l_combInt1) << "\n";
    std::cout << " " << l_combInt2 << "\t - \t" << l_combInt3 << "\t = \t" << std::boolalpha << (l_combInt2 - l_combInt3) << "\n";
    std::cout << " " << l_combInt2 << "\t - \t" << l_combInt4 << "\t = \t" << std::boolalpha << (l_combInt2 - l_combInt4) << "\n";

    std::cout << " " << l_combInt3 << "\t - \t" << l_combInt1 << "\t = \t" << std::boolalpha << (l_combInt3 - l_combInt1) << "\n";
    std::cout << " " << l_combInt3 << "\t - \t" << l_combInt2 << "\t = \t" << std::boolalpha << (l_combInt3 - l_combInt2) << "\n";
    std::cout << " " << l_combInt3 << "\t - \t" << l_combInt4 << "\t = \t" << std::boolalpha << (l_combInt3 - l_combInt4) << "\n";

    std::cout << " " << l_combInt4 << "\t - \t" << l_combInt1 << "\t = \t" << std::boolalpha << (l_combInt4 - l_combInt1) << "\n";
    std::cout << " " << l_combInt4 << "\t - \t" << l_combInt2 << "\t = \t" << std::boolalpha << (l_combInt4 - l_combInt2) << "\n";
    std::cout << " " << l_combInt4 << "\t - \t" << l_combInt3 << "\t = \t" << std::boolalpha << (l_combInt4 - l_combInt3) << "\n";

    std::cout << " " << l_combInt1 << "\t + \t1" << "\t\t = \t"; l_combInt1.AddToElements(1); std::cout << l_combInt1 << "\n";
    std::cout << " " << l_combInt2 << "\t + \t1" << "\t\t = \t"; l_combInt2.AddToElements(1); std::cout << l_combInt2 << "\n";
    std::cout << " " << l_combInt3 << "\t + \t1" << "\t\t = \t"; l_combInt3.AddToElements(1); std::cout << l_combInt3 << "\n";
    std::cout << " " << l_combInt4 << "\t + \t1" << "\t\t = \t"; l_combInt4.AddToElements(1); std::cout << l_combInt4 << "\n";

    std::cout << " " << l_combInt1 << "\t + \t1" << "\t\t = \t"; l_combInt1.AddToElements(1); std::cout << l_combInt1 << "\n";
    std::cout << " " << l_combInt2 << "\t + \t1" << "\t\t = \t"; l_combInt2.AddToElements(1); std::cout << l_combInt2 << "\n";
    std::cout << " " << l_combInt3 << "\t + \t1" << "\t\t = \t"; l_combInt3.AddToElements(1); std::cout << l_combInt3 << "\n";
    std::cout << " " << l_combInt4 << "\t + \t1" << "\t\t = \t"; l_combInt4.AddToElements(1); std::cout << l_combInt4 << "\n";

    std::cout << " " << l_combInt1 << "\t - \t2" << "\t\t = \t"; l_combInt1.SubtractToElements(2); std::cout << l_combInt1 << "\n";
    std::cout << " " << l_combInt2 << "\t - \t2" << "\t\t = \t"; l_combInt2.SubtractToElements(2); std::cout << l_combInt2 << "\n";
    std::cout << " " << l_combInt3 << "\t - \t2" << "\t\t = \t"; l_combInt3.SubtractToElements(2); std::cout << l_combInt3 << "\n";
    std::cout << " " << l_combInt4 << "\t - \t2" << "\t\t = \t"; l_combInt4.SubtractToElements(2); std::cout << l_combInt4 << "\n";
}


int main(int argc, char* argv[])
{
    int l_exitValue = EXIT_SUCCESS;

    std::cout << "\n";

    std::cout << " " << k_programName << "\n\n";

    testFunction1();
    
    testFunction2();

    testFunction3();

    testFunction4();

    std::cout << std::endl;

    return l_exitValue;
}
