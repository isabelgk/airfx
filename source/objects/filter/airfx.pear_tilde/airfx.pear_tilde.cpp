#include "c74_min.h"
#include "airfx.hpp"
#include "filter/pear.hpp"

using namespace c74::min;

class pear_tilde : public airfx<pear_tilde, airwindohhs::pear::Pear<double>>
{
    atom m_about_text = symbol{ airwindohhs::pear::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pear::k_name.data() };
    MIN_TAGS{ airwindohhs::pear::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pear_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pear_tilde);
