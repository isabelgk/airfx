#include "c74_min.h"
#include "airfx.hpp"
#include "filter/reseq2.hpp"

using namespace c74::min;

class reseq2_tilde : public airfx<reseq2_tilde, airwindohhs::reseq2::ResEQ2<double>>
{
    atom m_about_text = symbol{ airwindohhs::reseq2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::reseq2::k_name.data() };
    MIN_TAGS{ airwindohhs::reseq2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    reseq2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(reseq2_tilde);
