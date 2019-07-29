#ifndef YSP_UTILITY_H_
#define YSP_UTILITY_H_

#include <functional>

#define ARRAR_SIZE(_A) (sizeof(_A)/sizeof(_A[0]))

/*
返回值就是member元素的地址的偏移量
1）TYPE是结构体类型，MEMBER是结构体中一个元素的元素名
2）这个宏返回的是member元素相对于整个结构体变量的首地址的偏移量，类型是int
*/
#define OFFSET_OF(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

/*
（1）ptr是指向结构体元素member的指针，type是结构体类型，member是结构体
中一个元素的元素名
（2）这个宏返回的就是指向整个结构体变量的指针，类型是(type *)
*/
#define CONTAINER_OF(ptr, type, member) ({\
const typeof(((type *)0)->member) * __mptr = (ptr);\
(type *)((char *)__mptr - OFFSET_OF(type, member)); }


#define CODE_DESC(_X, _V) (_V)
#define CODE_USED       1
#define CODE_UNUSED     0

#if CODE_DESC("scope-guard", CODE_USED)
/*
------------------HOW TO USE IT
一种是用ON_SCOPE_EXIT宏生成的，不需要dismiss，好处是自动生成唯一对象名。
但是也让这个方法不能从外部调用
Acquire Resource1
ON_SCOPE_EXIT([&] {  Release Resource1 })


另一种是自己生成ScopeGuard对象，这样容易调用dismiss方法；
ScopeGuard onFailureRollback([&] {  rollback  });
... // do something that could fail
onFailureRollback.Dismiss();
*/
#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)
#define ON_SCOPE_EXIT_POINTER(_pointer) ON_SCOPE_EXIT([&_pointer]{ delete _pointer;})
class ScopeGuard
{
public:
    typedef std::function<void()> ScopeFunc_T;
    explicit ScopeGuard(ScopeFunc_T onExitScope) :
        m_funcOnExitScope_(onExitScope),
        m_bDissmissed_(false)
    { }

    ~ScopeGuard()
    {
        if (!m_bDissmissed_) {
            m_funcOnExitScope_();
        }
    }

    void dismiss()
    {
        m_bDissmissed_ = true;
    }

private:
    ScopeGuard(ScopeGuard const&) = delete;
    ScopeGuard& operator=(ScopeGuard const&) = delete;

    ScopeFunc_T m_funcOnExitScope_;
    bool        m_bDissmissed_;
};
#endif

#if CODE_DESC("NoCopy", CODE_USED)
class NoCopy {
public:
    NoCopy() = default;
private:
    NoCopy(const NoCopy&) = delete;
    NoCopy& operator=(const NoCopy&) = delete;
};

template<typename T>
class NoCopyTemplate
{
public:
    NoCopyTemplate() = default;
private:
    NoCopyTemplate(const NoCopyTemplate&) = delete;
    NoCopyTemplate& operator=(const NoCopyTemplate&) = delete;
};
#endif  //"NoCopy"

void printMemory(const char *buf, int len);

namespace utility{

}   //utility

#endif  //YSP_UTILITY_H_