#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/ynotch.hpp"

using TWrapped = airwindohhs::ynotch::YNotch<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ynotch~", airwindohhs::ynotch::k_long_description.data());
}
