#include <variant>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "dwislpy-check.hh"
#include "dwislpy-ast.hh"
#include "dwislpy-util.hh"

Type type_of(Rtns rtns) {
    if (std::holds_alternative<VoidOr>(rtns)) {
        return std::get<VoidOr>(rtns).type;
    }
    if (std::holds_alternative<Type>(rtns)) {
        return std::get<Type>(rtns);
    }
    return Type {NoneTy {}}; // Should not happen. Unless you call on a void?
}

Rtns operator+ (Rtns r1, Rtns r2) {
    if (std::holds_alternative<VoidOr>(r1) && 
        std::holds_alternative<VoidOr>(r2)) {
        // if r1 is VoidOr and r2 is VoidOr
        if (type_of(r1) == type_of(r2)) {
        // check that types match
            return r1;
        } else {
            throw std::invalid_argument("error +'ing Rtns with diff types");
        }
    } 
    else if (std::holds_alternative<VoidOr>(r1) &&
        std::holds_alternative<Type>(r2)) {
        // if r1 is VoidOr and r2 is Type
        if (type_of(r1) == type_of(r2)) {
        // check that types match
        return r1;
        } else {
            throw std::invalid_argument("error +'ing Rtns with diff types");
        }
    } 
    else if (std::holds_alternative<VoidOr>(r1)) { 
        // if r1 is VoidOr and r2 is Void
        return r1;
    } 
    else if (std::holds_alternative<Type>(r1) && 
        std::holds_alternative<VoidOr>(r2)) {
        // if r1 is Type and r2 is VoidOr
        if (type_of(r1) == type_of(r2)) {
        // check that types match
        return r2;
        } else {
            throw std::invalid_argument("error +'ing Rtns with diff types");
        }
    } 
    else if (std::holds_alternative<Type>(r1) && 
        std::holds_alternative<Type>(r2)) {
        // if r1 is Type and r2 is Type
        if (type_of(r1) == type_of(r2)) {
        // check that types match
        return r2;
        } else {
            throw std::invalid_argument("error +'ing Rtns with diff types");
        }
    } 
    else if (std::holds_alternative<Type>(r1)) {
        // if r1 is Type and r2 is Void
        // RETURN VOIDOR
        return VoidOr{ type_of(r1) };
    } 
    else if (std::holds_alternative<Void>(r1) &&
        std::holds_alternative<VoidOr>(r2)) {
        // if r1 is Void and r2 is VoidOr
        return r2;
    } 
    else if (std::holds_alternative<Void>(r1) &&
        std::holds_alternative<Type>(r2)) {
        // if r1 is Void and r2 is Type
        // RETURN VOIDOR
        return VoidOr{ type_of(r2) };
    } 
    else {
        // r1 is Void and r2 is Void
        return r1;
    }
}

