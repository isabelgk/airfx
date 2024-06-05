#include "c74_min.h"
#include "airfx.hpp"
#include "effects/aura.hpp"

using namespace c74::min;

class aura_tilde : public airfx<aura_tilde, airwindohhs::aura::Aura<double>>
{
    atom m_about_text = symbol{ airwindohhs::aura::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::aura::k_name.data() };
    MIN_TAGS{ airwindohhs::aura::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    aura_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(aura_tilde);
