#include "c74_min.h"
#include "airfx.hpp"
#include "effects/cloudcoat.hpp"

using namespace c74::min;

class cloudcoat_tilde : public airfx<cloudcoat_tilde, airwindohhs::cloudcoat::CloudCoat<double>>
{
    atom m_about_text = symbol{ airwindohhs::cloudcoat::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::cloudcoat::k_name.data() };
    MIN_TAGS{ airwindohhs::cloudcoat::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    cloudcoat_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(cloudcoat_tilde);
