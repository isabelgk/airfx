#include "c74_min.h"
#include "airfx.hpp"
#include "amp-sims/leadamp.hpp"

using namespace c74::min;

class leadamp_tilde : public airfx<leadamp_tilde, airwindohhs::leadamp::LeadAmp<double>>
{
    atom m_about_text = symbol{ airwindohhs::leadamp::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::leadamp::k_name.data() };
    MIN_TAGS{ airwindohhs::leadamp::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    leadamp_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(leadamp_tilde);
