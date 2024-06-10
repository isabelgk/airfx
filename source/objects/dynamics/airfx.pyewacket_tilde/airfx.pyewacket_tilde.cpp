#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/pyewacket.hpp"

using namespace c74::min;

class pyewacket_tilde : public airfx<pyewacket_tilde, airwindohhs::pyewacket::Pyewacket<double>>
{
    atom m_about_text = symbol{ airwindohhs::pyewacket::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pyewacket::k_name.data() };
    MIN_TAGS{ airwindohhs::pyewacket::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pyewacket_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pyewacket_tilde);
