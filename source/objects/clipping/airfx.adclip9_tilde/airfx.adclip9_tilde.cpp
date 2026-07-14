#include "ext.h"

#include "airfx.hpp"
#include "clipping/adclip9.hpp"

using TWrapped = airwindohhs::adclip9::ADClip9<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.adclip9~", airwindohhs::adclip9::k_long_description.data());
}
