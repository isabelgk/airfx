#include "ext.h"

#include "airfx.hpp"
#include "consoles/consolemdbuss.hpp"

using TWrapped = airwindohhs::consolemdbuss::ConsoleMDBuss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolemdbuss~", airwindohhs::consolemdbuss::k_long_description.data());
}
