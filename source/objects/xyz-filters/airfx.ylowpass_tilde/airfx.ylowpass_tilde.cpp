#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/ylowpass.hpp"

using TWrapped = airwindohhs::ylowpass::YLowpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ylowpass~", airwindohhs::ylowpass::k_long_description.data());
}
