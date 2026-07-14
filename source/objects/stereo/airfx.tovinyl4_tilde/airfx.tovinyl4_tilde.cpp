#include "ext.h"

#include "airfx.hpp"
#include "stereo/tovinyl4.hpp"

using TWrapped = airwindohhs::tovinyl4::ToVinyl4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tovinyl4~", airwindohhs::tovinyl4::k_long_description.data());
}
