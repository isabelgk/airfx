#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/pointyguitar.hpp"

using TWrapped = airwindohhs::pointyguitar::PointyGuitar<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pointyguitar~", airwindohhs::pointyguitar::k_long_description.data());
}
