#include "c74_min.h"
#include "airfx.hpp"
#include "effects/aura.hpp"

using namespace c74::min;

class aura_tilde : public airfx<aura_tilde, airwindohhs::aura::Aura<double>>
{
  public:
    MIN_DESCRIPTION{ airwindohhs::aura::k_name.data() };
    MIN_TAGS{ airwindohhs::aura::k_tags.data() };

    aura_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(aura_tilde);
