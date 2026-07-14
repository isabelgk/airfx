#include "ext.h"

#include "airfx.hpp"
#include "stereo/srsly.hpp"

using TWrapped = airwindohhs::srsly::Srsly<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.srsly~", airwindohhs::srsly::k_long_description.data());
}
