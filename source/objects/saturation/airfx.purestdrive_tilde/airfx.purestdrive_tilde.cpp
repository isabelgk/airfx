#include "ext.h"

#include "airfx.hpp"
#include "saturation/purestdrive.hpp"

using TWrapped = airwindohhs::purestdrive::PurestDrive<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestdrive~", airwindohhs::purestdrive::k_long_description.data());
}
