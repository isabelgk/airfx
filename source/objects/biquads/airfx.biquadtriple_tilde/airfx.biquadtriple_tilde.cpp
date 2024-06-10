#include "c74_min.h"
#include "airfx.hpp"
#include "biquads/biquadtriple.hpp"

using namespace c74::min;

class biquadtriple_tilde : public airfx<biquadtriple_tilde, airwindohhs::biquadtriple::BiquadTriple<double>>
{
    atom m_about_text = symbol{ airwindohhs::biquadtriple::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::biquadtriple::k_name.data() };
    MIN_TAGS{ airwindohhs::biquadtriple::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    biquadtriple_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(biquadtriple_tilde);
