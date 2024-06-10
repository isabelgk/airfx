#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/drive.hpp"

using namespace c74::min;

class drive_tilde : public airfx<drive_tilde, airwindohhs::drive::Drive<double>>
{
    atom m_about_text = symbol{ airwindohhs::drive::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::drive::k_name.data() };
    MIN_TAGS{ airwindohhs::drive::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    drive_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(drive_tilde);
