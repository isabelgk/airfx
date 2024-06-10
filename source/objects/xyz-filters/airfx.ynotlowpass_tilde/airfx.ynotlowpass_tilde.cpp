#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/ynotlowpass.hpp"

using namespace c74::min;

class ynotlowpass_tilde : public airfx<ynotlowpass_tilde, airwindohhs::ynotlowpass::YNotLowpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::ynotlowpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ynotlowpass::k_name.data() };
    MIN_TAGS{ airwindohhs::ynotlowpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ynotlowpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ynotlowpass_tilde);
