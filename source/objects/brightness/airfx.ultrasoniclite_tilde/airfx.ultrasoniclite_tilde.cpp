#include "ext.h"

#include "airfx.hpp"
#include "brightness/ultrasoniclite.hpp"

using TWrapped = airwindohhs::ultrasoniclite::UltrasonicLite<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ultrasoniclite~", airwindohhs::ultrasoniclite::k_long_description.data());
}
