#include "ext.h"

#include "airfx.hpp"
#include "consoles/consolelabuss.hpp"

using TWrapped = airwindohhs::consolelabuss::ConsoleLABuss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolelabuss~", airwindohhs::consolelabuss::k_long_description.data());
}
