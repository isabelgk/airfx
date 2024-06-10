#include "c74_min.h"
#include "airfx.hpp"
#include "filter/avermatrix.hpp"

using namespace c74::min;

class avermatrix_tilde : public airfx<avermatrix_tilde, airwindohhs::avermatrix::AverMatrix<double>>
{
    atom m_about_text = symbol{ airwindohhs::avermatrix::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::avermatrix::k_name.data() };
    MIN_TAGS{ airwindohhs::avermatrix::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    avermatrix_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(avermatrix_tilde);
