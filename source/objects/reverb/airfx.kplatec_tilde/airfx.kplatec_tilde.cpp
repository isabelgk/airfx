#include "ext.h"

#include "airfx.hpp"
#include "reverb/kplatec.hpp"

using TWrapped = airwindohhs::kplatec::kPlateC<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kplatec~", airwindohhs::kplatec::k_long_description.data());
}
