#include "c74_min.h"
#include "airfx.hpp"
#include "utility/purestgain.hpp"

using namespace c74::min;

class purestgain_tilde : public airfx<purestgain_tilde, airwindohhs::purestgain::PurestGain<double>>
{
    atom m_about_text = symbol{ airwindohhs::purestgain::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::purestgain::k_name.data() };
    MIN_TAGS{ airwindohhs::purestgain::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    purestgain_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(purestgain_tilde);
