#include "ext.h"

#include "airfx.hpp"
#include "distortion/edge.hpp"

using TWrapped = airwindohhs::edge::Edge<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.edge~", airwindohhs::edge::k_long_description.data());
}
