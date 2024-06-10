#include "c74_min.h"
#include "airfx.hpp"
#include "amp-sims/lilamp.hpp"

using namespace c74::min;

class lilamp_tilde : public airfx<lilamp_tilde, airwindohhs::lilamp::LilAmp<double>>
{
    atom m_about_text = symbol{ airwindohhs::lilamp::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::lilamp::k_name.data() };
    MIN_TAGS{ airwindohhs::lilamp::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    lilamp_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(lilamp_tilde);
