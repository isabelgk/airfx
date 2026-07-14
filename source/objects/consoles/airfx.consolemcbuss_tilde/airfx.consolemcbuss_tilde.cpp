#include "ext.h"

#include "airfx.hpp"
#include "consoles/consolemcbuss.hpp"

using TWrapped = airwindohhs::consolemcbuss::ConsoleMCBuss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolemcbuss~", airwindohhs::consolemcbuss::k_long_description.data());
}
