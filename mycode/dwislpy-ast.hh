#ifndef __DWISLPY_AST_H_
#define __DWISLPY_AST_H_

// dwislpy-ast.hh
//
// Object classes used by the parser to represent the syntax trees of
// DwiSlpy programs.
//
// It defines a class for a DwiSlpy program and its block of statements,
// and also the two abstract classes whose subclasses form the syntax
// trees of a program's code.
//
//  * Prgm - a DwiSlpy program that consists of a block of statements.
//
//  * Blck - a series of DwiSlpy statements.
//
//  * Stmt - subclasses for the various statments that can occur
//           in a block of code, namely assignment, print, pass,
//           return, and procedure invocation. These get executed
//           when the program runs.
//
//  * Expn - subclasses for the various expressions than can occur
//           on the right-hand side of an assignment statement.
//           These get evaluated to compute a value.
//

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>
#include <iostream>
#include <variant>
#include "dwislpy-util.hh"
#include "dwislpy-check.hh"
#include "dwislpy-inst.hh" // new to HW5

// Valu
//
// The return type of `eval` and of literal values.
// Note: the type `none` is defined in *-util.hh.
//
typedef std::variant<int, bool, std::string, none> Valu;

//
// We "pre-declare" each AST subclass for mutually recursive definitions.
//

class Prgm;
class Defn;
class Nest;
class Blck;
//
class Stmt;
class Pass;
class Asgn;
class Ntro;
//
class PlEq;
class MnEq;
// debug cond
class Ifif;
class Whil;
class Untl;
// debug B
class Rtrn;
class Proc;

class Prnt;
//
class Expn;
// debug B
class Func;

class Plus;
class Mnus;
class Tmes;
class IDiv;
class IMod;
// debug logic
class Conj;
class Disj;
class LNot;
class Less;
class LsEq;
class Equl;
//
class Inpt;
class IntC;
class StrC;
class Lkup;
class Ltrl;

//
// We alias some types, including pointers and vectors.
//

typedef std::string Name;
typedef std::unordered_map<Name,Valu> Ctxt;
//
typedef std::shared_ptr<Lkup> Lkup_ptr; 
typedef std::shared_ptr<Ltrl> Ltrl_ptr; 
typedef std::shared_ptr<IntC> IntC_ptr; 
typedef std::shared_ptr<StrC> StrC_ptr; 
typedef std::shared_ptr<Inpt> Inpt_ptr; 
// debug logicals
typedef std::shared_ptr<Conj> Conj_ptr; 
typedef std::shared_ptr<Disj> Disj_ptr; 
typedef std::shared_ptr<Less> Less_ptr; 
typedef std::shared_ptr<LsEq> LsEq_ptr; 
typedef std::shared_ptr<Equl> Equl_ptr; 
typedef std::shared_ptr<LNot> LNot_ptr; 


typedef std::shared_ptr<Plus> Plus_ptr; 
typedef std::shared_ptr<Mnus> Mnus_ptr; 
typedef std::shared_ptr<Tmes> Tmes_ptr;
typedef std::shared_ptr<IDiv> IDiv_ptr;
typedef std::shared_ptr<IMod> IMod_ptr;
//
typedef std::shared_ptr<Ntro> Ntro_ptr; 
typedef std::shared_ptr<Pass> Pass_ptr; 
typedef std::shared_ptr<Prnt> Prnt_ptr; 
typedef std::shared_ptr<Asgn> Asgn_ptr;
typedef std::shared_ptr<PlEq> PlEq_ptr;
typedef std::shared_ptr<MnEq> MnEq_ptr;
typedef std::shared_ptr<Rtrn> Rtrn_ptr;
typedef std::shared_ptr<Func> Func_ptr;
typedef std::shared_ptr<Proc> Proc_ptr;

// debug Cond
typedef std::shared_ptr<Ifif> Ifif_ptr;
typedef std::shared_ptr<Whil> Whil_ptr;
typedef std::shared_ptr<Untl> Untl_ptr;

