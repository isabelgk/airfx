#include "ext.h"

#include "airfx.hpp"
#include "clipping/adclip8.hpp"

using TWrapped = airwindohhs::adclip8::ADClip8<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.adclip8~", airwindohhs::adclip8::k_long_description.data());
}
