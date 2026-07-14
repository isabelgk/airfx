#include "ext.h"

#include "airfx.hpp"
#include "subtlety/inflamer.hpp"

using TWrapped = airwindohhs::inflamer::Inflamer<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.inflamer~", airwindohhs::inflamer::k_long_description.data());
}
