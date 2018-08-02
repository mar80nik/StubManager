/*
 * StubManager.hh
 *
 *  Created on: 24 ш■ы. 2018 у.
 *      Author: ▐ыш 
 */

#ifndef STUBMANAGER_HH_
#define STUBMANAGER_HH_

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#define DEFAULT_STUB NULL

#define ASSERT(A, B, pRet)                                      \
    if(A != B)                                                  \
    {                                                           \
        cout << "=> ASSERT "#A" (" << A;                        \
        cout << ") == "#B" (" << B;                             \
        cout << ") failed at LINE " << __LINE__ << endl;        \
        *pRet &= false;                                         \
    }                                                           \
    else                                                        \
    {                                                           \
        *pRet &= true;                                          \
    }

struct StabCall
{
protected:
    std::string func_name;
    void * func_pntr;
public:
    StabCall() {}
    StabCall(const std::string& name, void * pntr):
        func_name(name), func_pntr(pntr)
    {}
    bool operator==(const StabCall& call) const
    {
        return (call.func_name == func_name) && (call.func_pntr == func_pntr);
    }
    bool operator==(std::vector<StabCall>::iterator it) const
    {
        return (it->func_name == func_name) && (it->func_pntr == func_pntr);
    }
    std::string format() const
    {
        std::ostringstream out;
        out << "["<< func_name << ";" << func_pntr << "]";
        return out.str();

    }
};
typedef std::vector<StabCall> StabCalls;
typedef StabCalls::iterator StabCallsIterator;
typedef std::vector<void **> StabsPointers;
typedef StabsPointers::iterator StabsPointersIterator;

class StubManager
{
	StabCalls actualCalls;
    StabCalls registeredCalls;
    StabsPointers stubsPointers;
public:
    StubManager();
    virtual ~StubManager();
    void Reset();
	void ResetStubs();
	void ResetActualCalls();
	void ResetRegisteredCalls();
	void AddStubPointer(void** pntr);
	void AddActualCall(const std::string& func_name, void* func_pntr);
	void AddRegisteredCall(const std::string& func_name, void* func_pntr);
    bool CheckStubs();
};

extern StubManager stubManager;
#endif /* STUBMANAGER_HH_ */
