#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>
#include <functional>
#include <iostream>
#include <exception>
#include <algorithm>
#include <sstream>

#include "dwislpy-ast.hh"
#include "dwislpy-util.hh"
#include "dwislpy-check.hh" // for type_name debug

//
// dwislpy-ast.cc
//
// Below are the implementations of methods for AST nodes. They are organized
// into groups. The first group represents the DWISLPY interpreter by giving
// the code for 
//
//    Prgm::run, Blck::exec, Stmt::exec, Expn::eval
//
// The second group AST::output and AST::dump performs pretty printing
// of SLPY code and also the output of the AST, resp.
//

//
// to_string
//
// Helper function that converts a DwiSlpy value into a string.
// This is meant to be used by `print` and also `str`.
// 
std::string to_string(Valu v) {
    if (std::holds_alternative<int>(v)) {
        return std::to_string(std::get<int>(v));
    } else if (std::holds_alternative<std::string>(v)) {
        return std::get<std::string>(v);
    } else if (std::holds_alternative<bool>(v)) {
        if (std::get<bool>(v)) {
            return "True";
        } else {
            return "False";
        }
    } else if (std::holds_alternative<none>(v)) {
        return "None";
    } else {
        return "<unknown>";
    }
}

//
// to_repr
//
// Helper function that converts a DwiSlpy value into a string.
// This is meant to mimic Python's `repr` function in that it gives
// the source code string for the value. Used by routines that dump
// a literal value.
//
std::string to_repr(Valu v) {
    if (std::holds_alternative<std::string>(v)) {
        //
        // Strings have to be converted to show their quotes and also
        // to have the unprintable chatacters given as \escape sequences.
        //
        return "\"" + re_escape(std::get<std::string>(v)) + "\"";
    } else {
        //
        // The other types aren't special. (This will have to change when
        // we have value types that aren't "ground" types e.g. list types.)
        //
        return to_string(v);
    }
}



// * * * * *
// The DWISLPY interpreter
//

//
// Prgm::run, Blck::exec, Stmt::exec
//
//  - execute DWISLPY statements, changing the runtime context mapping
//    variables to their current values.
//

void Prgm::run(void) const {
    Ctxt main_ctxt { };
    if (main) {
        main->exec(defs,main_ctxt);
    }
}

std::optional<Valu> Defn::call(const Defs& defs, const Expn_vec xpns, 
    const Ctxt& ctxt) const {
    // create frame ctxt, unordered map.
    Ctxt frme = ctxt; // copy
    int lngth = xpns.size();
    for (int i=0; i<lngth; i++) {
        frme[symt.get_frml(i)->name] = xpns[i]->eval(defs,ctxt); 
            //frame of symt[i] = xpn[i]
            // but how does the symt know it's the right name?
            // won't the front formals keep getting overwritten while the
            // end formals are never touched? because xpns only goes so far.
            //shouldn't it be the stuff at the end minus some offset?
    }
    // run the nest with the updated ctxt
    return nest->exec(defs,frme);
}

std::optional<Valu> Nest::exec(const Defs& defs, Ctxt& ctxt) const {
    std::optional<Valu> rv = blck->exec(defs,ctxt);
    if (rv.has_value()) {
        return rv;
    }
    return std::nullopt;
}
 
std::optional<Valu> Blck::exec(const Defs& defs, Ctxt& ctxt) const {
    for (Stmt_ptr s : stmts) {
        std::optional<Valu> rv = s->exec(defs,ctxt);
        if (rv.has_value()) {
            return rv;
        } 
    }
    return std::nullopt;
}

std::optional<Valu> Ifif::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    bool cnd = std::get<bool>(cond->eval(defs,ctxt));
    if (cnd) {
        std::optional<Valu> rv = frst->exec(defs,ctxt); // nest
        if (rv.has_value()) {
            return rv;
        } 
    } else if (scnd != nullptr) {
        std::optional<Valu> rv = frst->exec(defs,ctxt); // nest
        if (rv.has_value()) {
            return rv;
        } 
    }
    // untested
    return std::nullopt;
}

std::optional<Valu> Untl::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    do {
        std::optional<Valu> rv = nest->exec(defs,ctxt);
        if (rv.has_value()) {
            return rv;
        }
    } while (!std::get<bool>(cond->eval(defs,ctxt)));
    return std::nullopt;
}

