#include "c74_min.h"
#include "airfx.hpp"
#include "amp-sims/bigamp.hpp"

using namespace c74::min;

class bigamp_tilde : public airfx<bigamp_tilde, airwindohhs::bigamp::BigAmp<double>>
{
    atom m_about_text = symbol{ airwindohhs::bigamp::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::bigamp::k_name.data() };
    MIN_TAGS{ airwindohhs::bigamp::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    bigamp_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(bigamp_tilde);
