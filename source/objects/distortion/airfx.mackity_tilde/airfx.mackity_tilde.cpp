#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/mackity.hpp"

using namespace c74::min;

class mackity_tilde : public airfx<mackity_tilde, airwindohhs::mackity::Mackity<double>>
{
    atom m_about_text = symbol{ airwindohhs::mackity::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::mackity::k_name.data() };
    MIN_TAGS{ airwindohhs::mackity::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    mackity_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(mackity_tilde);
