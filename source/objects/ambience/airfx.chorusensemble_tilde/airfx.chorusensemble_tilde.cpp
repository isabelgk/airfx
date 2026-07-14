#include "ext.h"

#include "airfx.hpp"
#include "ambience/chorusensemble.hpp"

using TWrapped = airwindohhs::chorusensemble::ChorusEnsemble<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.chorusensemble~", airwindohhs::chorusensemble::k_long_description.data());
}
