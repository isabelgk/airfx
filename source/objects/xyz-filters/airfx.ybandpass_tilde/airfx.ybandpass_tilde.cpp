#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/ybandpass.hpp"

using TWrapped = airwindohhs::ybandpass::YBandpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ybandpass~", airwindohhs::ybandpass::k_long_description.data());
}
