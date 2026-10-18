#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/consolehchannel.hpp"

using TWrapped = airwindohhs::consolehchannel::ConsoleHChannel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolehchannel~", airwindohhs::consolehchannel::k_long_description.data());
}
