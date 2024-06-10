#include "c74_min.h"
#include "airfx.hpp"
#include "utility/bitshiftpan.hpp"

using namespace c74::min;

class bitshiftpan_tilde : public airfx<bitshiftpan_tilde, airwindohhs::bitshiftpan::BitShiftPan<double>>
{
    atom m_about_text = symbol{ airwindohhs::bitshiftpan::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::bitshiftpan::k_name.data() };
    MIN_TAGS{ airwindohhs::bitshiftpan::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    bitshiftpan_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(bitshiftpan_tilde);
