#include "c74_min.h"
#include "airfx.hpp"
#include "biquads/biquadplus.hpp"

using namespace c74::min;

class biquadplus_tilde : public airfx<biquadplus_tilde, airwindohhs::biquadplus::BiquadPlus<double>>
{
    atom m_about_text = symbol{ airwindohhs::biquadplus::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::biquadplus::k_name.data() };
    MIN_TAGS{ airwindohhs::biquadplus::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    biquadplus_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(biquadplus_tilde);
