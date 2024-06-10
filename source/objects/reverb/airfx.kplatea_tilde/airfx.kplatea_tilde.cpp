#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/kplatea.hpp"

using namespace c74::min;

class kplatea_tilde : public airfx<kplatea_tilde, airwindohhs::kplatea::kPlateA<double>>
{
    atom m_about_text = symbol{ airwindohhs::kplatea::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::kplatea::k_name.data() };
    MIN_TAGS{ airwindohhs::kplatea::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    kplatea_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(kplatea_tilde);
