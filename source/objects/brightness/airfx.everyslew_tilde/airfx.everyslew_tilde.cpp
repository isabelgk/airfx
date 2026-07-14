#include "ext.h"

#include "airfx.hpp"
#include "brightness/everyslew.hpp"

using TWrapped = airwindohhs::everyslew::EverySlew<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.everyslew~", airwindohhs::everyslew::k_long_description.data());
}
