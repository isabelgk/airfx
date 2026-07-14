#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/xhighpass.hpp"

using TWrapped = airwindohhs::xhighpass::XHighpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.xhighpass~", airwindohhs::xhighpass::k_long_description.data());
}
