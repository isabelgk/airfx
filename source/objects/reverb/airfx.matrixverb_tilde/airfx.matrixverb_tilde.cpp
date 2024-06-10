#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/matrixverb.hpp"

using namespace c74::min;

class matrixverb_tilde : public airfx<matrixverb_tilde, airwindohhs::matrixverb::MatrixVerb<double>>
{
    atom m_about_text = symbol{ airwindohhs::matrixverb::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::matrixverb::k_name.data() };
    MIN_TAGS{ airwindohhs::matrixverb::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    matrixverb_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(matrixverb_tilde);
