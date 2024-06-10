#include "c74_min.h"
#include "airfx.hpp"
#include "filter/kalman.hpp"

using namespace c74::min;

class kalman_tilde : public airfx<kalman_tilde, airwindohhs::kalman::Kalman<double>>
{
    atom m_about_text = symbol{ airwindohhs::kalman::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::kalman::k_name.data() };
    MIN_TAGS{ airwindohhs::kalman::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    kalman_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(kalman_tilde);
