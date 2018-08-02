/*
 * StubManager.cc
 *
 *  Created on: 24 ш■ы. 2018 у.
 *      Author: ▐ыш 
 */

#include "stubs.hh"
#include "StubManager.hh"

#define DEBUG(A) /* A */

using namespace std;

StubManager::StubManager()
{
    Reset();
}

StubManager::~StubManager()
{
}

void StubManager::Reset()
{
    cout << "Stub manager RESET" << endl;
    ResetActualCalls();
    ResetRegisteredCalls();
    ResetStubs();
}

bool StubManager::CheckStubs()
 {
     bool ret = true;
     StabCallsIterator it;

     cout << "=================================================" << endl;
     cout << "Start to check stubs..." << endl;
     DEBUG(cout << "Calls to check: " << actualCalls.size() << endl);
     DEBUG(cout << "Stubs to check: " << registeredCalls.size() << endl);
     DEBUG(cout << "Stub pointers : " << stubsPointers.size() << endl);

     for (it = actualCalls.begin(); it != actualCalls.end(); )
     {
         StabCallsIterator itc;
         itc = std::find(registeredCalls.begin(), registeredCalls.end(), it);
         if(itc != registeredCalls.end())
         {
             registeredCalls.erase(itc);
             actualCalls.erase(it);
             DEBUG(cout << it->format() << " => OK" << endl);
         }
         else
         {
             cout << it->format() << " => unverified call" << endl;
             it++;
         }
     }
     for (it = registeredCalls.begin(); it != registeredCalls.end(); it++)
     {
         cout << "=> STUB was not called with " << it->format() << endl;
     }
     ASSERT(registeredCalls.size(), 0, &ret);
     ASSERT(actualCalls.size(), 0, &ret);
     cout << "=================================================" << endl;
     return ret;
}

void StubManager::AddActualCall(const std::string& func_name, void* func_pntr)
{
    DEBUG(std::cout << "Calling " << func_name << " as " << func_pntr << std::endl);
	actualCalls.push_back(StabCall(func_name, func_pntr));
}
void StubManager::AddRegisteredCall(const std::string& func_name, void* func_pntr)
{
    DEBUG(std::cout << "Register call for " << func_name << " with " << func_pntr << std::endl);
	registeredCalls.push_back(StabCall(func_name, func_pntr));
}
void StubManager::AddStubPointer(void** pntr)
{
    DEBUG(std::cout << "Add stub pointer like " << pntr << std::endl);
    stubsPointers.push_back(pntr);
}

void StubManager::ResetActualCalls()
{
	if (actualCalls.size() != 0)
	{
		DEBUG(cout << "Reseting all (" << actualCalls.size() << ") the actualCalls" << endl);
		actualCalls.clear();
	}
	return;
}
void StubManager::ResetRegisteredCalls()
{
	if (registeredCalls.size() != 0)
	{
		DEBUG(cout << "Reseting all (" << registeredCalls.size() << ") the registeredCalls" << endl);
		registeredCalls.clear();
	}
	return;
}
void StubManager::ResetStubs()
{
    if (stubsPointers.size() != 0)
    {
        StabsPointersIterator it;
        DEBUG(cout << "Reseting all (" << stubsPointers.size() << ") the stubs" << endl);
        for (it = stubsPointers.begin(); it != stubsPointers.end(); it++)
        {
            void ** tmp = *it;
            *tmp = NULL;
        }
        stubsPointers.clear();
    }
    return;
}
