#include "c74_min.h"
#include "airfx.hpp"
#include "effects/dubly.hpp"

using namespace c74::min;

class dubly_tilde : public airfx<dubly_tilde, airwindohhs::dubly::Dubly<double>>
{
    atom m_about_text = symbol{ airwindohhs::dubly::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dubly::k_name.data() };
    MIN_TAGS{ airwindohhs::dubly::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dubly_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dubly_tilde);