std::optional<Valu> Whil::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    while (std::get<bool>(cond->eval(defs,ctxt))) {
        std::optional<Valu> rv = nest->exec(defs,ctxt);
        if (rv.has_value()) {
            return rv;
        }
    }
    return std::nullopt;
}

std::optional<Valu> Asgn::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    ctxt[name] = expn->eval(defs,ctxt);
    return std::nullopt;
}

std::optional<Valu> Ntro::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    ctxt[name] = expn->eval(defs,ctxt);
    return std::nullopt;
}

std::optional<Valu> PlEq::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    Valu base = ctxt[name];
    Valu increment = expn->eval(defs,ctxt);
    if (std::holds_alternative<int>(base) && std::holds_alternative<int>(increment)) {
        ctxt[name] = std::get<int>(base) + std::get<int>(increment);
    } else if (std::holds_alternative<std::string>(base) && 
                std::holds_alternative<std::string>(increment)) {
        ctxt[name] = std::get<std::string>(base) + std::get<std::string>(increment);
    } else {
        std::string msg = "Bad input to PlEq";
        throw DwislpyError { where(), msg };
    }
    return std::nullopt;
}

std::optional<Valu> MnEq::exec(const Defs& defs,
                               Ctxt& ctxt) const {
    ctxt[name] = std::get<int>(ctxt[name]) - 
	    std::get<int>(expn->eval(defs,ctxt));
    return std::nullopt;
}

std::optional<Valu> Proc::exec([[maybe_unused]] const Defs& defs,
                               [[maybe_unused]] Ctxt& ctxt) const {
    // must not return a value!
    // evaluate the parameter expressions xpns
    // build new frame of local variables as a Ctxt (unordered map)
    // then execute code with Defn::call!
        // maybe throw an error if there's a return value.
    // duplicate the code or give the xpns to Defn::call?
    // the xpns should go to Defn::call because they need to be bound
    // to the local names. Do it by index in Defn::call.

    // so: 1) lookup name to get Defn_ptr
    // 2) call Defn::call
    // 3) check return value. error if there is one.
    Defn_ptr d = Defn_ptr{nullptr};
    for (Defn_ptr maybe: defs) {
        if (maybe->name == name) {
            d = maybe;
        }
    }
    if (d) {
        std::optional<Valu> rv = d->call(defs, xpns, ctxt); // gives back rv
        if (rv.has_value()) {
            std::string msg = "Hey, procedures can't have values! " + name;
            throw DwislpyError { where(), msg };
        } else {
            return std::nullopt;
        }
    } else {
        std::string msg = "Run-time error: procedure'" + name +"'";
        msg += "not defined.";
        throw DwislpyError { where(), msg };
    }
}
 
std::optional<Valu> Rtrn::exec([[maybe_unused]] const Defs& defs,
                               [[maybe_unused]] Ctxt& ctxt) const {
    if (expn) {
        return expn->eval(defs, ctxt);
    }
    // does nothing!
    return std::nullopt;
}
 
std::optional<Valu> Pass::exec([[maybe_unused]] const Defs& defs,
                               [[maybe_unused]] Ctxt& ctxt) const {
    // does nothing!
    return std::nullopt;
}
  
std::optional<Valu> Prnt::exec(const Defs& defs, Ctxt& ctxt) const {
    for (Expn_ptr expn: xpns) {
        std::cout << to_string(expn->eval(defs,ctxt)) << std::endl;
    }
    if (xpns.size() == 0) { std::cout << std::endl; }
    return std::nullopt;
}

//
// Expn::eval
//
//  - evaluate DWISLPY expressions within a runtime context to determine their
//    (integer) value.
//

Valu Func::eval(const Defs& defs, const Ctxt& ctxt) const {
   //unimplemented -- lookup name? Defn call?
    Defn_ptr d = Defn_ptr{nullptr};
    for (Defn_ptr maybe: defs) {
        if (maybe->name == name) {
            d = maybe;
        }
    }
    if (d) {
        std::optional<Valu> rv = d->call(defs, xpns, ctxt); // gives back rv
        if (rv.has_value()) {
            return rv.value();
        } else {
            std::string msg = "Hey, functions need values! " + name;
            throw DwislpyError { where(), msg };
        }
    } else {
        std::string msg = "Run-time error: function'" + name +"'";
        msg += "not defined.";
        throw DwislpyError { where(), msg };
    }
}

