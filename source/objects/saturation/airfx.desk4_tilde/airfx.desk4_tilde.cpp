#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/desk4.hpp"

using namespace c74::min;

class desk4_tilde : public airfx<desk4_tilde, airwindohhs::desk4::Desk4<double>>
{
    atom m_about_text = symbol{ airwindohhs::desk4::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::desk4::k_name.data() };
    MIN_TAGS{ airwindohhs::desk4::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    desk4_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(desk4_tilde);
