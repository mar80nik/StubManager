/*
 * StubManager.cc
 *
 *  Created on: 24 ш■ы. 2018 у.
 *      Author: ▐ыш 
 */

#include "stubs.hh"
#include "StubManager.hh"

using namespace std;

StubManager::StubManager()
{
    Reset();
}

StubManager::~StubManager() {
    // TODO Auto-generated destructor stub
}

void StubManager::Reset()
{
    cout << "Stub manager RESET" << endl;
    actualCalls.empty();
}

bool StubManager::check_stubs(StabCalls& registeredCalls)
 {
     bool ret = true;
     StabCallsIterator it;
     for (it = actualCalls.begin(); it != actualCalls.end(); )
     {
         StabCallsIterator itc;
         itc = std::find(registeredCalls.begin(), registeredCalls.end(), it);
         if(itc != registeredCalls.end())
         {
             registeredCalls.erase(itc);
             actualCalls.erase(it);
         }
         else
         {
             it++;
         }
     }
     for (it = actualCalls.begin(); it != actualCalls.end(); it++)
     {
         cout << "=> unverified call with " << it->format() << endl;
     }
     for (it = registeredCalls.begin(); it != registeredCalls.end(); it++)
     {
         cout << "=> STUB was not called with " << it->format() << endl;
     }
     ASSERT(registeredCalls.size(), 0, &ret);
     ASSERT(actualCalls.size(), 0, &ret);
     return ret;
 }
