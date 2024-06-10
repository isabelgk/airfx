#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/kplatec.hpp"

using namespace c74::min;

class kplatec_tilde : public airfx<kplatec_tilde, airwindohhs::kplatec::kPlateC<double>>
{
    atom m_about_text = symbol{ airwindohhs::kplatec::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::kplatec::k_name.data() };
    MIN_TAGS{ airwindohhs::kplatec::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    kplatec_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(kplatec_tilde);
