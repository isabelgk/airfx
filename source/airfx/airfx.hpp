#pragma once

#include "ext.h"
#include "ext_obex.h"
#include "ext_obex_util.h"
#include "z_dsp.h"

#include <memory>
#include <string>
#include <string_view>

namespace airfx {

// Airwindows parameter names occasionally contain spaces (e.g. "low cut"),
// which don't route correctly through Max's "attrname value" message syntax
// (the space is a message-list delimiter). Attributes are registered under
// the sanitized name; matching in attr_get/attr_set re-applies the same
// sanitization to the wrapped plugin's raw parameter name for comparison.
inline std::string sanitize_attr_name(std::string_view name)
{
    std::string s(name);
    for (char &c : s) {
        if (c == ' ') {
            c = '_';
        }
    }
    return s;
}

// Every generated per-plugin .cpp instantiates this template on its own wrapped
// airwindohhs plugin class and calls init_class() once from ext_main(). No
// per-object CMakeLists.txt or hand-written boilerplate beyond that one call.

template <typename TWrapped>
struct t_obj
{
    t_pxobject ob;
    std::unique_ptr<TWrapped> wrapped;
    void *dump_out;
};

// object_alloc() zero-fills raw memory rather than invoking constructors, so
// class_ptr/about_symbol -- both set once per class, not per instance -- live
// as function-local statics rather than object fields. Safe because each
// generated .cpp's translation unit instantiates this template for exactly one
// TWrapped, so there is exactly one class per instantiation.
template <typename TWrapped>
t_class *&class_ptr()
{
    static t_class *c = nullptr;
    return c;
}

template <typename TWrapped>
t_symbol *&about_symbol()
{
    static t_symbol *s = nullptr;
    return s;
}

template <typename TWrapped>
void perform64(t_obj<TWrapped> *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts,
               long sampleframes, long flags, void *userparam)
{
    x->wrapped->process(ins, outs, sampleframes);
}

template <typename TWrapped>
void dsp64_method(t_obj<TWrapped> *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize,
                   long flags)
{
    x->wrapped->setSampleRate(samplerate);
    dsp_add64(dsp64, (t_object *)x, (t_perfroutine64)perform64<TWrapped>, 0, NULL);
}

// Shared, generic getter/setter -- one pair per class, not one per parameter.
// Which parameter an attribute corresponds to is resolved at call time by
// matching the attribute's own name (t_attr::name) against the wrapped
// plugin's get_parameter_name(i); called only on attribute get/set, never in
// the audio path.

template <typename TWrapped>
t_max_err attr_get(t_obj<TWrapped> *x, void *attr, long *ac, t_atom **av)
{
    const char *name = ((t_attr *)attr)->name->s_name;
    for (int i = 0; i < TWrapped::kNumParameters; i++) {
        if (sanitize_attr_name(x->wrapped->get_parameter_name(i)) == name) {
            if (!(*ac && *av)) {
                *ac = 1;
                *av = (t_atom *)getbytes(sizeof(t_atom));
            }
            atom_setfloat(*av, x->wrapped->get_parameter_value(i));
            return MAX_ERR_NONE;
        }
    }
    return MAX_ERR_GENERIC;
}

template <typename TWrapped>
t_max_err attr_set(t_obj<TWrapped> *x, void *attr, long ac, t_atom *av)
{
    if (!ac || !av) {
        return MAX_ERR_NONE;
    }
    const char *name = ((t_attr *)attr)->name->s_name;
    for (int i = 0; i < TWrapped::kNumParameters; i++) {
        if (sanitize_attr_name(x->wrapped->get_parameter_name(i)) == name) {
            x->wrapped->set_parameter_value(i, (float)atom_getfloat(av));
            return MAX_ERR_NONE;
        }
    }
    return MAX_ERR_GENERIC;
}

template <typename TWrapped>
void about_method(t_obj<TWrapped> *x)
{
    t_atom a;
    atom_setsym(&a, about_symbol<TWrapped>());
    outlet_anything((t_outlet *)x->dump_out, gensym("about"), 1, &a);
}

template <typename TWrapped>
void free_fn(t_obj<TWrapped> *x)
{
    dsp_free(&x->ob);
    x->wrapped.~unique_ptr<TWrapped>();
}

template <typename TWrapped>
void *new_fn(t_symbol *s, long argc, t_atom *argv)
{
    auto *x = (t_obj<TWrapped> *)object_alloc(class_ptr<TWrapped>());
    if (!x) {
        return nullptr;
    }
    new (&x->wrapped) std::unique_ptr<TWrapped>(std::make_unique<TWrapped>());

    dsp_setup(&x->ob, 2);
    // Outlets are created right-to-left, so the last outlet_new() call becomes
    // the leftmost (index 0): dump outlet first, then the R signal outlet,
    // then the L signal outlet, so the visual/index layout ends up
    // [L signal, R signal, dump] matching outs[0]/outs[1] in perform64.
    x->dump_out = outlet_new(x, NULL);
    outlet_new(x, "signal");
    outlet_new(x, "signal");

    return x;
}

// Called once per class from the generated .cpp's ext_main(). Builds one
// throwaway TWrapped instance purely to enumerate get_parameter_name/title(i)
// at class-setup time (once per class, same cost model as constructing one
// per object); real per-object instances are created in new_fn() above.
template <typename TWrapped>
void init_class(const char *classname, const char *long_description)
{
    t_class *c = class_new(classname, (method)new_fn<TWrapped>, (method)free_fn<TWrapped>, sizeof(t_obj<TWrapped>),
                            NULL, A_GIMME, 0);
    class_dspinit(c);
    class_addmethod(c, (method)dsp64_method<TWrapped>, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)about_method<TWrapped>, "about", 0);

    TWrapped tmp;
    for (int i = 0; i < TWrapped::kNumParameters; i++) {
        t_object *attr = attribute_new(sanitize_attr_name(tmp.get_parameter_name(i)).c_str(), USESYM(float64), 0,
                                        (method)attr_get<TWrapped>, (method)attr_set<TWrapped>);
        attr_addfilter_clip(attr, 0.0, 1.0, 1, 1);
        class_addattr(c, attr);
    }

    class_register(CLASS_BOX, c);

    class_ptr<TWrapped>() = c;
    about_symbol<TWrapped>() = gensym(long_description);
}

} // namespace airfx
