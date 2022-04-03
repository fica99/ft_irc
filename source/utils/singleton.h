#pragma once

#include "utils/memory.h"
#include "utils/assert.h"

namespace ircserv
{

// These macros are used to declare simple singleton for cases where using a templated base class is not an option.
#define POP_DECLARE_SIMPLE_SINGLETON(Type) \
    public: \
    static inline Type& GetInstance() { popAssert(ms_Instance!=NULL); return *ms_Instance; } \
    static inline bool HasInstance() { return ms_Instance != NULL; } \
    static void CreateSingleton() { popNew(Type)(); } \
    static void DestroySingleton() { popDelete(ms_Instance); } \
    private: \
    Type(const Type&); \
    Type & operator=(const Type &); \
    private: \
    static Type* ms_Instance

#define POP_IMPLEMENT_SIMPLE_SINGLETON(Type) \
    Type* Type::ms_Instance

#define POP_IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR() \
    popAssert(ms_Instance == NULL);\
    ms_Instance = this

#define POP_IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR() \
    popAssert(ms_Instance != NULL);\
    ms_Instance = NULL

}
