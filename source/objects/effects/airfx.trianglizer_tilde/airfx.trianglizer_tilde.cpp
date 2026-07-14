#include "ext.h"

#include "airfx.hpp"
#include "effects/trianglizer.hpp"

using TWrapped = airwindohhs::trianglizer::Trianglizer<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.trianglizer~", airwindohhs::trianglizer::k_long_description.data());
}
