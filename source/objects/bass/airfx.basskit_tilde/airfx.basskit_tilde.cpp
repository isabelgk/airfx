#include "ext.h"

#include "airfx.hpp"
#include "bass/basskit.hpp"

using TWrapped = airwindohhs::basskit::BassKit<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.basskit~", airwindohhs::basskit::k_long_description.data());
}
