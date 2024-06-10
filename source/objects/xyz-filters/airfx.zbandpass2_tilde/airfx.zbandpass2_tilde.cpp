#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/zbandpass2.hpp"

using namespace c74::min;

class zbandpass2_tilde : public airfx<zbandpass2_tilde, airwindohhs::zbandpass2::ZBandpass2<double>>
{
    atom m_about_text = symbol{ airwindohhs::zbandpass2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::zbandpass2::k_name.data() };
    MIN_TAGS{ airwindohhs::zbandpass2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    zbandpass2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(zbandpass2_tilde);
