#ifndef ITUENGINE_MACROS_H
#define ITUENGINE_MACROS_H

#include <list>
#include <algorithm>
using namespace std;

// Macro to declare an event interface. Generates declarations for ctor/dtor.
#define DECLARE_EVENT_INTERFACE(name)                              \
protected:                                                         \
    name() { }                                                     \
    virtual ~name() = 0;                                           \

// Macro to implement event interface. Defines dtor
#define IMPLEMENT_EVENT_INTERFACE(name)                            \
    inline name::~name() { }                                       \

// Macros to define events that use 0, 1 or 2 parameters. If you need more
// than two, you should define a struct/class and pass a pointer to it.

// Event with no args: Declare OnFoo handler and Foo functor.
#define DEFINE_NO_ARG_EVENT(iface,name)                           \
virtual void On##name() { };                                      \
class name : public unary_function<iface*, void> {                \
public:                                                           \
    name() { }                                                    \
    void operator()(iface* obj)                                   \
    {                                                             \
        obj->On##name();                                          \
    }                                                             \
};                                                                \

// Event with one arg: Declare OnFoo handler and Foo functor.
#define DEFINE_1_ARG_EVENT(iface,name,T1)                         \
virtual void On##name(T1) { }                                     \
class name : public unary_function<iface*, void> {                \
protected:                                                        \
    T1 m_arg1;                                                    \
public:                                                           \
    name(T1 a1) : m_arg1(a1) { }                                  \
    void operator()(iface* obj)                                   \
    {                                                             \
        obj->On##name(m_arg1);                                    \
    }                                                             \
};                                                                \

// Event with two args: Declare OnFoo handler and Foo functor.
#define DEFINE_2_ARG_EVENT(iface,name,T1,T2)                      \
virtual void On##name(T1, T2) { }                                 \
class name : public unary_function<iface*, void> {                \
protected:                                                        \
    T1 m_arg1;                                                    \
    T2 m_arg2;                                                    \
public:                                                           \
    name(T1 a1, T2 a2) : m_arg1(a1), m_arg2(a2) { }               \
    void operator()(iface* obj)                                   \
    {                                                             \
        obj->On##name(m_arg1, m_arg2);                            \
    }                                                             \
}; 


#endif