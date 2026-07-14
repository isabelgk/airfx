#include "ext.h"

#include "airfx.hpp"
#include "dithers/tpdfdither.hpp"

using TWrapped = airwindohhs::tpdfdither::TPDFDither<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tpdfdither~", airwindohhs::tpdfdither::k_long_description.data());
}
