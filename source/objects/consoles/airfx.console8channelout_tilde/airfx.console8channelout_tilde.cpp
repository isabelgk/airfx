#include "ext.h"

#include "airfx.hpp"
#include "consoles/console8channelout.hpp"

using TWrapped = airwindohhs::console8channelout::Console8ChannelOut<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console8channelout~", airwindohhs::console8channelout::k_long_description.data());
}
