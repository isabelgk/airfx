#include "ext.h"

#include "airfx.hpp"
#include "brightness/ultrasonic.hpp"

using TWrapped = airwindohhs::ultrasonic::Ultrasonic<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ultrasonic~", airwindohhs::ultrasonic::k_long_description.data());
}
