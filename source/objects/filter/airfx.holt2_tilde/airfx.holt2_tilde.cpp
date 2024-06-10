#include "c74_min.h"
#include "airfx.hpp"
#include "filter/holt2.hpp"

using namespace c74::min;

class holt2_tilde : public airfx<holt2_tilde, airwindohhs::holt2::Holt2<double>>
{
    atom m_about_text = symbol{ airwindohhs::holt2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::holt2::k_name.data() };
    MIN_TAGS{ airwindohhs::holt2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    holt2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(holt2_tilde);
