#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/hombre.hpp"

using namespace c74::min;

class hombre_tilde : public airfx<hombre_tilde, airwindohhs::hombre::Hombre<double>>
{
    atom m_about_text = symbol{ airwindohhs::hombre::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::hombre::k_name.data() };
    MIN_TAGS{ airwindohhs::hombre::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    hombre_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(hombre_tilde);
