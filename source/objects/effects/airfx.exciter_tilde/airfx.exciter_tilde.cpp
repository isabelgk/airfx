#include "c74_min.h"
#include "airfx.hpp"
#include "effects/exciter.hpp"

using namespace c74::min;

class exciter_tilde : public airfx<exciter_tilde, airwindohhs::exciter::Exciter<double>>
{
    atom m_about_text = symbol{ airwindohhs::exciter::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::exciter::k_name.data() };
    MIN_TAGS{ airwindohhs::exciter::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    exciter_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(exciter_tilde);
