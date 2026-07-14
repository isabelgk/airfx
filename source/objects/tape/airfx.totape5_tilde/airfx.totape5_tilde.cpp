#include "ext.h"

#include "airfx.hpp"
#include "tape/totape5.hpp"

using TWrapped = airwindohhs::totape5::ToTape5<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.totape5~", airwindohhs::totape5::k_long_description.data());
}
