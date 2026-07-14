#include "ext.h"

#include "airfx.hpp"
#include "tape/tapehack2.hpp"

using TWrapped = airwindohhs::tapehack2::TapeHack2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tapehack2~", airwindohhs::tapehack2::k_long_description.data());
}
