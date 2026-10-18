#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/consolex2buss.hpp"

using TWrapped = airwindohhs::consolex2buss::ConsoleX2Buss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolex2buss~", airwindohhs::consolex2buss::k_long_description.data());
}
