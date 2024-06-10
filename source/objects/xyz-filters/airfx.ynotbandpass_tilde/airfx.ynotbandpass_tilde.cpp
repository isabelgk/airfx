#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/ynotbandpass.hpp"

using namespace c74::min;

class ynotbandpass_tilde : public airfx<ynotbandpass_tilde, airwindohhs::ynotbandpass::YNotBandpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::ynotbandpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ynotbandpass::k_name.data() };
    MIN_TAGS{ airwindohhs::ynotbandpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ynotbandpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ynotbandpass_tilde);
