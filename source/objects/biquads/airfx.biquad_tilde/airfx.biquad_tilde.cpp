#include "c74_min.h"
#include "airfx.hpp"
#include "biquads/biquad.hpp"

using namespace c74::min;

class biquad_tilde : public airfx<biquad_tilde, airwindohhs::biquad::Biquad<double>>
{
    atom m_about_text = symbol{ airwindohhs::biquad::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::biquad::k_name.data() };
    MIN_TAGS{ airwindohhs::biquad::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    biquad_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(biquad_tilde);
