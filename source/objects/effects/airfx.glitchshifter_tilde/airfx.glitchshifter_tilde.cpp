#include "ext.h"

#include "airfx.hpp"
#include "effects/glitchshifter.hpp"

using TWrapped = airwindohhs::glitchshifter::GlitchShifter<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.glitchshifter~", airwindohhs::glitchshifter::k_long_description.data());
}
