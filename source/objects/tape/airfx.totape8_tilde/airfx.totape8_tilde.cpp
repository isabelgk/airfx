#include "ext.h"

#include "airfx.hpp"
#include "tape/totape8.hpp"

using TWrapped = airwindohhs::totape8::ToTape8<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.totape8~", airwindohhs::totape8::k_long_description.data());
}
