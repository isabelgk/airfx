#include "ext.h"

#include "airfx.hpp"
#include "ambience/melt.hpp"

using TWrapped = airwindohhs::melt::Melt<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.melt~", airwindohhs::melt::k_long_description.data());
}
