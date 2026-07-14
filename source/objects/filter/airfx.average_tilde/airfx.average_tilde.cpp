#include "ext.h"

#include "airfx.hpp"
#include "filter/average.hpp"

using TWrapped = airwindohhs::average::Average<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.average~", airwindohhs::average::k_long_description.data());
}
