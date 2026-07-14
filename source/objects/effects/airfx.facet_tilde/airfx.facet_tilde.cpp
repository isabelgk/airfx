#include "ext.h"

#include "airfx.hpp"
#include "effects/facet.hpp"

using TWrapped = airwindohhs::facet::Facet<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.facet~", airwindohhs::facet::k_long_description.data());
}
