#include "ext.h"

#include "airfx.hpp"
#include "stereo/srsly3.hpp"

using TWrapped = airwindohhs::srsly3::Srsly3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.srsly3~", airwindohhs::srsly3::k_long_description.data());
}
