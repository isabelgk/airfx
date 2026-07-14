#include "ext.h"

#include "airfx.hpp"
#include "utility/rightomono.hpp"

using TWrapped = airwindohhs::rightomono::RightoMono<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.rightomono~", airwindohhs::rightomono::k_long_description.data());
}