bool operator== (Rtns r1, Rtns r2) {
    if (std::holds_alternative<Void>(r1) &&
        std::holds_alternative<Void>(r2)) {
        return true;
    } else if (std::holds_alternative<VoidOr>(r1) &&
        std::holds_alternative<VoidOr>(r2)) {
        if (type_of(r1) == type_of(r2)) {
            return true;
        } else {
            return false;
        }
    } else if (std::holds_alternative<Type>(r1) &&
        std::holds_alternative<Type>(r2)) {
        if (type_of(r1) == type_of(r2)) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool is_int(Type type) {
    return std::holds_alternative<IntTy>(type);
}

bool is_str(Type type) {
    return std::holds_alternative<StrTy>(type);
}

bool is_bool(Type type) {
    return std::holds_alternative<BoolTy>(type);
}

bool is_None(Type type) {
    return std::holds_alternative<NoneTy>(type);
}

bool operator==(Type type1, Type type2) {
    if (is_int(type1) && is_int(type2)) {
        return true;
    }
    if (is_str(type1) && is_str(type2)) {
        return true;
    }
    if (is_bool(type1) && is_bool(type2)) {
        return true;
    }
    if (is_None(type1) && is_None(type2)) {
        return true;
    }
    return false;
}

bool operator!=(Type type1, Type type2) {
    return !(type1 == type2);
}

std::string type_name(Type type) {
    if (is_int(type)) {
        return "int";
    }
    if (is_str(type)) {
        return "str";
    }
    if (is_bool(type)) {
        return "bool";
    } 
    if (is_None(type)) {
        return "None";
    }
    return "wtf";
}

unsigned int Defn::arity(void) const {
    return symt.get_frmls_size();
}

Type Defn::returns(void) const {
    return rety;
}

SymInfo_ptr Defn::formal(int i) const {
    return symt.get_frml(i);
}

// CHECK METHODS! ************** //
// 
void Prgm::chck(void) {
    for (Defn_ptr dfpr : defs) {
        dfpr->chck(defs);
    }
    if (main) {
        Rtns rtns = main->chck(Rtns{Void {}},defs,main_symt);
        if (!std::holds_alternative<Void>(rtns)) {
            DwislpyError(main->where(), "Main script should not return.");
        }
    }
}

Rtns Nest::chck(Rtns expd, [[maybe_unused]] Defs& defs, 
    [[maybe_unused]] SymT& symt) {
   
    Rtns n = blck->chck(expd,defs,symt);

    return n; // Fix this!!
}

void Defn::chck(Defs& defs) {
    Rtns rtns = nest->chck(Rtns{rety}, defs, symt);
    if (!(rtns == rety)) {
        throw DwislpyError { where(), "Mismatch return types" };
    }
}



Rtns Untl::chck(Rtns expd, Defs& defs, SymT& symt) {
    Type cond_ty = cond->chck(defs,symt);
    if (is_bool(cond_ty)) {
        Rtns b1 = nest->chck(expd,defs,symt);
        return b1;
    } else {
        std::string msg = "condition not a boolean";
        throw DwislpyError { where(), msg };
    }
}

Rtns Whil::chck(Rtns expd, Defs& defs, SymT& symt) {
    Type cond_ty = cond->chck(defs,symt);
    if (is_bool(cond_ty)) {
        Rtns b1 = nest->chck(expd,defs,symt);
        return b1 + Rtns {Void {}};
    } else {
        std::string msg = "condition not a boolean";
        throw DwislpyError { where(), msg };
    }
}

Rtns Ifif::chck(Rtns expd, Defs& defs, SymT& symt) {
    Type cond_ty = cond->chck(defs,symt);
    // symt.displayTable(); debug
    if (is_bool(cond_ty)) {
        Rtns b1 = frst->chck(expd,defs,symt);
        if (scnd) { // there's an else
            Rtns b2 = scnd->chck(expd,defs,symt);
            return b1+b2;
        } else {
            return b1 + Rtns{Void{}}; //uses overloaded "+" for sum type
        }
    } else {
        std::string msg = "condition not a boolean";
        throw DwislpyError { where(), msg };
    }
}

Rtns Asgn::chck(Rtns expd, Defs& defs, SymT& symt) {
    if (symt.has_info(name)) { // left hand defined
        Type t1 = symt.get_info(name)->type; // lhs type
        Type t2 = expn->chck(defs,symt); // rhs type
        if (t1 == t2) { // same type
            return Type {NoneTy {}}; // checks-out! & we say Asgn no return
        } else {
            std::string msg = "Mismatch types for Asgn";
            throw DwislpyError { where(), msg };
        }
    } else {
        std::string msg = "Unknown identifier.";
        throw DwislpyError {where(), msg };
    }
}

Rtns PlEq::chck(Rtns expd, Defs& defs, SymT& symt) {
    return Rtns {Void {}}; // Fix this!!
}

Rtns MnEq::chck(Rtns expd, Defs& defs, SymT& symt) {
    return Rtns {Void {}}; // Fix this!!
}

Rtns Prnt::chck(Rtns expd, Defs& defs, SymT& symt) {
    for (Expn_ptr expn : xpns) {
        Type expn_ty = expn->chck(defs,symt); //check the expn within the prnt
    }
    return Rtns {Void {}}; // Fix this!!
}

Rtns Ntro::chck([[maybe_unused]] Rtns expd, Defs& defs, SymT& symt) {
    // check that the type declared matches type of expression.
    if (type == expn->chck(defs,symt)) {
        // add the info to symbol table with Symt::add_locl
         symt.add_locl(name, type);
    } else {
        std::string msg = "type declared doesn't match type of expn in Ntro";
        throw DwislpyError { where(), msg };
    }
    return Rtns {Void {}}; // Ntro doesn't return
}

Rtns Proc::chck(Rtns expd, Defs& defs, SymT& symt) {
    // lookup name within defs, a vector of Defn_ptrs.
    Defn_ptr my_proc = nullptr;
    for (Defn_ptr defn : defs) {
        if (defn->name == name) {
           my_proc = defn;
        } 
    }
    if (my_proc) {
        // use get_frmls_size to check # params expected against passed
        int num_params_expected = my_proc->symt.get_frmls_size();
        int num_params_passed = xpns.size();
        if (num_params_expected == num_params_passed) {
            // check types of params using get_frml
            for (int i=0; i<num_params_passed; i++) {
                Expn_ptr expn = xpns[i];
                // how to get type from symt?
                Type expected_ty = my_proc->symt.get_frml(i)->type;
                if (expn->chck(defs,symt) != expected_ty) {
                    // throw error
                    std::string msg = "type of argument not expected";
                    throw DwislpyError { where(), msg };
                }
            }
        } else {
            std::string msg = "procedure passed an unexpected number of params";
            throw DwislpyError { where(), msg };
        }
    } else { 
        std::string msg = "procedure being called hasn't been defined";
        throw DwislpyError { where(), msg };
    }
    return Rtns {Void {}}; // procedures don't return
}

Rtns Rtrn::chck(Rtns expd, Defs& defs, SymT& symt) {
    if (expn) { // procedure return has wrapped nullptr
        Type expn_ty = expn->chck(defs,symt);
        if (expn_ty == type_of(expd)) {
            return Rtns {expn_ty};
        } else {
            std::string msg = "return type doesn't match expected";
            throw DwislpyError { where(), msg };
        }
    } else if (type_of(expd) == NoneTy {}) {
        return Rtns {NoneTy {}};
    }
}

Rtns Pass::chck(Rtns expd, Defs& defs, SymT& symt) {
    return Rtns {Void {}}; 
}

Rtns Blck::chck(Rtns expd, Defs& defs, SymT& symt) {
    
    // Scan through the statements and check their return behavior.
    // TODO: return a summarization of the behaviors!

    Rtns prior = Void {};
    for (Stmt_ptr stmt : stmts) {
        
        // Check this statement.
        [[maybe_unused]]
        Rtns stmt_rtns = stmt->chck(expd, defs, symt);

        if (std::holds_alternative<Type>(prior)) {
            throw DwislpyError { where(), "illegal statements after a return" };
        } else if (std::holds_alternative<VoidOr>(prior)) {
            if (!std::holds_alternative<Void>(stmt_rtns) &&
                type_of(prior) != type_of(stmt_rtns)) {
                throw DwislpyError { where(), "blck can return diff type" };
            } else {
                prior = stmt_rtns;
            }
        } else {
            prior = stmt_rtns;
        }
    }
    return prior;
}

Type Func::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    // lookup name within defs, a vector of Defn_ptrs.
    Defn_ptr my_func = nullptr;
    for (Defn_ptr defn : defs) {
        if (defn->name == name) {
           my_func = defn;
        } 
    }
    if (my_func) {
        // use get_frmls_size to check # params expected against passed
        int num_params_expected = my_func->symt.get_frmls_size();
        int num_params_passed = xpns.size();
        if (num_params_expected == num_params_passed) {
            // check types of params using get_frml
            for (int i=0; i<num_params_passed; i++) {
                Expn_ptr expn = xpns[i];
                // how to get type from symt?
                Type expected_ty = my_func->symt.get_frml(i)->type;
                if (expn->chck(defs,symt) != expected_ty) {
                    // throw error
                    std::string msg = "type of argument not expected";
                    throw DwislpyError { where(), msg };
                }
            }
        } else {
            std::string msg = "function passed an unexpected number of params";
            throw DwislpyError { where(), msg };
        }
    } else { 
        std::string msg = "function being called hasn't been defined";
        throw DwislpyError { where(), msg };
    }

    // return type from def
    return my_func->rety;
}

Type Conj::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    // takes two bool, returns bool
    Type left_ty = left->chck(defs,symt);
    Type rght_ty = rght->chck(defs,symt);
    if (is_bool(left_ty) && is_bool(rght_ty)) { // both bool?
        return Type {BoolTy {}}; 
    } else {
        std::string msg = "Mistmatched operand types for Conj.";
        throw DwislpyError { where(), msg };
    }
}

