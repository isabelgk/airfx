#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/buildatpdf.hpp"

using namespace c74::min;

class buildatpdf_tilde : public airfx<buildatpdf_tilde, airwindohhs::buildatpdf::BuildATPDF<double>>
{
    atom m_about_text = symbol{ airwindohhs::buildatpdf::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::buildatpdf::k_name.data() };
    MIN_TAGS{ airwindohhs::buildatpdf::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    buildatpdf_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(buildatpdf_tilde);
