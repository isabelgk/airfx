#include "ext.h"

#include "airfx.hpp"
#include "filter/silken.hpp"

using TWrapped = airwindohhs::silken::Silken<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.silken~", airwindohhs::silken::k_long_description.data());
}
