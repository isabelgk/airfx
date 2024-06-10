#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/everyslew.hpp"

using namespace c74::min;

class everyslew_tilde : public airfx<everyslew_tilde, airwindohhs::everyslew::EverySlew<double>>
{
    atom m_about_text = symbol{ airwindohhs::everyslew::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::everyslew::k_name.data() };
    MIN_TAGS{ airwindohhs::everyslew::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    everyslew_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(everyslew_tilde);
