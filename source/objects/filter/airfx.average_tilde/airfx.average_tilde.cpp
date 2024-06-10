#include "c74_min.h"
#include "airfx.hpp"
#include "filter/average.hpp"

using namespace c74::min;

class average_tilde : public airfx<average_tilde, airwindohhs::average::Average<double>>
{
    atom m_about_text = symbol{ airwindohhs::average::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::average::k_name.data() };
    MIN_TAGS{ airwindohhs::average::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    average_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(average_tilde);
