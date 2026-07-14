#include "ext.h"

#include "airfx.hpp"
#include "tone-color/apicolypse.hpp"

using TWrapped = airwindohhs::apicolypse::Apicolypse<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.apicolypse~", airwindohhs::apicolypse::k_long_description.data());
}