Valu Disj::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    if (std::holds_alternative<bool>(lv)) {
        bool ln = std::get<bool>(lv);
        if (ln) {
            return Valu{true};
        } else {
            Valu rv = rght->eval(defs,ctxt);
            if (std::holds_alternative<bool>(rv)) {
                bool rn = std::get<bool>(rv);
                return Valu {ln || rn};
            }
        }
    }        
    std::string msg = "Run-time error: wrong operand type for or.";
    throw DwislpyError { where(), msg };
}

Valu Conj::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    if (std::holds_alternative<bool>(lv)) {
        bool ln = std::get<bool>(lv);
        if (!ln) { // short circuit
            return Valu {false};
        } else {
            Valu rv = rght->eval(defs,ctxt);
            if (std::holds_alternative<bool>(rv)) {
                bool rn = std::get<bool>(rv);
                return Valu {ln && rn};
            }        
        }
    }
    std::string msg = "Run-time error: wrong operand type for and.";
    throw DwislpyError { where(), msg };
}

Valu LNot::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu ex = expn->eval(defs,ctxt);
    if (std::holds_alternative<bool>(ex)) {
        bool en = std::get<bool>(ex);
        return Valu {!en};
    } else {
        std::string msg = "Run-time error: wrong operand type for not.";
        throw DwislpyError { where(), msg };
    }        
}

Valu Less::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln < rn};
    } else {
        std::string msg = "Run-time error: wrong operand type for plus.";
        throw DwislpyError { where(), msg };
    }        
}

Valu LsEq::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln <= rn};
    } else {
        std::string msg = "Run-time error: wrong operand type for lessEq.";
        throw DwislpyError { where(), msg };
    }        
}

Valu Equl::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln == rn};
    } else if (std::holds_alternative<bool>(lv)
                && std::holds_alternative<bool>(rv)) {
        bool ln = std::get<bool>(lv);
        bool rn = std::get<bool>(rv);
        return Valu {ln == rn};
    } else if (std::holds_alternative<std::string>(lv)
                && std::holds_alternative<std::string>(rv)) {
        std::string ln = std::get<std::string>(lv);
        std::string rn = std::get<std::string>(rv);
        return Valu {ln == rn};
    } else {
        std::string msg = "Run-time error: wrong operand type for equals.";
        throw DwislpyError { where(), msg };
    }        
}

Valu Plus::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln + rn};
    } else if (std::holds_alternative<std::string>(lv)
               && std::holds_alternative<std::string>(rv)) {
        std::string ls = std::get<std::string>(lv);
        std::string rs = std::get<std::string>(rv);
        return Valu {ls + rs};
    } else {
        std::string msg = "Run-time error: wrong operand type for plus.";
        throw DwislpyError { where(), msg };
    }        
}

Valu Mnus::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln - rn};
    } else {
        std::string msg = "Run-time error: wrong operand type for minus.";
        throw DwislpyError { where(), msg };
    }        
}

Valu Tmes::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        return Valu {ln * rn};
    } else {
        // Exercise: make this work for (int,str) and (str,int).
        std::string msg = "Run-time error: wrong operand type for times.";
        throw DwislpyError { where(), msg };
    }        
}

Valu IDiv::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        if (rn == 0) {
            throw DwislpyError { where(), "Run-time error: division by 0."};
        } else {
            return Valu {ln / rn};
        } 
    } else {
        std::string msg = "Run-time error: wrong operand type for quotient.";
        throw DwislpyError { where(), msg };
    }        
}

Valu IMod::eval(const Defs& defs, const Ctxt& ctxt) const {
    Valu lv = left->eval(defs,ctxt);
    Valu rv = rght->eval(defs,ctxt);
    if (std::holds_alternative<int>(lv)
        && std::holds_alternative<int>(rv)) {
        int ln = std::get<int>(lv);
        int rn = std::get<int>(rv);
        if (rn == 0) {
            throw DwislpyError { where(), "Run-time error: division by 0."};
        } else {
            return Valu {ln % rn};
        } 
    } else {
        std::string msg = "Run-time error: wrong operand type for remainder.";
        throw DwislpyError { where(), msg };
    }        
}
Valu Ltrl::eval([[maybe_unused]] const Defs& defs,
                [[maybe_unused]] const Ctxt& ctxt) const {
    return valu;
}

