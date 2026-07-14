#include "ext.h"

#include "airfx.hpp"
#include "tape/tapehack.hpp"

using TWrapped = airwindohhs::tapehack::TapeHack<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tapehack~", airwindohhs::tapehack::k_long_description.data());
}