//
typedef std::shared_ptr<Prgm> Prgm_ptr; 
typedef std::shared_ptr<Nest> Nest_ptr; 
typedef std::shared_ptr<Defn> Defn_ptr; 
typedef std::shared_ptr<Blck> Blck_ptr; 
typedef std::shared_ptr<Stmt> Stmt_ptr; 
typedef std::shared_ptr<Expn> Expn_ptr;
//
typedef std::vector<Stmt_ptr> Stmt_vec;
typedef std::vector<Expn_ptr> Expn_vec;
typedef std::vector<Name> Name_vec;
typedef std::vector<Defn_ptr> Defs;
//
    
//
//
// ************************************************************

// Syntax tree classes used to represent a DwiSlpy program's code.
//
// The classes Blck, Stmt, Expn are all subclasses of AST.
//

//
// class AST 
//
// Cover top-level type for all "abstract" syntax tree classes.
// I.e. this is *the* abstract class (in the OO sense) that all
// the AST node subclasses are derived from.
//

class AST {
private:
    Locn locn; // Location of construct in source code (for reporting errors).
public:
    AST(Locn lo) : locn {lo} { }
    virtual ~AST(void) = default;
    virtual void output(std::ostream& os) const = 0;
    virtual void dump(int level = 0) const = 0;
    Locn where(void) const { return locn; }
};

//
// class Prgm
//
// An object in this class holds all the information gained
// from parsing the source code of a DwiSlpy program. A program
// is a series of DwiSlpy definitions followed by a block of
// statements.
//
// The method Prgm::run implements the DwiSlpy interpreter. This runs the
// DwiSlpy program, executing its statments, updating the state of
// program variables as a result, getting user input from the console,
// and outputting results to the console.  The interpreter relies on
// the Blck::exec, Stmt::exec, and Expn::eval methods of the various
// syntactic components that constitute the Prgm object.
//

class Prgm : public AST {
public:
    //
    Defs defs;
    Blck_ptr main;
    SymT main_symt;
    //
    Prgm(Defs ds, Blck_ptr mn, Locn lo) :
        AST {lo}, defs {ds}, main {mn}, main_symt{} { }
    virtual ~Prgm(void) = default;
    //
    virtual void chck(void);
    virtual void dump(int level = 0) const;
    virtual void run(void) const; // Execute the program.
    virtual void output(std::ostream& os) const; // Output formatted code.
    virtual void trans(void);   // translate to IR
    virtual void compile(std::ostream& os); // generate MIPS
};

