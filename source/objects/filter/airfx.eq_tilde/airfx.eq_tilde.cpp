#include "ext.h"

#include "airfx.hpp"
#include "filter/eq.hpp"

using TWrapped = airwindohhs::eq::EQ<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.eq~", airwindohhs::eq::k_long_description.data());
}
