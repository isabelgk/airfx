#include "ext.h"

#include "airfx.hpp"
#include "tone-color/channelx.hpp"

using TWrapped = airwindohhs::channelx::ChannelX<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.channelx~", airwindohhs::channelx::k_long_description.data());
}
