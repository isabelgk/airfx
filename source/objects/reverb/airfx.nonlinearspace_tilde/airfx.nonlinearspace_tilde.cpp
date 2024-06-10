#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/nonlinearspace.hpp"

using namespace c74::min;

class nonlinearspace_tilde : public airfx<nonlinearspace_tilde, airwindohhs::nonlinearspace::NonlinearSpace<double>>
{
    atom m_about_text = symbol{ airwindohhs::nonlinearspace::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::nonlinearspace::k_name.data() };
    MIN_TAGS{ airwindohhs::nonlinearspace::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    nonlinearspace_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(nonlinearspace_tilde);
