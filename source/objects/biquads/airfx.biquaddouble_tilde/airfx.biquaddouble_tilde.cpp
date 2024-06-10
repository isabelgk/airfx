#include "c74_min.h"
#include "airfx.hpp"
#include "biquads/biquaddouble.hpp"

using namespace c74::min;

class biquaddouble_tilde : public airfx<biquaddouble_tilde, airwindohhs::biquaddouble::BiquadDouble<double>>
{
    atom m_about_text = symbol{ airwindohhs::biquaddouble::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::biquaddouble::k_name.data() };
    MIN_TAGS{ airwindohhs::biquaddouble::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    biquaddouble_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(biquaddouble_tilde);
