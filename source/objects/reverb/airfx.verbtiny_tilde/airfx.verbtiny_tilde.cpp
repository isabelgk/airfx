#include "ext.h"

#include "airfx.hpp"
#include "reverb/verbtiny.hpp"

using TWrapped = airwindohhs::verbtiny::VerbTiny<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.verbtiny~", airwindohhs::verbtiny::k_long_description.data());
}
