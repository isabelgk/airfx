#include "ext.h"

#include "airfx.hpp"
#include "consoles/consolelachannel.hpp"

using TWrapped = airwindohhs::consolelachannel::ConsoleLAChannel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolelachannel~", airwindohhs::consolelachannel::k_long_description.data());
}
