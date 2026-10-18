#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/consolexchannel.hpp"

using TWrapped = airwindohhs::consolexchannel::ConsoleXChannel<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.consolexchannel~", airwindohhs::consolexchannel::k_long_description.data());
}
