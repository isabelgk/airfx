#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/kcathedral.hpp"

using namespace c74::min;

class kcathedral_tilde : public airfx<kcathedral_tilde, airwindohhs::kcathedral::kCathedral<double>>
{
    atom m_about_text = symbol{ airwindohhs::kcathedral::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::kcathedral::k_name.data() };
    MIN_TAGS{ airwindohhs::kcathedral::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    kcathedral_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(kcathedral_tilde);
