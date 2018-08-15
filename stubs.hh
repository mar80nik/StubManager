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

#define STUB_MANAGER_ADD_ACTUAL_CALL(name) \
    union {void * pntr; pntr_type_##name func_pntr;} converter; \
    converter.func_pntr = pntr_##name; \
    StubManager::GetInstance().AddActualCall(#name, converter.pntr)   \


#define STUB_DEC(name, retType, defReturn, ...)                  \
    typedef retType (*pntr_type_##name)(__VA_ARGS__);                    \
    extern pntr_type_##name pntr_##name;
/********************************************************************/
#define FUN_CALL(name, retType, defReturn, ...) \
    retType Ret = defReturn;                                                            \
    if(pntr_##name != NULL)                                                 \
    {                                                                       \
        Ret = (*pntr_##name)(__VA_ARGS__);                                   \
    }                                                                       \
    return Ret;

#define VOID_FUN_CALL(name, retType, defReturn, ...) \
    if(pntr_##name != NULL)                                                 \
    {                                                                       \
        (*pntr_##name)(__VA_ARGS__);                                   \
    }                                                                       \
    return;

/********************************************************************/
#define STUB_DEF(name, retType, defReturn, ...)                  \
    STUB_DEF_1(COUNT(__VA_ARGS__), name, retType, defReturn, __VA_ARGS__)
#define STUB_DEF_1(N, name, retType, defReturn, ...)                  \
    pntr_type_##name pntr_##name = NULL;                                        \
    STUB_DEF_2(N, name, retType, defReturn, __VA_ARGS__)
#define STUB_DEF_2(N, name, retType, defReturn, ...)                  \
    retType name(GET_TYPE_NAME_ARGS(N, __VA_ARGS__))                                  \
    {                                                                           \
        STUB_MANAGER_ADD_ACTUAL_CALL(name); \
        FUN_CALL(name, retType, defReturn, GET_NAME_ARGS(N, __VA_ARGS__))  \
    }

#define FOREACH1(FUN, N, A) \
    FUN(N, A)
#define FOREACH2(FUN, N, A, ...) \
    FUN(N, A), FOREACH1(FUN, 1, __VA_ARGS__)
#define FOREACH3(FUN, N, A, ...) \
    FUN(N, A), FOREACH2(FUN, 2, __VA_ARGS__)

#define NAME_ARG(N, _TYPE) a##N
#define TYPE_NAME_ARG(N, TYPE) TYPE NAME_ARG(N, TYPE)

#define GET_TYPE_NAME_ARGS(N, ...) \
    FOREACH##N(TYPE_NAME_ARG, N, __VA_ARGS__)
#define GET_NAME_ARGS(N, ...) \
    FOREACH##N(NAME_ARG, N, __VA_ARGS__)
/********************************************************************/
#define COUNT(...) COUNT_(__VA_ARGS__, 3,2,1)
#define COUNT_(_1,_2,_3,N,...) N
/********************************************************************/




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
