#include "ext.h"

#include "airfx.hpp"
#include "distortion/zoom.hpp"

using TWrapped = airwindohhs::zoom::Zoom<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zoom~", airwindohhs::zoom::k_long_description.data());
}
