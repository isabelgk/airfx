#include "c74_min.h"
#include "airfx.hpp"
#include "biquads/biquadnonlin.hpp"

using namespace c74::min;

class biquadnonlin_tilde : public airfx<biquadnonlin_tilde, airwindohhs::biquadnonlin::BiquadNonLin<double>>
{
    atom m_about_text = symbol{ airwindohhs::biquadnonlin::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::biquadnonlin::k_name.data() };
    MIN_TAGS{ airwindohhs::biquadnonlin::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    biquadnonlin_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(biquadnonlin_tilde);
