#include "ext.h"

#include "airfx.hpp"
#include "ambience/stereochorus.hpp"

using TWrapped = airwindohhs::stereochorus::StereoChorus<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.stereochorus~", airwindohhs::stereochorus::k_long_description.data());
}
