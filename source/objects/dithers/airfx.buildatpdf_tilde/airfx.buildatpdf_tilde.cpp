#include "ext.h"

#include "airfx.hpp"
#include "dithers/buildatpdf.hpp"

using TWrapped = airwindohhs::buildatpdf::BuildATPDF<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.buildatpdf~", airwindohhs::buildatpdf::k_long_description.data());
}
