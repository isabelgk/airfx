#include "ext.h"

#include "airfx.hpp"
#include "reverb/matrixverb.hpp"

using TWrapped = airwindohhs::matrixverb::MatrixVerb<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.matrixverb~", airwindohhs::matrixverb::k_long_description.data());
}
