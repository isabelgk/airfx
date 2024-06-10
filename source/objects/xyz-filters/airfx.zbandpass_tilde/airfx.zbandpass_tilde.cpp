#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/zbandpass.hpp"

using namespace c74::min;

class zbandpass_tilde : public airfx<zbandpass_tilde, airwindohhs::zbandpass::ZBandpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::zbandpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::zbandpass::k_name.data() };
    MIN_TAGS{ airwindohhs::zbandpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    zbandpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(zbandpass_tilde);
