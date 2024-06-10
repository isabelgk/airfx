#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/xbandpass.hpp"

using namespace c74::min;

class xbandpass_tilde : public airfx<xbandpass_tilde, airwindohhs::xbandpass::XBandpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::xbandpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::xbandpass::k_name.data() };
    MIN_TAGS{ airwindohhs::xbandpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    xbandpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(xbandpass_tilde);
