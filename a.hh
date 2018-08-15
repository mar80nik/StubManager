/*
 * a.hh
 *
 *  Created on: 13 рту. 2018 у.
 *      Author: asfod_000
 */

#ifndef A_HH_
#define A_HH_

#include "StubManager.hh"
#include "stubs.hh"

STUB_DEC(test10, int, 0, char, char)
STUB_DEC(test20, float, 1.1, double, char)
STUB_DEC(test30, float, 3.0, float, char)

STUB_DEC(test40, float, 3.0, float, char, int)

#endif /* A_HH_ */
