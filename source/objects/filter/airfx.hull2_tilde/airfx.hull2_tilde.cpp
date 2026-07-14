#include "ext.h"

#include "airfx.hpp"
#include "filter/hull2.hpp"

using TWrapped = airwindohhs::hull2::Hull2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hull2~", airwindohhs::hull2::k_long_description.data());
}
