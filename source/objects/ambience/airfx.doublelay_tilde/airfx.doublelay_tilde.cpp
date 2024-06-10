#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/doublelay.hpp"

using namespace c74::min;

class doublelay_tilde : public airfx<doublelay_tilde, airwindohhs::doublelay::Doublelay<double>>
{
    atom m_about_text = symbol{ airwindohhs::doublelay::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::doublelay::k_name.data() };
    MIN_TAGS{ airwindohhs::doublelay::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    doublelay_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(doublelay_tilde);
