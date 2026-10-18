#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/consolex2channel.hpp"

using TWrapped = airwindohhs::consolex2channel::ConsoleX2Channel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolex2channel~", airwindohhs::consolex2channel::k_long_description.data());
}
