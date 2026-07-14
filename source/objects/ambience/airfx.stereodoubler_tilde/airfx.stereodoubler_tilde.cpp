#include "ext.h"

#include "airfx.hpp"
#include "ambience/stereodoubler.hpp"

using TWrapped = airwindohhs::stereodoubler::StereoDoubler<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.stereodoubler~", airwindohhs::stereodoubler::k_long_description.data());
}
