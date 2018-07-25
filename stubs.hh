/*
 * stubs.hh
 *
 *  Created on: 24 ш■ы. 2018 у.
 *      Author: ▐ыш 
 */

#ifndef STUBS_HH_
#define STUBS_HH_

#define STUB_DEF(name, retType, defReturn, Arg1Type, Arg2Type)  \
    typedef retType (*pntr_type_##name)(Arg1Type, Arg2Type);    \
    pntr_type_##name pntr_##name = NULL;                        \
    retType name(Arg1Type arg1, Arg2Type arg2)                  \
    {                                                           \
        retType Ret;                                            \
        manager.AddCall(#name, (void *)pntr_##name);            \
        if(pntr_##name != NULL)                                 \
        {                                                       \
            Ret = (*pntr_##name)(arg1, arg2);                   \
        }                                                       \
        else                                                    \
        {                                                       \
            Ret = defReturn;                                    \
        }                                                       \
        return Ret;                                             \
    }

#define STUB_ADD_EX(name, funcPntr, stubCalls, count)              \
    pntr_##name = funcPntr;                                     \
    for(int i = 0; i < count; i++ )                             \
    {                                                           \
        stubCalls.push_back(StabCall(#name,                     \
                            (void*)funcPntr));                  \
    }

#define STUB_ADD(name, funcPntr, stubCalls)                     \
        STUB_ADD_EX(name, funcPntr, stubCalls, 1)



#endif /* STUBS_HH_ */
