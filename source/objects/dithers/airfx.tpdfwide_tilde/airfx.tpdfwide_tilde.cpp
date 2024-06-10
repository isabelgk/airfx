#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/tpdfwide.hpp"

using namespace c74::min;

class tpdfwide_tilde : public airfx<tpdfwide_tilde, airwindohhs::tpdfwide::TPDFWide<double>>
{
    atom m_about_text = symbol{ airwindohhs::tpdfwide::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tpdfwide::k_name.data() };
    MIN_TAGS{ airwindohhs::tpdfwide::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tpdfwide_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tpdfwide_tilde);
