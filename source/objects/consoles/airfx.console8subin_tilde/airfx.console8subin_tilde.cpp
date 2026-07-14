#include "ext.h"

#include "airfx.hpp"
#include "consoles/console8subin.hpp"

using TWrapped = airwindohhs::console8subin::Console8SubIn<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console8subin~", airwindohhs::console8subin::k_long_description.data());
}