Type Disj::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    // takes two bool, returns bool
    Type left_ty = left->chck(defs,symt);
    Type rght_ty = rght->chck(defs,symt);
    if (is_bool(left_ty) && is_bool(rght_ty)) { // both bool?
        return Type {BoolTy {}}; 
    } else {
        std::string msg = "Mistmatched operand types for Disj.";
        throw DwislpyError { where(), msg };
    }
}

Type Less::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    //LsEq takes two int, returns bool
    Type left_ty = left->chck(defs,symt);
    Type rght_ty = rght->chck(defs,symt);
    if (is_int(left_ty) && is_int(rght_ty)) { // both int?
        return Type {BoolTy {}};
    } else {
        std::string msg = "Mistmatched operand types for Less.";
        throw DwislpyError { where(), msg };
    }
}

Type LsEq::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    //LsEq takes two int, returns bool
    Type left_ty = left->chck(defs,symt);
    Type rght_ty = rght->chck(defs,symt);
    if (is_int(left_ty) && is_int(rght_ty)) { // both int?
        return Type {BoolTy {}};
    } else {
        std::string msg = "Mistmatched operand types for LsEq.";
        throw DwislpyError { where(), msg };
    }
}

Type Equl::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    //Equl takes two int, bool, or string. returns bool
    Type left_ty = left->chck(defs,symt);
    Type rght_ty = rght->chck(defs,symt);
    if (is_int(left_ty) && is_int(rght_ty)) { // both int?
        return Type {BoolTy {}};
    } else if (is_str(left_ty) && is_str(rght_ty)) { // both str?
        return Type {BoolTy {}}; 
    } else if (is_bool(left_ty) && is_bool(rght_ty)) { // both bool?
        return Type {BoolTy {}}; 
    } else {
        std::string msg = "Mistmatched operand types for Equl.";
        throw DwislpyError { where(), msg };
     }
}

