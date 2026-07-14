#include "ext.h"

#include "airfx.hpp"
#include "dynamics/drumslam.hpp"

using TWrapped = airwindohhs::drumslam::DrumSlam<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.drumslam~", airwindohhs::drumslam::k_long_description.data());
}
