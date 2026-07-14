#include "ext.h"

#include "airfx.hpp"
#include "distortion/zoutputstage.hpp"

using TWrapped = airwindohhs::zoutputstage::ZOutputStage<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zoutputstage~", airwindohhs::zoutputstage::k_long_description.data());
}
