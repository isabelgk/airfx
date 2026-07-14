#include "ext.h"

#include "airfx.hpp"
#include "filter/weight.hpp"

using TWrapped = airwindohhs::weight::Weight<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.weight~", airwindohhs::weight::k_long_description.data());
}
