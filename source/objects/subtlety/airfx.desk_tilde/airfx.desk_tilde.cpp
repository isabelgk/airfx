#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/desk.hpp"

using namespace c74::min;

class desk_tilde : public airfx<desk_tilde, airwindohhs::desk::Desk<double>>
{
    atom m_about_text = symbol{ airwindohhs::desk::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::desk::k_name.data() };
    MIN_TAGS{ airwindohhs::desk::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    desk_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(desk_tilde);
