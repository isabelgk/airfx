#include "ext.h"

#include "airfx.hpp"
#include "tape/totape9.hpp"

using TWrapped = airwindohhs::totape9::ToTape9<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.totape9~", airwindohhs::totape9::k_long_description.data());
}
