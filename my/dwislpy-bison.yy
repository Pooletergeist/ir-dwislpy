%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {DWISLPY}
%define api.parser.class {Parser}
%define parse.error verbose
    
%code requires{
    
    #include "dwislpy-ast.hh"
    #include "dwislpy-check.hh"

    namespace DWISLPY {
        class Driver;
        class Lexer;
    }

    #define YY_NULLPTR nullptr

}

%parse-param { Lexer  &lexer }
%parse-param { Driver &main  }
    
%code{

    #include <sstream>
    #include "dwislpy-util.hh"    
    #include "dwislpy-main.hh"

    #undef yylex
    #define yylex lexer.yylex
    
}


%define api.value.type variant
%define parse.assert
%define api.token.prefix {Token_}

%locations

%token               EOFL  0  
%token               EOLN
%token               INDT
%token               DEDT
%token               PASS "pass"
%token               PRNT "print"
%token               INPT "input"
%token               INTC "int"
%token               STRC "str"
%token               BOOL "bool"
%token               ARRW "->"
%token               ASGN "="

%token		         PLEQ "+="
%token               MNEQ "-="
%token		         CONJ "and"
%token		         DISJ "or"
%token		         LESS "<"
%token		         LSEQ "<="
%token		         EQUL "=="
%token		         LNOT "not"
%token		         IFIF "if"
%token		         ELSE "else"
%token		         REPT "repeat"
%token		         UNTL "until"
%token		         WHIL "while"
%token               RTRN "return"
%token               DEFN "def"
%token               CMMA ","
%token               COLN ":"

%token               PLUS "+"
%token               MNUS "-"
%token               TMES "*"
%token               IDIV "//"
%token               IMOD "%"
%token               LPAR "(" 
%token               RPAR ")"
%token               NONE "None"
%token               TRUE "True"
%token               FALS "False"
%token <int>         NMBR
%token <std::string> NAME
%token <std::string> STRG

%type <Prgm_ptr> prgm
%type <Defs> defs
%type <Defn_ptr> defn
%type <SymT>     nmes
%type <Type>     type
%type <Nest_ptr> nest
%type <Blck_ptr> blck
%type <Stmt_vec> stms
%type <Stmt_ptr> stmt
%type <Expn_ptr> expn
%type <Expn_vec> xpns

%%

%start main;

%left DISJ;
%left CONJ;
%precedence NOT;
%precedence EQUL LSEQ LESS;
%left PLUS MNUS;
%left TMES IMOD IDIV;
    
main:
  prgm {
      main.set($1);
  }
;

nest:
    INDT blck DEDT {
      Defs ds { };
      Blck_ptr b = $2; 
      $$ = Nest_ptr { new Nest {ds, b, b->where()} };
    }
    | INDT blck EOFL {
      Defs ds { };
      Blck_ptr b = $2; 
      $$ = Nest_ptr { new Nest {ds, b, b->where()} };
    }
;

prgm:
  defs blck {
    Defs ds = $1;
    Blck_ptr b = $2;
    $$ = Prgm_ptr { new Prgm {ds, b, b->where()} }; 
  }
| blck {
      Defs ds { };
      Blck_ptr b = $1; 
      $$ = Prgm_ptr { new Prgm {ds, b, b->where()} };
  }   
| defs {
    Defs ds = $1;
    $$ = Prgm_ptr { new Prgm {ds, Blck_ptr{nullptr}, lexer.locate(@1)} };
  }
;

defs:
  defs defn {
    Defs dd = $1;
    dd.push_back($2);
    $$ = dd;
  }
| defn {
    Defs dd { };
    dd.push_back($1);
    $$ = dd;
  }
;

defn:
  DEFN NAME LPAR nmes RPAR ARRW type COLN EOLN nest {
    $$ = Defn_ptr { new Defn {$2, $4, $7, $10, lexer.locate(@1) } };
  }
| DEFN NAME LPAR nmes RPAR COLN EOLN nest {
    $$ = Defn_ptr { new Defn {$2, $4, NoneTy {}, $8, lexer.locate(@1) } };
  }
;

blck:
  stms {
      Stmt_vec ss = $1;
      $$ = Blck_ptr { new Blck {ss, ss[0]->where()} };
  }
;

stms:
  stms stmt {
      Stmt_vec ss = $1;
      ss.push_back($2);
      $$ = ss;
  }
| stmt {
      Stmt_vec ss { };
      ss.push_back($1);
      $$ = ss;
  }
;
  
stmt: 
  NAME COLN type ASGN expn EOLN {
    $$ = Ntro_ptr { new Ntro { $1, $3, $5, lexer.locate(@2)} };
  }
| NAME ASGN expn EOLN {
      $$ = Asgn_ptr { new Asgn {$1,$3,lexer.locate(@2)} };
  }
| IFIF expn COLN EOLN nest ELSE COLN EOLN nest {
      $$ = Ifif_ptr { new Ifif {$2, $5, $9, lexer.locate(@2)} };
  }
| IFIF expn COLN EOLN nest {
      $$ = Ifif_ptr { new Ifif {$2, $5, nullptr, lexer.locate(@2)} };
  }
