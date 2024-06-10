#include "c74_min.h"
#include "airfx.hpp"
#include "amp-sims/crickbass.hpp"

using namespace c74::min;

class crickbass_tilde : public airfx<crickbass_tilde, airwindohhs::crickbass::CrickBass<double>>
{
    atom m_about_text = symbol{ airwindohhs::crickbass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::crickbass::k_name.data() };
    MIN_TAGS{ airwindohhs::crickbass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    crickbass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(crickbass_tilde);
