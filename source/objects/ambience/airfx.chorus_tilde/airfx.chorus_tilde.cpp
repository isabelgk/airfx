#include "ext.h"

#include "airfx.hpp"
#include "ambience/chorus.hpp"

using TWrapped = airwindohhs::chorus::Chorus<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.chorus~", airwindohhs::chorus::k_long_description.data());
}
