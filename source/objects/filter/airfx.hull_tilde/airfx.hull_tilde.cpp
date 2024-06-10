#include "c74_min.h"
#include "airfx.hpp"
#include "filter/hull.hpp"

using namespace c74::min;

class hull_tilde : public airfx<hull_tilde, airwindohhs::hull::Hull<double>>
{
    atom m_about_text = symbol{ airwindohhs::hull::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::hull::k_name.data() };
    MIN_TAGS{ airwindohhs::hull::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    hull_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(hull_tilde);
