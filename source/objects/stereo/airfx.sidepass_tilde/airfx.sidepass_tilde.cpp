#include "ext.h"

#include "airfx.hpp"
#include "stereo/sidepass.hpp"

using TWrapped = airwindohhs::sidepass::Sidepass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.sidepass~", airwindohhs::sidepass::k_long_description.data());
}
