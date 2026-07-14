#include "ext.h"

#include "airfx.hpp"
#include "distortion/mackity.hpp"

using TWrapped = airwindohhs::mackity::Mackity<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.mackity~", airwindohhs::mackity::k_long_description.data());
}
