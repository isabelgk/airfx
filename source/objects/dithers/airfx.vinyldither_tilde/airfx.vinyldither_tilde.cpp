#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/vinyldither.hpp"

using namespace c74::min;

class vinyldither_tilde : public airfx<vinyldither_tilde, airwindohhs::vinyldither::VinylDither<double>>
{
    atom m_about_text = symbol{ airwindohhs::vinyldither::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::vinyldither::k_name.data() };
    MIN_TAGS{ airwindohhs::vinyldither::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    vinyldither_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(vinyldither_tilde);
