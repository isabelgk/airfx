#include "ext.h"

#include "airfx.hpp"
#include "dithers/ditherbox.hpp"

using TWrapped = airwindohhs::ditherbox::Ditherbox<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ditherbox~", airwindohhs::ditherbox::k_long_description.data());
}
