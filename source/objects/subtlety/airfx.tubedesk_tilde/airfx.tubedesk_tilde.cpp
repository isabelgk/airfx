#include "ext.h"

#include "airfx.hpp"
#include "subtlety/tubedesk.hpp"

using TWrapped = airwindohhs::tubedesk::TubeDesk<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tubedesk~", airwindohhs::tubedesk::k_long_description.data());
}
