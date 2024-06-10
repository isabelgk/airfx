#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/stereoensemble.hpp"

using namespace c74::min;

class stereoensemble_tilde : public airfx<stereoensemble_tilde, airwindohhs::stereoensemble::StereoEnsemble<double>>
{
    atom m_about_text = symbol{ airwindohhs::stereoensemble::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::stereoensemble::k_name.data() };
    MIN_TAGS{ airwindohhs::stereoensemble::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    stereoensemble_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(stereoensemble_tilde);
