#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/ensemble.hpp"

using namespace c74::min;

class ensemble_tilde : public airfx<ensemble_tilde, airwindohhs::ensemble::Ensemble<double>>
{
    atom m_about_text = symbol{ airwindohhs::ensemble::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ensemble::k_name.data() };
    MIN_TAGS{ airwindohhs::ensemble::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ensemble_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ensemble_tilde);
