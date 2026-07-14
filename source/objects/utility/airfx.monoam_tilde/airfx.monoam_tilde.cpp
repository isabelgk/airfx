#include "ext.h"

#include "airfx.hpp"
#include "utility/monoam.hpp"

using TWrapped = airwindohhs::monoam::MoNoam<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.monoam~", airwindohhs::monoam::k_long_description.data());
}
