#include "c74_min.h"
#include "airfx.hpp"
#include "amp-sims/midamp.hpp"

using namespace c74::min;

class midamp_tilde : public airfx<midamp_tilde, airwindohhs::midamp::MidAmp<double>>
{
    atom m_about_text = symbol{ airwindohhs::midamp::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::midamp::k_name.data() };
    MIN_TAGS{ airwindohhs::midamp::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    midamp_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(midamp_tilde);
