/*
 * a.cc
 *
 *  Created on: 22 ш■ы. 2018 у.
 *      Author: ▐ыш 
 */
#include <stdio.h>
#include <iostream>
#include <vector>

#include "stubs.hh"
#include "StubManager.hh"

using namespace std;

#define LOG_STUB_CALL(name, ...)                                \
    cout << "Calling "#name" = " << name(__VA_ARGS__) << endl

StubManager manager;

STUB_DEF(test10, int, 0, char, char);
STUB_DEF(test20, float, 1.1, double, char);
STUB_DEF(test30, float, 3.0, float, char);

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

int main()
{
    StabCalls calls;

    manager.Reset();
    calls.empty();

    STUB_ADD(test10, &stub1, calls);
    STUB_ADD_EX(test20, NULL, calls, 3);
    STUB_ADD(test30, &stub31, calls);

    LOG_STUB_CALL(test10, 1, 2);
    LOG_STUB_CALL(test20, 1, 2);
    LOG_STUB_CALL(test20, 1, 2);
    LOG_STUB_CALL(test30, 1, 2);

    manager.Reset();
    calls.empty();

    STUB_ADD(test30, &stub31, calls);

    LOG_STUB_CALL(test10, 1, 2);
    LOG_STUB_CALL(test20, 1, 2);
    LOG_STUB_CALL(test20, 1, 2);

    manager.check_stubs(calls);
    return 0;
}



