#include "ext.h"

#include "airfx.hpp"
#include "tone-color/channel9.hpp"

using TWrapped = airwindohhs::channel9::Channel9<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.channel9~", airwindohhs::channel9::k_long_description.data());
}
