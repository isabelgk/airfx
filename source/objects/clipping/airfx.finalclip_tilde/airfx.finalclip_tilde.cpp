#include "ext.h"

#include "airfx.hpp"
#include "clipping/finalclip.hpp"

using TWrapped = airwindohhs::finalclip::FinalClip<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.finalclip~", airwindohhs::finalclip::k_long_description.data());
}