class Nest: public AST {
public:
    //
    Defs defs;
    Blck_ptr blck;
    //
    Nest(Defs ds, Blck_ptr bk, Locn lo) :
        AST {lo}, defs {ds}, blck {bk} { }
    virtual ~Nest(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
};

//
// class Defn
//
// This should become the AST node type that results from parsing
// a `def`. Right now it contains no information.
//
class Defn : public AST {
public:
    //
    Name name;
    SymT symt;
    Type rety; 
    Nest_ptr nest; 
    //
    Defn(Name nm, SymT sy, Type rt, Nest_ptr ns, Locn lo) : 
        AST {lo}, name {nm}, symt {sy}, rety {rt}, nest {ns}  { }
    virtual ~Defn(void) = default;
    //
    virtual std::optional<Valu> call(const Defs& defs, const Expn_vec xpns, 
        const Ctxt& ctxt) const;
    virtual void dump(int level = 0) const;
    virtual void output(std::ostream& os) const; // Output formatted code.
    virtual void chck(Defs& defs);
    // to make compiler play nice
    unsigned int arity(void) const; 
    virtual Type returns(void) const;
    SymInfo_ptr formal(int i) const;
    // IR
    virtual void trans(void); // Generate IR code
};

//
// class Stmt
//
// Abstract class for program statment syntax trees,
//
// Subclasses are
//
//   Asgn - assignment statement "v = e"
//   Prnt - output statement "print(e1,e2,...,ek)"
//   Pass - statement that does nothing
//
// These each support the methods:
//
//  * exec(ctxt): execute the statement within the stack frame
//
//  * output(os), output(os,indent): output formatted DwiSlpy code of
//        the statement to the output stream `os`. The `indent` string
//        gives us a string of spaces for indenting the lines of its
//        code.
//
//  * dump: output the syntax tree of the expression
//
class Stmt : public AST {
public:
    Stmt(Locn lo) : AST {lo} { }
    virtual ~Stmt(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const = 0;
    virtual void output(std::ostream& os, std::string indent) const = 0;
    virtual void output(std::ostream& os) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt) = 0;
    // Generate IR code:
    virtual void trans(std::string exit, SymT& symt, INST_vec& code) = 0; 
};

//
// Untl - repeat until stmt AST node
//
class Untl : public Stmt {
public:
    Nest_ptr nest;
    Expn_ptr cond;
    Untl(Nest_ptr n, Expn_ptr x, Locn l) : Stmt {l}, nest {n}, cond {x} { }
    virtual ~Untl(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};

//
// Whil - assignment statement AST node
//
class Whil : public Stmt {
public:
    Expn_ptr cond;
    Nest_ptr nest;
    Whil(Expn_ptr x, Nest_ptr n, Locn l) : Stmt {l}, cond {x}, nest {n} { }
    virtual ~Whil(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};

//
// Ifif - assignment statement AST node
//
class Ifif : public Stmt {
public:
    Expn_ptr cond;
    Nest_ptr frst;
    Nest_ptr scnd;
    Ifif(Expn_ptr x, Nest_ptr f, Nest_ptr s, Locn l) : 
        Stmt {l}, cond {x}, frst {f}, scnd {s} { }
    virtual ~Ifif(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};

//
// Ntro - variable introduction with initializer
//
class Ntro : public Stmt {
public:
    Name name;
    Type type;
    Expn_ptr expn;
    Ntro(Name x, Type t, Expn_ptr e, Locn l) :
        Stmt {l}, name {x}, type {t},expn {e} { }
    virtual ~Ntro(void) = default;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};

//
// Asgn - assignment statement AST node
//
class Asgn : public Stmt {
public:
    Name     name;
    Expn_ptr expn;
    Asgn(Name x, Expn_ptr e, Locn l) : Stmt {l}, name {x}, expn {e} { }
    virtual ~Asgn(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};

//
// PlEq - assignment statement AST node
//
class PlEq : public Stmt {
public:
    Name     name;
    Expn_ptr expn;
    PlEq(Name x, Expn_ptr e, Locn l) : Stmt {l}, name {x}, expn {e} { }
    virtual ~PlEq(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};

//
// MnEq - assignment statement AST node
//
class MnEq : public Stmt {
public:
    Name     name;
    Expn_ptr expn;
    MnEq(Name x, Expn_ptr e, Locn l) : Stmt {l}, name {x}, expn {e} { }
    virtual ~MnEq(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};


//
// Prnt - print statement AST node
//
class Prnt : public Stmt {
public:
    Expn_vec xpns;
    Prnt(Expn_vec xs, Locn l) : Stmt {l}, xpns {xs} { }
    virtual ~Prnt(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};

//
// Proc - statement AST node
//
class Proc : public Stmt {
public:
//
    Name name;
    Expn_vec xpns;
//
    Proc(Name name, Expn_vec xs, Locn l) : Stmt {l}, name {name}, xpns {xs} { }
    virtual ~Proc(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};


//
// Rtrn - statement AST node
//
class Rtrn : public Stmt {
public:
//
    Expn_ptr expn;
//
    Rtrn(Expn_ptr e, Locn l) : Stmt {l}, expn {e} { }
    virtual ~Rtrn(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};

///
// Pass - pass statement AST node
//
class Pass : public Stmt {
public:
    Pass(Locn l) : Stmt {l} { }
    virtual ~Pass(void) = default;
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};

//
// class Blck
//
// Represents a sequence of statements.
//
class Blck : public AST {
public:
    Stmt_vec stmts;
    virtual ~Blck(void) = default;
    Blck(Stmt_vec ss, Locn lo) : AST {lo}, stmts {ss}  { }
    //
    virtual std::optional<Valu> exec(const Defs& defs, Ctxt& ctxt) const;
    virtual void output(std::ostream& os, std::string indent) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Rtns chck(Rtns expd, Defs& defs, SymT& symt);
    virtual void trans(std::string exit, SymT& symt, INST_vec& code);
};


//
// class Expn
//
// Abstract class for integer expression syntax trees,
//
// Subclasses are
//
//   Plus - binary operation + applied to two sub-expressions
//   Mnus - binary operation - applied to two sub-expressions
//   Tmes - binary operation * applied to two sub-expressions
//   Ltrl - value constant expression
//   Lkup - variable access (i.e. "look-up") within function frame
//   Inpt - obtains a string of input (after output of a prompt)
//   IntC - converts a value to an integer value
//   StrC - converts a value to a string value
//
// These each support the methods:
//
//  * eval(ctxt): evaluate the expression; return its result
//  * output(os): output formatted DwiSlpy code of the expression.
//  * dump: output the syntax tree of the expression
//
class Expn : public AST {
public:
    Type type; // for translation into IR.
    Expn(Locn lo) : AST {lo} { }
    virtual ~Expn(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const = 0;
    virtual Type chck(Defs& defs, SymT& symt) = 0;
    virtual void trans(Name dest, SymT& symt, INST_vec& code) = 0;
    virtual void trans_cndn(std::string then_lbl, std::string else_lbl,
                            SymT& symt, INST_vec& code); // Generate IR
};
    
//
// Func - expression AST node
//
class Func: public Expn {
public:
//
    Name name;
    Expn_vec xpns;
//
    Func(Name name, Expn_vec xs, Locn l) : Expn {l}, name {name}, xpns {xs} { }
    virtual ~Func(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
    virtual void trans_cndn(std::string then_lbl, std::string else_lbl, 
                            SymT& symt, INST_vec& code);
};


//
// Conj - binary operation's AST node
//
class Conj : public Expn {
public:
    Expn_ptr left;
    Expn_ptr rght;
    Conj(Expn_ptr lf, Expn_ptr rg, Locn lo)
        : Expn {lo}, left {lf}, rght {rg} { }
    virtual ~Conj(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
    virtual void trans_cndn(std::string then_lbl, std::string else_lbl, 
                            SymT& symt, INST_vec& code);
};

//
// Disj - binary operation's AST node
//
class Disj : public Expn {
public:
    Expn_ptr left;
    Expn_ptr rght;
    Disj(Expn_ptr lf, Expn_ptr rg, Locn lo)
        : Expn {lo}, left {lf}, rght {rg} { }
    virtual ~Disj(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
    virtual void trans_cndn(std::string then_lbl, std::string else_lbl, 
                            SymT& symt, INST_vec& code);
};
 
//
// Less - binary operation's AST node
//
class Less : public Expn {
public:
    Expn_ptr left;
    Expn_ptr rght;
    Less(Expn_ptr lf, Expn_ptr rg, Locn lo)
        : Expn {lo}, left {lf}, rght {rg} { }
    virtual ~Less(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
    virtual void trans_cndn(std::string then_lbl, std::string else_lbl, 
                            SymT& symt, INST_vec& code);
};

//
// LsEq - binary operation's AST node
//
class LsEq : public Expn {
public:
    Expn_ptr left;
    Expn_ptr rght;
    LsEq(Expn_ptr lf, Expn_ptr rg, Locn lo)
        : Expn {lo}, left {lf}, rght {rg} { }
    virtual ~LsEq(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
    virtual void trans_cndn(std::string then_lbl, std::string else_lbl, 
                            SymT& symt, INST_vec& code);
};

//
// Equl - binary operation's AST node
//
class Equl : public Expn {
public:
    Expn_ptr left;
    Expn_ptr rght;
    Equl(Expn_ptr lf, Expn_ptr rg, Locn lo)
        : Expn {lo}, left {lf}, rght {rg} { }
    virtual ~Equl(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
    virtual void trans_cndn(std::string then_lbl, std::string else_lbl, 
                            SymT& symt, INST_vec& code);
};

//
// LNot - binary operation's AST node
//
class LNot : public Expn {
public:
    Expn_ptr expn;
    LNot(Expn_ptr ex, Locn lo)
        : Expn {lo}, expn {ex} { }
    virtual ~LNot(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
    virtual void trans_cndn(std::string then_lbl, std::string else_lbl, 
                            SymT& symt, INST_vec& code);
};

//
// Plus - addition binary operation's AST node
//
class Plus : public Expn {
public:
    Expn_ptr left;
    Expn_ptr rght;
    Plus(Expn_ptr lf, Expn_ptr rg, Locn lo)
        : Expn {lo}, left {lf}, rght {rg} { }
    virtual ~Plus(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
};

//
// Mnus - subtraction binary operation's AST node
//
class Mnus : public Expn {
public:
    Expn_ptr left;
    Expn_ptr rght;
    Mnus(Expn_ptr lf, Expn_ptr rg, Locn lo)
        : Expn {lo}, left {lf}, rght {rg} { }
    virtual ~Mnus(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
};

//
// Tmes - multiplication binary operation's AST node
//
class Tmes : public Expn {
public:
    Expn_ptr left;
    Expn_ptr rght;
    Tmes(Expn_ptr lf, Expn_ptr rg, Locn lo)
        : Expn {lo}, left {lf}, rght {rg} { }
    virtual ~Tmes(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
};

//
// IDiv - quotient binary operation's AST node
//
class IDiv : public Expn {
public:
    Expn_ptr left;
    Expn_ptr rght;
    IDiv(Expn_ptr lf, Expn_ptr rg, Locn lo)
        : Expn {lo}, left {lf}, rght {rg} { }
    virtual ~IDiv(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
};

//
// IMod - remainder binary operation's AST node
//
class IMod : public Expn {
public:
    Expn_ptr left;
    Expn_ptr rght;
    IMod(Expn_ptr lf, Expn_ptr rg, Locn lo)
        : Expn {lo}, left {lf}, rght {rg} { }
    virtual ~IMod(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
};

//
// Ltrl - literal valu AST node
//
class Ltrl : public Expn {
public:
    Valu valu;
    Ltrl(Valu vl, Locn lo) : Expn {lo}, valu {vl} { }
    virtual ~Ltrl(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
    virtual void trans_cndn(std::string then_lbl, std::string else_lbl, 
                            SymT& symt, INST_vec& code);
};


//
// Lkup - variable use/look-up AST node
//
class Lkup : public Expn {
public:
    Name name;
    Lkup(Name nm, Locn lo) : Expn {lo}, name {nm} { }
    virtual ~Lkup(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
    virtual void trans_cndn(std::string then_lbl, std::string else_lbl, 
                            SymT& symt, INST_vec& code);
};

//
// Inpt - input expression AST node
//
class Inpt : public Expn {
public:
    Expn_ptr expn;
    Inpt(Expn_ptr e, Locn lo) : Expn {lo}, expn {e} { }
    virtual ~Inpt(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
};

//
// IntC - int conversion expression AST node
//
class IntC : public Expn {
public:
    Expn_ptr expn;
    IntC(Expn_ptr e, Locn lo) : Expn {lo}, expn {e} { }
    virtual ~IntC(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
};

//
// StrC - string conversion expression AST node
//
class StrC : public Expn {
public:
    Expn_ptr expn;
    StrC(Expn_ptr e, Locn lo) : Expn {lo}, expn {e} { }
    virtual ~StrC(void) = default;
    virtual Valu eval(const Defs& defs, const Ctxt& ctxt) const;
    virtual void output(std::ostream& os) const;
    virtual void dump(int level = 0) const;
    virtual Type chck(Defs& defs, SymT& symt);
    virtual void trans(std::string dest, SymT& symt, INST_vec& code);
};

#endif
