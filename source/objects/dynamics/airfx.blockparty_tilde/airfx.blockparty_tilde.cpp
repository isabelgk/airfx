#include "ext.h"

#include "airfx.hpp"
#include "dynamics/blockparty.hpp"

using TWrapped = airwindohhs::blockparty::BlockParty<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.blockparty~", airwindohhs::blockparty::k_long_description.data());
}
