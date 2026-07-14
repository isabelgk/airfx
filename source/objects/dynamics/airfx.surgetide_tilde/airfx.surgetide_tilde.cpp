#include "ext.h"

#include "airfx.hpp"
#include "dynamics/surgetide.hpp"

using TWrapped = airwindohhs::surgetide::SurgeTide<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.surgetide~", airwindohhs::surgetide::k_long_description.data());
}
