#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/purestsquish.hpp"

using namespace c74::min;

class purestsquish_tilde : public airfx<purestsquish_tilde, airwindohhs::purestsquish::PurestSquish<double>>
{
    atom m_about_text = symbol{ airwindohhs::purestsquish::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::purestsquish::k_name.data() };
    MIN_TAGS{ airwindohhs::purestsquish::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    purestsquish_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(purestsquish_tilde);
