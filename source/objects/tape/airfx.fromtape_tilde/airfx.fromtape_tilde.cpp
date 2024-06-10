#include "c74_min.h"
#include "airfx.hpp"
#include "tape/fromtape.hpp"

using namespace c74::min;

class fromtape_tilde : public airfx<fromtape_tilde, airwindohhs::fromtape::FromTape<double>>
{
    atom m_about_text = symbol{ airwindohhs::fromtape::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::fromtape::k_name.data() };
    MIN_TAGS{ airwindohhs::fromtape::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    fromtape_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(fromtape_tilde);
