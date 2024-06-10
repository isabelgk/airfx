#include "c74_min.h"
#include "airfx.hpp"
#include "utility/monoam.hpp"

using namespace c74::min;

class monoam_tilde : public airfx<monoam_tilde, airwindohhs::monoam::MoNoam<double>>
{
    atom m_about_text = symbol{ airwindohhs::monoam::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::monoam::k_name.data() };
    MIN_TAGS{ airwindohhs::monoam::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    monoam_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(monoam_tilde);
