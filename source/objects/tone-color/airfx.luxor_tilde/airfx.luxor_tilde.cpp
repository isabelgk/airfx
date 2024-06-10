#include "c74_min.h"
#include "airfx.hpp"
#include "tone-color/luxor.hpp"

using namespace c74::min;

class luxor_tilde : public airfx<luxor_tilde, airwindohhs::luxor::Luxor<double>>
{
    atom m_about_text = symbol{ airwindohhs::luxor::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::luxor::k_name.data() };
    MIN_TAGS{ airwindohhs::luxor::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    luxor_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(luxor_tilde);
