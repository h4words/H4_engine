#pragma once
#include <typeinfo>
#include <unordered_map>
#include <string>
#include <Log.hpp>
namespace H4_engine
{
    class Component;
    enum FieldType
    {
        FIELD_VOID = 0,
        FIELD_INTEGER,
        FIELD_FLOAT,
        FIELD_STRING,
        FIELD_BOOLEAN
    };

    struct FieldInfo
    {
        ptrdiff_t offset;
        FieldType fieldtype;
        std::string alias;
    };

    struct DataMap
    {
        FieldInfo *fields;
        unsigned int fields_count;
    };

template<typename T, typename U> constexpr size_t offsetOf(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

    #define SIZE_OF_ARRAY(a) sizeof(a) / sizeof(a[0])

    #define DECLARE_DATADESC()                                                                 \
        static DataMap m_datamap;                                                              \
        virtual DataMap* GetDataDescMap();                                                     

    #define BEGIN_DATADESC(ClassName)                                                          \
        DataMap ClassName::m_datamap = { nullptr, 0 };                                         \
        DataMap* ClassName::GetDataDescMap() {                                                 \
            typedef ClassName ThisClass;                                                       \
            static FieldInfo fields[] = {                                                      \
                {0, FIELD_VOID, ""},
    #define DEFINE_FIELD(FieldTp, FieldName)                                                   \
                {offsetof(ThisClass, FieldName), FieldTp, #FieldName}
    #define END_DATADESC()                                                                     \
            };                                                                                 \
            if (sizeof(fields) > sizeof(fields[0]))                                            \
            {                                                                                  \
                ThisClass::m_datamap.fields_count = SIZE_OF_ARRAY( fields ) - 1;               \
                ThisClass::m_datamap.fields = &fields[1];                                      \
            }                                                                                  \
            else                                                                               \
            {                                                                                  \
                ThisClass::m_datamap.fields_count = 1;                                         \
                ThisClass::m_datamap.fields = fields;                                          \
            }                                                                                  \
            return &ThisClass::m_datamap;                                                      \
        }                                                                       
    
}