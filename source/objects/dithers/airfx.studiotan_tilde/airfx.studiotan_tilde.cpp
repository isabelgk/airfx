#include "ext.h"

#include "airfx.hpp"
#include "dithers/studiotan.hpp"

using TWrapped = airwindohhs::studiotan::StudioTan<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.studiotan~", airwindohhs::studiotan::k_long_description.data());
}
