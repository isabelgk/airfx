#include "ext.h"

#include "airfx.hpp"
#include "dithers/spatializedither.hpp"

using TWrapped = airwindohhs::spatializedither::SpatializeDither<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.spatializedither~", airwindohhs::spatializedither::k_long_description.data());
}
