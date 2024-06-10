#include "c74_min.h"
#include "airfx.hpp"
#include "effects/guitarconditioner.hpp"

using namespace c74::min;

class guitarconditioner_tilde : public airfx<guitarconditioner_tilde, airwindohhs::guitarconditioner::GuitarConditioner<double>>
{
    atom m_about_text = symbol{ airwindohhs::guitarconditioner::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::guitarconditioner::k_name.data() };
    MIN_TAGS{ airwindohhs::guitarconditioner::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    guitarconditioner_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(guitarconditioner_tilde);
