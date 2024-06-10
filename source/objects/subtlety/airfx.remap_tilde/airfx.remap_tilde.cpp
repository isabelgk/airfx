#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/remap.hpp"

using namespace c74::min;

class remap_tilde : public airfx<remap_tilde, airwindohhs::remap::Remap<double>>
{
    atom m_about_text = symbol{ airwindohhs::remap::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::remap::k_name.data() };
    MIN_TAGS{ airwindohhs::remap::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    remap_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(remap_tilde);
