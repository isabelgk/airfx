#include "ext.h"

#include "airfx.hpp"
#include "brightness/ultrasonicmed.hpp"

using TWrapped = airwindohhs::ultrasonicmed::UltrasonicMed<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ultrasonicmed~", airwindohhs::ultrasonicmed::k_long_description.data());
}
