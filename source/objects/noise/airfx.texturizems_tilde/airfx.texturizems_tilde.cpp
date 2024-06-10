#include "c74_min.h"
#include "airfx.hpp"
#include "noise/texturizems.hpp"

using namespace c74::min;

class texturizems_tilde : public airfx<texturizems_tilde, airwindohhs::texturizems::TexturizeMS<double>>
{
    atom m_about_text = symbol{ airwindohhs::texturizems::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::texturizems::k_name.data() };
    MIN_TAGS{ airwindohhs::texturizems::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    texturizems_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(texturizems_tilde);