Valu Lkup::eval([[maybe_unused]] const Defs& defs, const Ctxt& ctxt) const {
    if (ctxt.count(name) > 0) {
        return ctxt.at(name);
    } else {
        std::string msg = "Run-time error: variable '" + name +"'";
        msg += "not defined.";
        throw DwislpyError { where(), msg };
    }
}

Valu Inpt::eval([[maybe_unused]] const Defs& defs, const Ctxt& ctxt) const {
    Valu v = expn->eval(defs,ctxt);
    if (std::holds_alternative<std::string>(v)) {
        //
        std::string prompt = std::get<std::string>(v);
        std::cout << prompt;
        //
        std::string vl;
        std::cin >> vl;
        //
        return Valu {vl};
    } else {
        std::string msg = "Run-time error: prompt is not a string.";
        throw DwislpyError { where(), msg };
    }
}

Valu IntC::eval([[maybe_unused]] const Defs& defs, const Ctxt& ctxt) const {
    //
    // The integer conversion operation does nothing in this
    // version of DWISLPY.
    //
    Valu v = expn->eval(defs,ctxt);
    if (std::holds_alternative<int>(v)) {
        return Valu {v};
    } else if (std::holds_alternative<std::string>(v)) {
        std::string s = std::get<std::string>(v);
        try {
            int i = std::stoi(s);
            return Valu {i};
        } catch (std::invalid_argument e) {
            std::string msg = "Run-time error: \""+s+"\"";
            msg += "cannot be converted to an int.";
            throw DwislpyError { where(), msg };
        }
    } else if (std::holds_alternative<bool>(v)) {
        bool b = std::get<bool>(v);
        return Valu {b ? 1 : 0};
    } else {
        std::string msg = "Run-time error: cannot convert to an int.";
        throw DwislpyError { where(), msg };
    }
}

Valu StrC::eval([[maybe_unused]] const Defs& defs, const Ctxt& ctxt) const {
    //
    // The integer conversion operation does nothing in this
    // version of DWISLPY.
    //
    Valu v = expn->eval(defs,ctxt);
    return Valu { to_string(v) };
}

// * * * * *
//
// AST::output
//
// - Pretty printer for DWISLPY code represented in an AST.
//
// The code below is an implementation of a pretty printer. For each case
// of an AST node (each subclass) the `output` method provides the means for
// printing the code of the DWISLPY construct it represents.
//
//

void Prgm::output(std::ostream& os) const {
    for (Defn_ptr defn : defs) {
        defn->output(os);
    }
    main->output(os);
}

void Defn::output(std::ostream& os) const {
    // similar to Jim's starter
    os << "def" << std::endl; 
    os << name << "(";
    int count = 0;
    int lngth = symt.get_frmls_size();
    for (unsigned int i=0; i < arity(); i++) {
        SymInfo_ptr frml = formal(i);
        os << frml->name << ":" << type_name(frml->type);
        if (count != lngth-1) { os << ", "; }
    }
    os << "):" << std::endl;
    nest->output(os,"\t");
}

void Nest::output(std::ostream& os, std::string indent) const {
    blck->output(os,indent);
}

void Nest::output(std::ostream& os) const {
    blck->output(os);
}

void Blck::output(std::ostream& os, std::string indent) const {
    for (Stmt_ptr s : stmts) {
        s->output(os,indent);
    }
}

void Blck::output(std::ostream& os) const {
    for (Stmt_ptr s : stmts) {
        s->output(os);
    }
}

void Stmt::output(std::ostream& os) const {
    output(os,"");
}

void Untl::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << "repeat";
    cond->output(os);
    os << ":";
    os << std::endl;
    nest->output(os);
    os << std::endl;
}

void Whil::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << "while ";
    cond->output(os);
    os << ":";
    os << std::endl;
    nest->output(os);
    os << std::endl;
}

void Ifif::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << "if ";
    cond->output(os);
    os << ":";
    os << std::endl;
    os << indent + "\t";
    frst->output(os);
    if (scnd != nullptr) {
        os << "else:";
        os << std::endl;
        os << indent + "\t";
        scnd->output(os);
        os << std::endl;
    }
}

