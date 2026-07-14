#include "ext.h"

#include "airfx.hpp"
#include "consoles/console8litebuss.hpp"

using TWrapped = airwindohhs::console8litebuss::Console8LiteBuss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console8litebuss~", airwindohhs::console8litebuss::k_long_description.data());
}
