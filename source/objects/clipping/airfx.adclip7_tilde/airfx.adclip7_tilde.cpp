#include "ext.h"

#include "airfx.hpp"
#include "clipping/adclip7.hpp"

using TWrapped = airwindohhs::adclip7::ADClip7<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.adclip7~", airwindohhs::adclip7::k_long_description.data());
}
