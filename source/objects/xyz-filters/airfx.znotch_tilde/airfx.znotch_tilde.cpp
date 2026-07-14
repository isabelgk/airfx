#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/znotch.hpp"

using TWrapped = airwindohhs::znotch::ZNotch<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.znotch~", airwindohhs::znotch::k_long_description.data());
}
