#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/flutter.hpp"

using namespace c74::min;

class flutter_tilde : public airfx<flutter_tilde, airwindohhs::flutter::Flutter<double>>
{
    atom m_about_text = symbol{ airwindohhs::flutter::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::flutter::k_name.data() };
    MIN_TAGS{ airwindohhs::flutter::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    flutter_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(flutter_tilde);
