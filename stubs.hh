/*
 * stubs.hh
 *
 *  Created on: 24 ш■ы. 2018 у.
 *      Author: ▐ыш 
 */

#ifndef STUBS_HH_
#define STUBS_HH_

#define STUB_DEF(manager, name, retType, defReturn, Arg1Type, Arg2Type)  \
    typedef retType (*pntr_type_##name)(Arg1Type, Arg2Type);    \
    pntr_type_##name pntr_##name = NULL;                        \
                                                                \
    retType name(Arg1Type arg1, Arg2Type arg2)                  \
    {                                                           \
        retType Ret;                                            \
        manager.AddActualCall(#name, (void *)pntr_##name);      \
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

#define STUB_ADD_EX(manager, name, funcPntr, count)             \
    pntr_##name = funcPntr;                                     \
    manager.AddStubPointer((void **)&pntr_##name);              \
    for(int i = 0; i < count; i++ )                             \
    {                                                           \
        manager.AddRegisteredCall(#name, (void*)funcPntr);      \
    }

#define STUB_ADD(manager, name, funcPntr)                       \
        STUB_ADD_EX(manager, name, funcPntr, 1)



#endif /* STUBS_HH_ */
