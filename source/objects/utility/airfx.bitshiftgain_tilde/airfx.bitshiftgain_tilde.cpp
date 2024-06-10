#include "c74_min.h"
#include "airfx.hpp"
#include "utility/bitshiftgain.hpp"

using namespace c74::min;

class bitshiftgain_tilde : public airfx<bitshiftgain_tilde, airwindohhs::bitshiftgain::BitShiftGain<double>>
{
    atom m_about_text = symbol{ airwindohhs::bitshiftgain::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::bitshiftgain::k_name.data() };
    MIN_TAGS{ airwindohhs::bitshiftgain::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    bitshiftgain_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(bitshiftgain_tilde);
