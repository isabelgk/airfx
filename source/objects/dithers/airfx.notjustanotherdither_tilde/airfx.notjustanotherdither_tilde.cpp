#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/notjustanotherdither.hpp"

using namespace c74::min;

class notjustanotherdither_tilde : public airfx<notjustanotherdither_tilde, airwindohhs::notjustanotherdither::NotJustAnotherDither<double>>
{
    atom m_about_text = symbol{ airwindohhs::notjustanotherdither::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::notjustanotherdither::k_name.data() };
    MIN_TAGS{ airwindohhs::notjustanotherdither::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    notjustanotherdither_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(notjustanotherdither_tilde);