void Asgn::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << name << " = ";
    expn->output(os);
    os << std::endl;
}

void Ntro::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << name << " : " << type_name(type) << " = ";
    expn->output(os);
    os << std::endl;
}

void PlEq::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << name << " += ";
    expn->output(os);
    os << std::endl;
}

void MnEq::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << name << " -= ";
    expn->output(os);
    os << std::endl;
}

void Pass::output(std::ostream& os, std::string indent) const {
    os << indent << "pass" << std::endl;
}

void Proc::output(std::ostream& os, std::string indent) const {
    os << indent << name << "(";
    int count = 0;
    int lngth = xpns.size();
    for (Expn_ptr expn : xpns) {
        expn->output(os);
        if (count != lngth-1) { os << ", "; }
    }
    os << ")" << std::endl;
 }

void Rtrn::output(std::ostream& os, std::string indent) const {
    os << indent << "return";
    if (expn) { os << std::endl; }
}

void Prnt::output(std::ostream& os, std::string indent) const {
    os << indent;
    os << "print";
    os << "(";
    int count = 0;
    int lngth = xpns.size();
    for (Expn_ptr expn : xpns) {
        expn->output(os);
        if (count != lngth-1) { os << ", "; }
    }
    os << ")" << std::endl;
}

void Func::output(std::ostream& os) const {
    os << name << "(";
    int count = 0;
    int lngth = xpns.size();
    for (Expn_ptr expn : xpns) {
        expn->output(os);
        if (count != lngth-1) { os << ", "; }
    }
    os << ")" << std::endl;
}

 void Conj::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " and ";
    rght->output(os);
    os << ")";
}

void Disj::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " or ";
    rght->output(os);
    os << ")";
}

void Less::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " < ";
    rght->output(os);
    os << ")";
}

void LsEq::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " <= ";
    rght->output(os);
    os << ")";
}

void Equl::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " = ";
    rght->output(os);
    os << ")";
}

void Plus::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " + ";
    rght->output(os);
    os << ")";
}

void Mnus::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " - ";
    rght->output(os);
    os << ")";
}

void Tmes::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " * ";
    rght->output(os);
    os << ")";
}

void IDiv::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " // ";
    rght->output(os);
    os << ")";
}

void IMod::output(std::ostream& os) const {
    os << "(";
    left->output(os);
    os << " % ";
    rght->output(os);
    os << ")";
}

void LNot::output(std::ostream& os) const {
    os << "not ";
    expn->output(os);
}
void Ltrl::output(std::ostream& os) const {
    os << to_repr(valu);
}

void Lkup::output(std::ostream& os) const {
    os << name;
}

void Inpt::output(std::ostream& os) const {
    os << "input(";
    expn->output(os);
    os << ")";
}

void IntC::output(std::ostream& os) const {
    os << "int(";
    expn->output(os);
    os << ")";
}

void StrC::output(std::ostream& os) const {
    os << "str(";
    expn->output(os);
    os << ")";
}


// * * * * *
//
// AST::dump
//
// - Dumps the AST of DWISLPY code.
//
// The code below dumps the contents of an AST as a series of lines
// indented and headed by the AST node type and its subcontents.
//

void dump_indent(int level) {
    //std::string indent { level, std::string {"    "} };
    for (int i=0; i<level; i++) {
        std::cout << "    ";
    }
}

void Prgm::dump(int level) const {
    dump_indent(level);
    std::cout << "PRGM" << std::endl;
    for (Defn_ptr defn : defs) {
        defn->dump(level+1);
    }
    if (main) {main->dump(level+1);}
}

void Defn::dump(int level) const {
    // from Jim's starter
    dump_indent(level);
    std::cout << "DEFN" << type_name(rety) << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
    for (unsigned int i=0; i < arity(); i++) {
        dump_indent(level+1);
        SymInfo_ptr frml = formal(i);
        std::cout << frml->name << ":" << type_name(frml->type) << std::endl;
    }
    nest->dump(level+1);
}

void Nest::dump(int level) const {
    dump_indent(level);
    std::cout << "NEST" << std::endl;
    blck->dump(level+1);
}

void Blck::dump(int level) const {
    dump_indent(level);
    std::cout << "BLCK" << std::endl;
    for (Stmt_ptr stmt : stmts) {
        stmt->dump(level+1);
    }
}

