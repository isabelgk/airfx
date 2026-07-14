#include "ext.h"

#include "airfx.hpp"
#include "bass/infrasonic.hpp"

using TWrapped = airwindohhs::infrasonic::Infrasonic<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.infrasonic~", airwindohhs::infrasonic::k_long_description.data());
}