| REPT COLN EOLN nest UNTL expn EOLN {
      $$ = Untl_ptr { new Untl {$4, $6, lexer.locate(@1)} };
  }
| WHIL expn COLN EOLN nest {
      $$ = Whil_ptr { new Whil {$2, $5, lexer.locate(@2)} };
  }
| NAME PLEQ expn EOLN {
      $$ = PlEq_ptr { new PlEq {$1, $3, lexer.locate(@2)} };
  }
| NAME MNEQ expn EOLN {
      $$ = MnEq_ptr { new MnEq {$1, $3, lexer.locate(@2)} };
  }
| PASS EOLN {
      $$ = Pass_ptr { new Pass {lexer.locate(@1)} };
  }
| PRNT LPAR xpns RPAR EOLN {
      $$ = Prnt_ptr { new Prnt {$3,lexer.locate(@1)} };
  }
| RTRN expn EOLN {
      $$ = Rtrn_ptr { new Rtrn {$2, lexer.locate(@1)} };
  }
| RTRN EOLN {
      $$ = Rtrn_ptr { new Rtrn {Expn_ptr{nullptr}, lexer.locate(@1)} };
  }
| NAME LPAR xpns RPAR EOLN {
      $$ = Proc_ptr { new Proc {$1, $3, lexer.locate(@1)} };
  }
;

expn:
  NAME LPAR xpns RPAR {
      $$ = Func_ptr { new Func {$1, $3, lexer.locate(@1)} };
  }
| expn CONJ expn {
      $$ = Conj_ptr { new Conj {$1,$3,lexer.locate(@2)} };
  }
| expn DISJ expn {
      $$ = Disj_ptr { new Disj {$1,$3,lexer.locate(@2)} };
  }
| expn LESS expn {
      $$ = Less_ptr { new Less {$1,$3,lexer.locate(@2)} };
  }
| expn LSEQ expn {
      $$ = LsEq_ptr { new LsEq {$1,$3,lexer.locate(@2)} };
  }
| expn EQUL expn {
      $$ = Equl_ptr { new Equl {$1,$3,lexer.locate(@2)} };
  }
| LNOT expn {
      $$ = LNot_ptr { new LNot {$2,lexer.locate(@2)} };
  }
| expn PLUS expn {
      $$ = Plus_ptr { new Plus {$1,$3,lexer.locate(@2)} };
  }
| expn MNUS expn {
      $$ = Mnus_ptr { new Mnus {$1,$3,lexer.locate(@2)} };
  }
| expn TMES expn {
      $$ = Tmes_ptr { new Tmes {$1,$3,lexer.locate(@2)} };
  }
| expn IDIV expn {
      $$ = IDiv_ptr { new IDiv {$1,$3,lexer.locate(@2)} };
  }
| expn IMOD expn {
      $$ = IMod_ptr { new IMod {$1,$3,lexer.locate(@2)} };
  }
| NMBR {
      $$ = Ltrl_ptr { new Ltrl {Valu {$1},lexer.locate(@1)} };
  }
| STRG {
      $$ = Ltrl_ptr { new Ltrl {Valu {de_escape($1)},lexer.locate(@1)} };
  }
| TRUE {
      $$ = Ltrl_ptr { new Ltrl {Valu {true},lexer.locate(@1)} };
  }
| FALS {
      $$ = Ltrl_ptr { new Ltrl {Valu {false},lexer.locate(@1)} };
  }
| NONE {
      $$ = Ltrl_ptr { new Ltrl {Valu {None},lexer.locate(@1)} };
  }    
| INPT LPAR expn RPAR {
      $$ = Inpt_ptr { new Inpt {$3,lexer.locate(@1)} };
  }
| INTC LPAR expn RPAR {
      $$ = IntC_ptr { new IntC {$3,lexer.locate(@1)} };
  }
| STRC LPAR expn RPAR {
      $$ = StrC_ptr { new StrC {$3,lexer.locate(@1)} };
  }
| NAME {
      $$ = Lkup_ptr { new Lkup {$1,lexer.locate(@1)} };
  }
| LPAR expn RPAR {
      $$ = $2;
  }
;

nmes:
  nmes CMMA NAME COLN type {
    SymT st = $1;
    st.add_frml($3,$5); 
    $$ = st; 
  }
| NAME COLN type {
    SymT st = { };
    st.add_frml($1,$3);
    $$ = st;
  }
| {
    SymT st = { };
    $$ = st;
  }
;

type:
  INTC { $$ = IntTy {}; }
| STRC { $$ = StrTy {}; }
| BOOL { $$ = BoolTy {}; }
| NONE { $$ = NoneTy {}; }
;



xpns:
  xpns CMMA expn {
    Expn_vec ee = $1;
    ee.push_back($3); 
    $$ = ee; 
  }
| expn {
    Expn_vec ee = { };
    ee.push_back($1);
    $$ = ee;
  }
| {
    Expn_vec ee = { };
    $$ = ee;
  }
;

%%
       
void DWISLPY::Parser::error(const location_type &loc, const std::string &msg) {
    throw DwislpyError { lexer.locate(loc), msg };
}
