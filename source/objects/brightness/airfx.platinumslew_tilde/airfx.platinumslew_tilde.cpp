#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/platinumslew.hpp"

using namespace c74::min;

class platinumslew_tilde : public airfx<platinumslew_tilde, airwindohhs::platinumslew::PlatinumSlew<double>>
{
    atom m_about_text = symbol{ airwindohhs::platinumslew::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::platinumslew::k_name.data() };
    MIN_TAGS{ airwindohhs::platinumslew::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    platinumslew_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(platinumslew_tilde);
