#include "ext.h"

#include "airfx.hpp"
#include "ambience/ensemble.hpp"

using TWrapped = airwindohhs::ensemble::Ensemble<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ensemble~", airwindohhs::ensemble::k_long_description.data());
}
