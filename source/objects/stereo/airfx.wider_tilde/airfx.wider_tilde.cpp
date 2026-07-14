#include "ext.h"

#include "airfx.hpp"
#include "stereo/wider.hpp"

using TWrapped = airwindohhs::wider::Wider<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.wider~", airwindohhs::wider::k_long_description.data());
}
