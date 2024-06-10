#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/righteous4.hpp"

using namespace c74::min;

class righteous4_tilde : public airfx<righteous4_tilde, airwindohhs::righteous4::Righteous4<double>>
{
    atom m_about_text = symbol{ airwindohhs::righteous4::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::righteous4::k_name.data() };
    MIN_TAGS{ airwindohhs::righteous4::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    righteous4_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(righteous4_tilde);
