#include "ext.h"

#include "airfx.hpp"
#include "clipping/clipsoftly.hpp"

using TWrapped = airwindohhs::clipsoftly::ClipSoftly<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.clipsoftly~", airwindohhs::clipsoftly::k_long_description.data());
}
