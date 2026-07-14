#include "ext.h"

#include "airfx.hpp"
#include "reverb/reverb.hpp"

using TWrapped = airwindohhs::reverb::Reverb<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.reverb~", airwindohhs::reverb::k_long_description.data());
}
