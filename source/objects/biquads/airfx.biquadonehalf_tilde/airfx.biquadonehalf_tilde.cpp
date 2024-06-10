#include "c74_min.h"
#include "airfx.hpp"
#include "biquads/biquadonehalf.hpp"

using namespace c74::min;

class biquadonehalf_tilde : public airfx<biquadonehalf_tilde, airwindohhs::biquadonehalf::BiquadOneHalf<double>>
{
    atom m_about_text = symbol{ airwindohhs::biquadonehalf::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::biquadonehalf::k_name.data() };
    MIN_TAGS{ airwindohhs::biquadonehalf::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    biquadonehalf_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(biquadonehalf_tilde);
