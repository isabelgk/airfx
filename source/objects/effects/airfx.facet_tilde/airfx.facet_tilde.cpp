#include "c74_min.h"
#include "airfx.hpp"
#include "effects/facet.hpp"

using namespace c74::min;

class facet_tilde : public airfx<facet_tilde, airwindohhs::facet::Facet<double>>
{
    atom m_about_text = symbol{ airwindohhs::facet::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::facet::k_name.data() };
    MIN_TAGS{ airwindohhs::facet::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    facet_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(facet_tilde);
