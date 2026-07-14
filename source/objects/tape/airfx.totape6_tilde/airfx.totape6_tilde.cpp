#include "ext.h"

#include "airfx.hpp"
#include "tape/totape6.hpp"

using TWrapped = airwindohhs::totape6::ToTape6<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.totape6~", airwindohhs::totape6::k_long_description.data());
}
