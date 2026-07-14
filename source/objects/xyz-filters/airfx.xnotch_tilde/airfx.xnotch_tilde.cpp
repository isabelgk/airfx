#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/xnotch.hpp"

using TWrapped = airwindohhs::xnotch::XNotch<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.xnotch~", airwindohhs::xnotch::k_long_description.data());
}
