#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/xlowpass.hpp"

using TWrapped = airwindohhs::xlowpass::XLowpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.xlowpass~", airwindohhs::xlowpass::k_long_description.data());
}
