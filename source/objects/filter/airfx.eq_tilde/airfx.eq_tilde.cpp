#include "c74_min.h"
#include "airfx.hpp"
#include "filter/eq.hpp"

using namespace c74::min;

class eq_tilde : public airfx<eq_tilde, airwindohhs::eq::EQ<double>>
{
    atom m_about_text = symbol{ airwindohhs::eq::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::eq::k_name.data() };
    MIN_TAGS{ airwindohhs::eq::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    eq_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(eq_tilde);