Type LNot::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    // takes bool. returns bool
    Type expn_ty = expn->chck(defs,symt);
    if (is_bool(expn_ty)) { // Not takes a bool
        return Type {BoolTy {}}; // Not returns a bool
    } else {
        std::string msg = "Wrong input type to LNot";
        throw DwislpyError { where(), msg };
    }
}

Type Plus::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    // takes two int or two str, returns type of inputs
    Type left_ty = left->chck(defs,symt);
    Type rght_ty = rght->chck(defs,symt);
    if (left_ty == Type {IntTy {}} && rght_ty == Type {IntTy {}}) {
        return Type {IntTy {}};
    } else if (is_str(left_ty) && is_str(rght_ty)) {
        return Type {StrTy {}}; 
    } else {
        std::string msg = "Wrong operand types for plus.";
        throw DwislpyError { where(), msg };
    }
}

Type Mnus::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    // takes two int. returns int
    Type left_ty = left->chck(defs,symt);
    Type rght_ty = rght->chck(defs,symt);
    if (is_int(left_ty) && is_int(rght_ty)) { // both int?
        return Type {IntTy {}};
    } else {
        std::string msg = "Mistmatched operand types for Mnus.";
        throw DwislpyError { where(), msg };
    }
}

Type Tmes::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    // takes two int. returns int
    Type left_ty = left->chck(defs,symt);
    Type rght_ty = rght->chck(defs,symt);
    if (is_int(left_ty) && is_int(rght_ty)) { // both int?
        return Type {IntTy {}};
    } else {
        std::string msg = "Mistmatched operand types for Tmes.";
        throw DwislpyError { where(), msg };
    }
}

Type IMod::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    // takes two int. returns int
    Type left_ty = left->chck(defs,symt);
    Type rght_ty = rght->chck(defs,symt);
    if (is_int(left_ty) && is_int(rght_ty)) { // both int?
        return Type {IntTy {}};
    } else {
        std::string msg = "Mistmatched operand types for IMod.";
        throw DwislpyError { where(), msg };
    }
}

Type IDiv::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    // takes two int. returns int
    Type left_ty = left->chck(defs,symt);
    Type rght_ty = rght->chck(defs,symt);
    if (is_int(left_ty) && is_int(rght_ty)) { // both int?
        return Type {IntTy {}};
    } else {
        std::string msg = "Mistmatched operand types for IDiv.";
        throw DwislpyError { where(), msg };
    }
}

Type Ltrl::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    if (std::holds_alternative<int>(valu)) {
        return Type {IntTy {}};
    } else if (std::holds_alternative<std::string>(valu)) {
        return Type {StrTy {}};
    } if (std::holds_alternative<bool>(valu)) {
        return Type {BoolTy {}};
    } else {
        return Type {NoneTy {}};
    }
}

Type Lkup::chck(Defs& defs, SymT& symt) {
    if (symt.has_info(name)) {
        return symt.get_info(name)->type;
    } else {
        throw DwislpyError {where(), "Unknown identifier."};
    }
}

Type Inpt::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    return Type {IntTy {}};
}

Type IntC::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    return Type {IntTy {}};
}

Type StrC::chck([[maybe_unused]] Defs& defs, [[maybe_unused]] SymT& symt) {
    return Type {StrTy {}};
}

// The end of my decomposition! ****

