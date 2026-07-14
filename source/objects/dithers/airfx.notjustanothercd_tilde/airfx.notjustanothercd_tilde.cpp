#include "ext.h"

#include "airfx.hpp"
#include "dithers/notjustanothercd.hpp"

using TWrapped = airwindohhs::notjustanothercd::NotJustAnotherCD<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.notjustanothercd~", airwindohhs::notjustanothercd::k_long_description.data());
}
