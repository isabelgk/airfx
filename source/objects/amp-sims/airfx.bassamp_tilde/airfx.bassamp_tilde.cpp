#include "c74_min.h"
#include "airfx.hpp"
#include "amp-sims/bassamp.hpp"

using namespace c74::min;

class bassamp_tilde : public airfx<bassamp_tilde, airwindohhs::bassamp::BassAmp<double>>
{
    atom m_about_text = symbol{ airwindohhs::bassamp::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::bassamp::k_name.data() };
    MIN_TAGS{ airwindohhs::bassamp::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    bassamp_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(bassamp_tilde);