void Ifif::dump(int level) const {
    dump_indent(level);
    std::cout << "IFIF" << std::endl;
    cond->dump(level+1);
    frst->dump(level+1);
    if (scnd != nullptr) {
        dump_indent(level);
        std::cout << "ELSE" << std::endl;
        scnd->dump(level+1);
    }
}

void Untl::dump(int level) const {
    dump_indent(level);
    std::cout << "REPT" << std::endl;
    nest->dump(level+1);
    dump_indent(level+1);
    std::cout << "UNTL" << std::endl;
    cond->dump(level+2);
}

void Whil::dump(int level) const {
    dump_indent(level);
    std::cout << "WHIL" << std::endl;
    cond->dump(level+1);
    nest->dump(level+1);
}

void Asgn::dump(int level) const {
    dump_indent(level);
    std::cout << "ASGN" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
    expn->dump(level+1);
}

void Ntro::dump(int level) const {
    dump_indent(level);
    std::cout << "NTRO" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
    dump_indent(level+1);
    std::cout << type_name(type) << std::endl;
    expn->dump(level+1);
}

void PlEq::dump(int level) const {
    dump_indent(level);
    std::cout << "PlEq" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
    expn->dump(level+1);
}

void MnEq::dump(int level) const {
    dump_indent(level);
    std::cout << "MnEq" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
    expn->dump(level+1);
}

void Prnt::dump(int level) const {
    dump_indent(level);
    std::cout << "PRNT" << std::endl;
    for (Expn_ptr expn : xpns) {
        expn->dump(level+1);
    }
}

void Proc::dump(int level) const {
    dump_indent(level);
    std::cout << "PROC" << std::endl;
    for (Expn_ptr expn : xpns) {
        expn->dump(level+1);
    }
}

void Rtrn::dump(int level) const {
    dump_indent(level);
    std::cout << "RTRN" << std::endl;
    if (expn) {
        expn->dump(level+1);
    }
}

void Pass::dump(int level) const {
    dump_indent(level);
    std::cout << "PASS" << std::endl;
}

void Func::dump(int level) const {
    dump_indent(level);
    std::cout << "FUNC" << type_name(type) << std::endl;
    for (Expn_ptr expn : xpns) {
        expn->dump(level+1);
    }
}

void Conj::dump(int level) const {
    dump_indent(level);
    std::cout << "CONJ" << type_name(type) << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Disj::dump(int level) const {
    dump_indent(level);
    std::cout << "DISJ" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Less::dump(int level) const {
    dump_indent(level);
    std::cout << "LESS" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void LsEq::dump(int level) const {
    dump_indent(level);
    std::cout << "LSEQ" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Equl::dump(int level) const {
    dump_indent(level);
    std::cout << "EQUL" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Plus::dump(int level) const {
    dump_indent(level);
    std::cout << "PLUS" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Mnus::dump(int level) const {
    dump_indent(level);
    std::cout << "MNUS" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void Tmes::dump(int level) const {
    dump_indent(level);
    std::cout << "TMES" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void IDiv::dump(int level) const {
    dump_indent(level);
    std::cout << "IDIV" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void IMod::dump(int level) const {
    dump_indent(level);
    std::cout << "IDIV" << std::endl;
    left->dump(level+1);
    rght->dump(level+1);
}

void LNot::dump(int level) const {
    dump_indent(level);
    std::cout << "LNOT" << std::endl;
    expn->dump(level+1);
}

void Ltrl::dump(int level) const {
    dump_indent(level);
    std::cout << "LTRL" << type_name(type) << std::endl;
    dump_indent(level+1);
    std::cout << to_repr(valu) << std::endl;
}

void Lkup::dump(int level) const {
    dump_indent(level);
    std::cout << "LKUP" << std::endl;
    dump_indent(level+1);
    std::cout << name << std::endl;
}

void Inpt::dump(int level) const {
    dump_indent(level);
    std::cout << "INPT" << std::endl;
    expn->dump(level+1);
}

void IntC::dump(int level) const {
    dump_indent(level);
    std::cout << "INTC" << std::endl;
    expn->dump(level+1);
}

void StrC::dump(int level) const {
    dump_indent(level);
    std::cout << "STRC" << std::endl;
    expn->dump(level+1);
}
