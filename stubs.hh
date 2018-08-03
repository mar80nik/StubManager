/*
 * stubs.hh
 *
 *  Created on: 24 ш■ы. 2018 у.
 *      Author: ▐ыш 
 */

#ifndef STUBS_HH_
#define STUBS_HH_

#define ASSERT(A, B) \
    if(A != B)                                                  \
    {                                                           \
        cout << "=> ASSERT "#A" (" << A;                        \
        cout << ") == "#B" (" << B;                             \
        cout << ") failed at " << __FILE__ << ":" << __LINE__ << endl;        \
        exit(1);                                                \
    }

#define STUB_DEF(name, retType, defReturn, Arg1Type, Arg2Type)                  \
    typedef retType (*pntr_type_##name)(Arg1Type, Arg2Type);                    \
    pntr_type_##name pntr_##name = NULL;                                        \
                                                                                \
    retType name(Arg1Type arg1, Arg2Type arg2)                                  \
    {                                                                           \
        retType Ret;                                                            \
        StubManager::GetInstance().AddActualCall(#name, (void *)pntr_##name);   \
        if(pntr_##name != NULL)                                                 \
        {                                                                       \
            Ret = (*pntr_##name)(arg1, arg2);                                   \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            Ret = defReturn;                                                    \
        }                                                                       \
        return Ret;                                                             \
    }

#define STUB_ADD_EX(name, funcPntr, count)                                      \
    ASSERT((void*)pntr_##name, 0);                                              \
    pntr_##name = funcPntr;                                                     \
    StubManager::GetInstance().AddStubPointer((void **)&pntr_##name);           \
    for(int i = 0; i < count; i++ )                                             \
    {                                                                           \
        StubManager::GetInstance().AddRegisteredCall(#name, (void*)funcPntr);   \
    }

#define STUB_ADD(name, funcPntr)                                                \
        STUB_ADD_EX(name, funcPntr, 1)



#endif /* STUBS_HH_ */
