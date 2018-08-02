/*
 * a.cc
 *
 *  Created on: 22 ш■ы. 2018 у.
 *      Author: ▐ыш 
 */
#include <stdio.h>
#include <iostream>
#include <vector>

#define LOG_STUB_CALL(name, ...)                                        \
    std::cout << "Calling "#name" = " << name(__VA_ARGS__) << std::endl

#include "StubManager.hh"
#include "stubs.hh"

using namespace std;

StubManager stubManager;

STUB_DEF(stubManager, test10, int, 0, char, char);
STUB_DEF(stubManager, test20, float, 1.1, double, char);
STUB_DEF(stubManager, test30, float, 3.0, float, char);

int stub1(char arg1, char arg2)
{
    (void)arg1;
    (void)arg2;
    return 1;
}

float stub31(float arg1, char arg2)
{
    (void)arg1;
    (void)arg2;
    return 3.1;
}

void test_01()
{
    cout << "---=== Executing " << __FUNCTION__ << " ===---" << endl;
    stubManager.Reset();

    STUB_ADD(stubManager, test10, &stub1);
    STUB_ADD_EX(stubManager, test20, DEFAULT_STUB, 3);
    STUB_ADD(stubManager, test30, &stub31);

    test10(1, 2);
    test20(1, 2);
    test20(1, 2);
    test30(1, 2);
    test20(1, 2);

    stubManager.CheckStubs();
}

void test_02()
{
    cout << "---=== Executing " << __FUNCTION__ << " ===---" << endl;
    stubManager.Reset();

    STUB_ADD(stubManager, test10, &stub1);
    STUB_ADD_EX(stubManager, test20, DEFAULT_STUB, 2);
    STUB_ADD(stubManager, test30, &stub31);

    test30(1, 2);
    test10(1, 2);
    test20(1, 2);
    test20(1, 2);

    stubManager.CheckStubs();
}

int main()
{
    test_01();
    test_02();

    return 0;
}




