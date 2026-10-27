#include "ext.h"

#include "airfx.hpp"
#include "ambience/echojam.hpp"

using TWrapped = airwindohhs::echojam::Echojam<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.echojam~", airwindohhs::echojam::k_long_description.data());
}
