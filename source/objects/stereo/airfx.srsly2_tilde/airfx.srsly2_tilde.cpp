#include "ext.h"

#include "airfx.hpp"
#include "stereo/srsly2.hpp"

using TWrapped = airwindohhs::srsly2::Srsly2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.srsly2~", airwindohhs::srsly2::k_long_description.data());
}
