#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/tpdfdither.hpp"

using namespace c74::min;

class tpdfdither_tilde : public airfx<tpdfdither_tilde, airwindohhs::tpdfdither::TPDFDither<double>>
{
    atom m_about_text = symbol{ airwindohhs::tpdfdither::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tpdfdither::k_name.data() };
    MIN_TAGS{ airwindohhs::tpdfdither::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tpdfdither_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tpdfdither_tilde);
