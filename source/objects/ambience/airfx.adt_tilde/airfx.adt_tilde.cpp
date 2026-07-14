#include "ext.h"

#include "airfx.hpp"
#include "ambience/adt.hpp"

using TWrapped = airwindohhs::adt::ADT<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.adt~", airwindohhs::adt::k_long_description.data());
}
