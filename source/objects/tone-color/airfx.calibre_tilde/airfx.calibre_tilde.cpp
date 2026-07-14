#include "ext.h"

#include "airfx.hpp"
#include "tone-color/calibre.hpp"

using TWrapped = airwindohhs::calibre::Calibre<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.calibre~", airwindohhs::calibre::k_long_description.data());
}
