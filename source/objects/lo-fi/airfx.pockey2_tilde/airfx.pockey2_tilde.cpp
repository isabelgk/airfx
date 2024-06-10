#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/pockey2.hpp"

using namespace c74::min;

class pockey2_tilde : public airfx<pockey2_tilde, airwindohhs::pockey2::Pockey2<double>>
{
    atom m_about_text = symbol{ airwindohhs::pockey2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pockey2::k_name.data() };
    MIN_TAGS{ airwindohhs::pockey2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pockey2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pockey2_tilde);
