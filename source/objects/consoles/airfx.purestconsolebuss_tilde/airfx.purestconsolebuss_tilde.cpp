#include "ext.h"

#include "airfx.hpp"
#include "consoles/purestconsolebuss.hpp"

using TWrapped = airwindohhs::purestconsolebuss::PurestConsoleBuss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestconsolebuss~", airwindohhs::purestconsolebuss::k_long_description.data());
}
