#include "ext.h"

#include "airfx.hpp"
#include "filter/donut.hpp"

using TWrapped = airwindohhs::donut::Donut<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.donut~", airwindohhs::donut::k_long_description.data());
}
