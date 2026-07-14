#include "ext.h"

#include "airfx.hpp"
#include "consoles/console8channelhype.hpp"

using TWrapped = airwindohhs::console8channelhype::Console8ChannelHype<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.console8channelhype~", airwindohhs::console8channelhype::k_long_description.data());
}
