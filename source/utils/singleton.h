#pragma once

#include "utils/memory.h"
#include "utils/assert.h"

namespace ircserv
{

// These macros are used to declare simple singleton for cases where using a templated base class is not an option.
#define DECLARE_SIMPLE_SINGLETON(Type) \
    public: \
    static inline Type& GetInstance() { Assert(ms_Instance!=NULL); return *ms_Instance; } \
    static inline bool HasInstance() { return ms_Instance != NULL; } \
    static void CreateSingleton() { New(Type)(); } \
    static void DestroySingleton() { Delete(ms_Instance); } \
    private: \
    Type(const Type&); \
    Type & operator=(const Type &); \
    private: \
    static Type* ms_Instance

#define IMPLEMENT_SIMPLE_SINGLETON(Type) \
    Type* Type::ms_Instance

#define IMPLEMENT_SIMPLE_SINGLETON_CONSTRUCTOR() \
    Assert(ms_Instance == NULL);\
    ms_Instance = this

#define IMPLEMENT_SIMPLE_SINGLETON_DESTRUCTOR() \
    Assert(ms_Instance != NULL);\
    ms_Instance = NULL

}
