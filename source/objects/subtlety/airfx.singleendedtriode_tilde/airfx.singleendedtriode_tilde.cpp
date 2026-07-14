#include "ext.h"

#include "airfx.hpp"
#include "subtlety/singleendedtriode.hpp"

using TWrapped = airwindohhs::singleendedtriode::SingleEndedTriode<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.singleendedtriode~", airwindohhs::singleendedtriode::k_long_description.data());
}
