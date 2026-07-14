#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/groovewear.hpp"

using TWrapped = airwindohhs::groovewear::GrooveWear<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.groovewear~", airwindohhs::groovewear::k_long_description.data());
}
