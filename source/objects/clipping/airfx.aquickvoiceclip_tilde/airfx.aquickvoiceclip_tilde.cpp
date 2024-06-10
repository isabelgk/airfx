#include "c74_min.h"
#include "airfx.hpp"
#include "clipping/aquickvoiceclip.hpp"

using namespace c74::min;

class aquickvoiceclip_tilde : public airfx<aquickvoiceclip_tilde, airwindohhs::aquickvoiceclip::AQuickVoiceClip<double>>
{
    atom m_about_text = symbol{ airwindohhs::aquickvoiceclip::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::aquickvoiceclip::k_name.data() };
    MIN_TAGS{ airwindohhs::aquickvoiceclip::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    aquickvoiceclip_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(aquickvoiceclip_tilde);
