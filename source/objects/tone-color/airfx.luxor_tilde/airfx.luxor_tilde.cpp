#include "ext.h"

#include "airfx.hpp"
#include "tone-color/luxor.hpp"

using TWrapped = airwindohhs::luxor::Luxor<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.luxor~", airwindohhs::luxor::k_long_description.data());
}
