#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/clearcoat.hpp"

using namespace c74::min;

class clearcoat_tilde : public airfx<clearcoat_tilde, airwindohhs::clearcoat::ClearCoat<double>>
{
    atom m_about_text = symbol{ airwindohhs::clearcoat::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::clearcoat::k_name.data() };
    MIN_TAGS{ airwindohhs::clearcoat::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    clearcoat_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(clearcoat_tilde);
