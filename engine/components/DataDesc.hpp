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
        FIELD_BOOLEAN,
        FIELD_VECTOR,
        FIELD_COLOR
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
        std::string component_name;
        DataMap *base_map;
    };

    template <typename T> 
    void DataMapAccess(T *ignored, DataMap **p)
    {
        *p = &T::m_datamap;
    }

    #define SIZE_OF_ARRAY(a) sizeof(a) / sizeof(a[0])

    #define DECLARE_COMPONENT(n)                                                               \
        virtual std::string GetName()                                                          \
        {                                                                                      \
            return #n;                                                                         \
        }

    #define DECLARE_DATADESC()                                                                 \
        static DataMap m_datamap;                                                              \
        virtual DataMap* GetDataDescMap();                                                     \
        static DataMap* GetBaseMap();                                                          \
        template <typename T> friend DataMap* DataMapInit(T *);

    #define BEGIN_DATADESC(ClassName)                                                          \
        DataMap ClassName::m_datamap = { nullptr, 0 };                                         \
        DataMap* ClassName::GetDataDescMap() { return &m_datamap; }                            \
        DataMap* ClassName::GetBaseMap() { DataMap *res; DataMapAccess((Component*)NULL, &res); return res; } \
        BEGIN_DATADESC_GUTS(ClassName)

    #define BEGIN_DATADESC_BASE(ClassName, BaseClass)                                          \
        DataMap ClassName::m_datamap = { nullptr, 0 };                                         \
        DataMap* ClassName::GetDataDescMap() { return &m_datamap; }                            \
        DataMap* ClassName::GetBaseMap() { DataMap *res; DataMapAccess((BaseClass*)NULL, &res); return res; } \
        BEGIN_DATADESC_GUTS(ClassName)

    #define BEGIN_DATADESC_NOBASE(ClassName)                                                   \
        DataMap ClassName::m_datamap = { nullptr, 0 };                                         \
        DataMap* ClassName::GetDataDescMap() { return &m_datamap; }                            \
        DataMap* ClassName::GetBaseMap() { return NULL; }                                      \
        BEGIN_DATADESC_GUTS(ClassName)
    
    #define BEGIN_DATADESC_GUTS(ClassName)                                                     \
        template <typename T> DataMap *DataMapInit(T *);                                       \
        template <> DataMap *DataMapInit<ClassName>(ClassName *);                              \
        namespace ClassName##_DataDescInit                                                     \
        {                                                                                      \
            DataMap *holder = DataMapInit((ClassName *)NULL);                                  \
        }                                                                                      \
        template <> DataMap *DataMapInit<ClassName>(ClassName *) {                             \
            typedef ClassName ThisClass;                                                       \
            ThisClass::m_datamap.component_name = #ClassName;                                  \
            ThisClass::m_datamap.base_map = ThisClass::GetBaseMap();                           \
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
                ThisClass::m_datamap.fields_count = 0;                                         \
                ThisClass::m_datamap.fields = fields;                                          \
            }                                                                                  \
            return &ThisClass::m_datamap;                                                      \
        }                                                                       
    
}