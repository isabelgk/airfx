#include "ext.h"

#include "airfx.hpp"
#include "ambience/sampledelay.hpp"

using TWrapped = airwindohhs::sampledelay::SampleDelay<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.sampledelay~", airwindohhs::sampledelay::k_long_description.data());
}
