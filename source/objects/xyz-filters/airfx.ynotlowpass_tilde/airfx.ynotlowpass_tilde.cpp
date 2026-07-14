#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/ynotlowpass.hpp"

using TWrapped = airwindohhs::ynotlowpass::YNotLowpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ynotlowpass~", airwindohhs::ynotlowpass::k_long_description.data());
}
