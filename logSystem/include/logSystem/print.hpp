#include <logSystem/core.hpp>

#ifndef COMMON_LOG_SYSTEM_PRINT_IMPL_H
#define COMMON_LOG_SYSTEM_PRINT_IMPL_H

namespace logSystem
{
    template <class... Args>
    void logSystem::print(const Args &...args)
    {
        PrintSystem p(args...);
        p.print();
    }

    template <class HeadClass, class... TailClass>
    void PrintSystem::_extractStr(const HeadClass &head, TailClass &...tail)
    {
        _text_list->append(dataObject::toString(head));
        _extractStr(tail...);
    }

    template <class... Args>
    PrintSystem::PrintSystem(const Args &...args)
    {
        _text_list = new dataObject::List<dataObject::String>();
        _extractStr(args...);
    }
}
#endif