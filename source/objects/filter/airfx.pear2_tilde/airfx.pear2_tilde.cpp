#include "c74_min.h"
#include "airfx.hpp"
#include "filter/pear2.hpp"

using namespace c74::min;

class pear2_tilde : public airfx<pear2_tilde, airwindohhs::pear2::Pear2<double>>
{
    atom m_about_text = symbol{ airwindohhs::pear2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pear2::k_name.data() };
    MIN_TAGS{ airwindohhs::pear2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pear2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pear2_tilde);
