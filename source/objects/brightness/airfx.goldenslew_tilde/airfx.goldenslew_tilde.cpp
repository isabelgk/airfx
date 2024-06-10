#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/goldenslew.hpp"

using namespace c74::min;

class goldenslew_tilde : public airfx<goldenslew_tilde, airwindohhs::goldenslew::GoldenSlew<double>>
{
    atom m_about_text = symbol{ airwindohhs::goldenslew::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::goldenslew::k_name.data() };
    MIN_TAGS{ airwindohhs::goldenslew::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    goldenslew_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(goldenslew_tilde);
