#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/sweeten.hpp"

using namespace c74::min;

class sweeten_tilde : public airfx<sweeten_tilde, airwindohhs::sweeten::Sweeten<double>>
{
    atom m_about_text = symbol{ airwindohhs::sweeten::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::sweeten::k_name.data() };
    MIN_TAGS{ airwindohhs::sweeten::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    sweeten_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(sweeten_tilde);
