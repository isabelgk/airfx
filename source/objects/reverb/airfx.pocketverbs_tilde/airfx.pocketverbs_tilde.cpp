#include "ext.h"

#include "airfx.hpp"
#include "reverb/pocketverbs.hpp"

using TWrapped = airwindohhs::pocketverbs::PocketVerbs<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pocketverbs~", airwindohhs::pocketverbs::k_long_description.data());
}
