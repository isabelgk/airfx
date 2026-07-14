#include "ext.h"

#include "airfx.hpp"
#include "tape/totape7.hpp"

using TWrapped = airwindohhs::totape7::ToTape7<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.totape7~", airwindohhs::totape7::k_long_description.data());
}
