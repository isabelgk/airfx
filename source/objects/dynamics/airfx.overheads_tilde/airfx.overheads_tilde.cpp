#include "ext.h"

#include "airfx.hpp"
#include "dynamics/overheads.hpp"

using TWrapped = airwindohhs::overheads::Overheads<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.overheads~", airwindohhs::overheads::k_long_description.data());
}
