#include "ext.h"

#include "airfx.hpp"
#include "ambience/stereoensemble.hpp"

using TWrapped = airwindohhs::stereoensemble::StereoEnsemble<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.stereoensemble~", airwindohhs::stereoensemble::k_long_description.data());
}
