#include "ext.h"

#include "airfx.hpp"
#include "ambience/triplespread.hpp"

using TWrapped = airwindohhs::triplespread::TripleSpread<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.triplespread~", airwindohhs::triplespread::k_long_description.data());
}
