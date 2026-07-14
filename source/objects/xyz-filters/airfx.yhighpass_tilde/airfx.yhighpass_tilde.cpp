#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/yhighpass.hpp"

using TWrapped = airwindohhs::yhighpass::YHighpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.yhighpass~", airwindohhs::yhighpass::k_long_description.data());
}
