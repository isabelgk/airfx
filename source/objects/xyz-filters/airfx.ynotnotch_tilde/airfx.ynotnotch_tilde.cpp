#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/ynotnotch.hpp"

using TWrapped = airwindohhs::ynotnotch::YNotNotch<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ynotnotch~", airwindohhs::ynotnotch::k_long_description.data());
}
