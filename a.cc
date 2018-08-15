/*
 * a.cc
 *
 *  Created on: 22 ш■ы. 2018 у.
 *      Author: ▐ыш 
 */
#include <stdio.h>
#include <iostream>
#include <vector>

#include "a.hh"

using namespace std;

STUB_DEF(test10, int, 0, char, char)
STUB_DEF(test20, float, 1.1, double, char)
STUB_DEF(test30, float, 3.0, float, char)

STUB_DEF(test40, float, 3.0, float, char, int)

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
    StubManager::GetInstance().Reset();

    STUB_ADD(test10, &stub1);
    STUB_ADD_EX(test20, DEFAULT_STUB, 3);
    STUB_ADD(test30, &stub31);

    test10(1, 2);
    test20(1, 2);
    test20(1, 2);
    test30(1, 2);
    test20(1, 2);

    StubManager::GetInstance().CheckStubs();
}

void test_02()
{
    cout << "---=== Executing " << __FUNCTION__ << " ===---" << endl;
    StubManager::GetInstance().Reset();

    STUB_ADD(test10, &stub1);
    STUB_ADD_EX(test20, DEFAULT_STUB, 2);
    STUB_ADD(test30, &stub31);

    test30(1, 2);
    test10(1, 2);
    test20(1, 2);
    test20(1, 2);

    StubManager::GetInstance().CheckStubs();
}

int main()
{
    test_01();
    test_02();

    return 0;
}




