#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/kplateb.hpp"

using namespace c74::min;

class kplateb_tilde : public airfx<kplateb_tilde, airwindohhs::kplateb::kPlateB<double>>
{
    atom m_about_text = symbol{ airwindohhs::kplateb::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::kplateb::k_name.data() };
    MIN_TAGS{ airwindohhs::kplateb::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    kplateb_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(kplateb_tilde);
