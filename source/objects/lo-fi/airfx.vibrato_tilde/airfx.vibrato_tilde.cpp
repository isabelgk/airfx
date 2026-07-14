#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/vibrato.hpp"

using TWrapped = airwindohhs::vibrato::Vibrato<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.vibrato~", airwindohhs::vibrato::k_long_description.data());
}
