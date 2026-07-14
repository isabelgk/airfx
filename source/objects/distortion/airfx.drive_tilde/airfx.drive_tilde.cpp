#include "ext.h"

#include "airfx.hpp"
#include "distortion/drive.hpp"

using TWrapped = airwindohhs::drive::Drive<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.drive~", airwindohhs::drive::k_long_description.data());
}
