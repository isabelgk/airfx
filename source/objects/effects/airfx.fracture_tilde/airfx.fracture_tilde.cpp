#include "c74_min.h"
#include "airfx.hpp"
#include "effects/fracture.hpp"

using namespace c74::min;

class fracture_tilde : public airfx<fracture_tilde, airwindohhs::fracture::Fracture<double>>
{
    atom m_about_text = symbol{ airwindohhs::fracture::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::fracture::k_name.data() };
    MIN_TAGS{ airwindohhs::fracture::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    fracture_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(fracture_tilde);
