// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "dwislpy-bison.tab.hh"


// Unqualified %code blocks.
#line 26 "dwislpy-bison.yy"


    #include <sstream>
    #include "dwislpy-util.hh"    
    #include "dwislpy-main.hh"

    #undef yylex
    #define yylex lexer.yylex
    

#line 56 "dwislpy-bison.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "dwislpy-bison.yy"
namespace DWISLPY {
#line 148 "dwislpy-bison.tab.cc"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Lexer  &lexer_yyarg, Driver &main_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg),
      main (main_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
    switch (this->type_get ())
    {
      case 47: // nest
      case 48: // blck
        value.move< Blck_ptr > (std::move (that.value));
        break;

      case 44: // defn
        value.move< Defn_ptr > (std::move (that.value));
        break;

      case 43: // defs
        value.move< Defs > (std::move (that.value));
        break;

      case 51: // expn
        value.move< Expn_ptr > (std::move (that.value));
        break;

      case 42: // prgm
        value.move< Prgm_ptr > (std::move (that.value));
        break;

      case 50: // stmt
        value.move< Stmt_ptr > (std::move (that.value));
        break;

      case 49: // stms
        value.move< Stmt_vec > (std::move (that.value));
        break;

      case 45: // fmls
        value.move< SymT > (std::move (that.value));
        break;

      case 46: // type
        value.move< Type > (std::move (that.value));
        break;

      case 37: // NMBR
        value.move< int > (std::move (that.value));
        break;

      case 38: // NAME
      case 39: // STRG
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->type_get ())
    {
      case 47: // nest
      case 48: // blck
        value.copy< Blck_ptr > (YY_MOVE (that.value));
        break;

      case 44: // defn
        value.copy< Defn_ptr > (YY_MOVE (that.value));
        break;

      case 43: // defs
        value.copy< Defs > (YY_MOVE (that.value));
        break;

      case 51: // expn
        value.copy< Expn_ptr > (YY_MOVE (that.value));
        break;

      case 42: // prgm
        value.copy< Prgm_ptr > (YY_MOVE (that.value));
        break;

      case 50: // stmt
        value.copy< Stmt_ptr > (YY_MOVE (that.value));
        break;

      case 49: // stms
        value.copy< Stmt_vec > (YY_MOVE (that.value));
        break;

      case 45: // fmls
        value.copy< SymT > (YY_MOVE (that.value));
        break;

      case 46: // type
        value.copy< Type > (YY_MOVE (that.value));
        break;

      case 37: // NMBR
        value.copy< int > (YY_MOVE (that.value));
        break;

      case 38: // NAME
      case 39: // STRG
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 47: // nest
      case 48: // blck
        value.move< Blck_ptr > (YY_MOVE (s.value));
        break;

      case 44: // defn
        value.move< Defn_ptr > (YY_MOVE (s.value));
        break;

      case 43: // defs
        value.move< Defs > (YY_MOVE (s.value));
        break;

      case 51: // expn
        value.move< Expn_ptr > (YY_MOVE (s.value));
        break;

      case 42: // prgm
        value.move< Prgm_ptr > (YY_MOVE (s.value));
        break;

      case 50: // stmt
        value.move< Stmt_ptr > (YY_MOVE (s.value));
        break;

      case 49: // stms
        value.move< Stmt_vec > (YY_MOVE (s.value));
        break;

      case 45: // fmls
        value.move< SymT > (YY_MOVE (s.value));
        break;

      case 46: // type
        value.move< Type > (YY_MOVE (s.value));
        break;

      case 37: // NMBR
        value.move< int > (YY_MOVE (s.value));
        break;

      case 38: // NAME
      case 39: // STRG
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  Parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  Parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 47: // nest
      case 48: // blck
        value.YY_MOVE_OR_COPY< Blck_ptr > (YY_MOVE (that.value));
        break;

      case 44: // defn
        value.YY_MOVE_OR_COPY< Defn_ptr > (YY_MOVE (that.value));
        break;

      case 43: // defs
        value.YY_MOVE_OR_COPY< Defs > (YY_MOVE (that.value));
        break;

      case 51: // expn
        value.YY_MOVE_OR_COPY< Expn_ptr > (YY_MOVE (that.value));
        break;

      case 42: // prgm
        value.YY_MOVE_OR_COPY< Prgm_ptr > (YY_MOVE (that.value));
        break;

      case 50: // stmt
        value.YY_MOVE_OR_COPY< Stmt_ptr > (YY_MOVE (that.value));
        break;

      case 49: // stms
        value.YY_MOVE_OR_COPY< Stmt_vec > (YY_MOVE (that.value));
        break;

      case 45: // fmls
        value.YY_MOVE_OR_COPY< SymT > (YY_MOVE (that.value));
        break;

      case 46: // type
        value.YY_MOVE_OR_COPY< Type > (YY_MOVE (that.value));
        break;

      case 37: // NMBR
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 38: // NAME
      case 39: // STRG
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 47: // nest
      case 48: // blck
        value.move< Blck_ptr > (YY_MOVE (that.value));
        break;

      case 44: // defn
        value.move< Defn_ptr > (YY_MOVE (that.value));
        break;

      case 43: // defs
        value.move< Defs > (YY_MOVE (that.value));
        break;

      case 51: // expn
        value.move< Expn_ptr > (YY_MOVE (that.value));
        break;

      case 42: // prgm
        value.move< Prgm_ptr > (YY_MOVE (that.value));
        break;

      case 50: // stmt
        value.move< Stmt_ptr > (YY_MOVE (that.value));
        break;

      case 49: // stms
        value.move< Stmt_vec > (YY_MOVE (that.value));
        break;

      case 45: // fmls
        value.move< SymT > (YY_MOVE (that.value));
        break;

      case 46: // type
        value.move< Type > (YY_MOVE (that.value));
        break;

      case 37: // NMBR
        value.move< int > (YY_MOVE (that.value));
        break;

      case 38: // NAME
      case 39: // STRG
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 47: // nest
      case 48: // blck
        value.copy< Blck_ptr > (that.value);
        break;

      case 44: // defn
        value.copy< Defn_ptr > (that.value);
        break;

      case 43: // defs
        value.copy< Defs > (that.value);
        break;

      case 51: // expn
        value.copy< Expn_ptr > (that.value);
        break;

      case 42: // prgm
        value.copy< Prgm_ptr > (that.value);
        break;

      case 50: // stmt
        value.copy< Stmt_ptr > (that.value);
        break;

      case 49: // stms
        value.copy< Stmt_vec > (that.value);
        break;

      case 45: // fmls
        value.copy< SymT > (that.value);
        break;

      case 46: // type
        value.copy< Type > (that.value);
        break;

      case 37: // NMBR
        value.copy< int > (that.value);
        break;

      case 38: // NAME
      case 39: // STRG
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 47: // nest
      case 48: // blck
        value.move< Blck_ptr > (that.value);
        break;

      case 44: // defn
        value.move< Defn_ptr > (that.value);
        break;

      case 43: // defs
        value.move< Defs > (that.value);
        break;

      case 51: // expn
        value.move< Expn_ptr > (that.value);
        break;

      case 42: // prgm
        value.move< Prgm_ptr > (that.value);
        break;

      case 50: // stmt
        value.move< Stmt_ptr > (that.value);
        break;

      case 49: // stms
        value.move< Stmt_vec > (that.value);
        break;

      case 45: // fmls
        value.move< SymT > (that.value);
        break;

      case 46: // type
        value.move< Type > (that.value);
        break;

      case 37: // NMBR
        value.move< int > (that.value);
        break;

      case 38: // NAME
      case 39: // STRG
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 47: // nest
      case 48: // blck
        yylhs.value.emplace< Blck_ptr > ();
        break;

      case 44: // defn
        yylhs.value.emplace< Defn_ptr > ();
        break;

      case 43: // defs
        yylhs.value.emplace< Defs > ();
        break;

      case 51: // expn
        yylhs.value.emplace< Expn_ptr > ();
        break;

      case 42: // prgm
        yylhs.value.emplace< Prgm_ptr > ();
        break;

      case 50: // stmt
        yylhs.value.emplace< Stmt_ptr > ();
        break;

      case 49: // stms
        yylhs.value.emplace< Stmt_vec > ();
        break;

      case 45: // fmls
        yylhs.value.emplace< SymT > ();
        break;

      case 46: // type
        yylhs.value.emplace< Type > ();
        break;

      case 37: // NMBR
        yylhs.value.emplace< int > ();
        break;

      case 38: // NAME
      case 39: // STRG
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 104 "dwislpy-bison.yy"
       {
      main.set(yystack_[0].value.as < Prgm_ptr > ());
  }
#line 1038 "dwislpy-bison.tab.cc"
    break;

  case 3:
#line 110 "dwislpy-bison.yy"
       {
      Defs ds { };
      Blck_ptr b = yystack_[0].value.as < Blck_ptr > (); 
      yylhs.value.as < Prgm_ptr > () = Prgm_ptr { new Prgm {ds, b, b->where()} };
  }
#line 1048 "dwislpy-bison.tab.cc"
    break;

  case 4:
#line 115 "dwislpy-bison.yy"
            {
      Defs     ds = yystack_[1].value.as < Defs > ();
      Blck_ptr b  = yystack_[0].value.as < Blck_ptr > (); 
      yylhs.value.as < Prgm_ptr > () = Prgm_ptr { new Prgm {ds, b, b->where()} };
  }
#line 1058 "dwislpy-bison.tab.cc"
    break;

  case 5:
#line 122 "dwislpy-bison.yy"
           {
      Defs ds { };
      Defn_ptr d = yystack_[0].value.as < Defn_ptr > ();
      ds[d->name] = d;
      yylhs.value.as < Defs > () = ds;
  }
#line 1069 "dwislpy-bison.tab.cc"
    break;

  case 6:
#line 128 "dwislpy-bison.yy"
            {
      Defs ds = yystack_[1].value.as < Defs > ();
      Defn_ptr d = yystack_[0].value.as < Defn_ptr > ();
      ds[d->name] = d;
      yylhs.value.as < Defs > () = ds;
  }
#line 1080 "dwislpy-bison.tab.cc"
    break;

  case 7:
#line 137 "dwislpy-bison.yy"
                                               {
    SymT ps { };
    yylhs.value.as < Defn_ptr > () = Defn_ptr { new Defn {yystack_[7].value.as < std::string > (), ps, yystack_[3].value.as < Type > (), yystack_[0].value.as < Blck_ptr > (), lexer.locate(yystack_[8].location)} };
  }
#line 1089 "dwislpy-bison.tab.cc"
    break;

  case 8:
#line 141 "dwislpy-bison.yy"
                                     {
    SymT ps { };
    yylhs.value.as < Defn_ptr > () = Defn_ptr { new Defn {yystack_[5].value.as < std::string > (), ps, NoneTy {}, yystack_[0].value.as < Blck_ptr > (), lexer.locate(yystack_[6].location)} };
  }
#line 1098 "dwislpy-bison.tab.cc"
    break;

  case 9:
#line 145 "dwislpy-bison.yy"
                                                    {
    yylhs.value.as < Defn_ptr > () = Defn_ptr { new Defn {yystack_[8].value.as < std::string > (), yystack_[6].value.as < SymT > (), yystack_[3].value.as < Type > (), yystack_[0].value.as < Blck_ptr > (), lexer.locate(yystack_[9].location)} };
  }
#line 1106 "dwislpy-bison.tab.cc"
    break;

  case 10:
#line 148 "dwislpy-bison.yy"
                                          {
    yylhs.value.as < Defn_ptr > () = Defn_ptr { new Defn {yystack_[6].value.as < std::string > (), yystack_[4].value.as < SymT > (), NoneTy {}, yystack_[0].value.as < Blck_ptr > (), lexer.locate(yystack_[7].location)} };
  }
#line 1114 "dwislpy-bison.tab.cc"
    break;

  case 11:
#line 154 "dwislpy-bison.yy"
                 {
    SymT ps { };
    ps.add_frml(yystack_[2].value.as < std::string > (),yystack_[0].value.as < Type > ());
    yylhs.value.as < SymT > () = ps;
  }
#line 1124 "dwislpy-bison.tab.cc"
    break;

  case 12:
#line 159 "dwislpy-bison.yy"
                           {
    SymT ps = yystack_[4].value.as < SymT > ();
    ps.add_frml(yystack_[2].value.as < std::string > (),yystack_[0].value.as < Type > ());
    yylhs.value.as < SymT > () = ps;
  }
#line 1134 "dwislpy-bison.tab.cc"
    break;

  case 13:
#line 167 "dwislpy-bison.yy"
       {
    yylhs.value.as < Type > () = IntTy {};
  }
#line 1142 "dwislpy-bison.tab.cc"
    break;

  case 14:
#line 170 "dwislpy-bison.yy"
       {
    yylhs.value.as < Type > () = StrTy {};
  }
#line 1150 "dwislpy-bison.tab.cc"
    break;

  case 15:
#line 173 "dwislpy-bison.yy"
       {
    yylhs.value.as < Type > () = BoolTy {};
  }
#line 1158 "dwislpy-bison.tab.cc"
    break;

  case 16:
#line 176 "dwislpy-bison.yy"
       {
    yylhs.value.as < Type > () = NoneTy {};
  }
#line 1166 "dwislpy-bison.tab.cc"
    break;

  case 17:
#line 182 "dwislpy-bison.yy"
                 {
    yylhs.value.as < Blck_ptr > () = yystack_[1].value.as < Blck_ptr > ();
  }
#line 1174 "dwislpy-bison.tab.cc"
    break;

  case 18:
#line 188 "dwislpy-bison.yy"
       {
      Stmt_vec ss = yystack_[0].value.as < Stmt_vec > ();
      yylhs.value.as < Blck_ptr > () = Blck_ptr { new Blck {ss, ss[0]->where()} };
  }
#line 1183 "dwislpy-bison.tab.cc"
    break;

  case 19:
#line 195 "dwislpy-bison.yy"
            {
      Stmt_vec ss = yystack_[1].value.as < Stmt_vec > ();
      ss.push_back(yystack_[0].value.as < Stmt_ptr > ());
      yylhs.value.as < Stmt_vec > () = ss;
  }
#line 1193 "dwislpy-bison.tab.cc"
    break;

  case 20:
#line 200 "dwislpy-bison.yy"
       {
      Stmt_vec ss { };
      ss.push_back(yystack_[0].value.as < Stmt_ptr > ());
      yylhs.value.as < Stmt_vec > () = ss;
  }
#line 1203 "dwislpy-bison.tab.cc"
    break;

  case 21:
#line 208 "dwislpy-bison.yy"
                                {
      yylhs.value.as < Stmt_ptr > () = Ntro_ptr { new Ntro {yystack_[5].value.as < std::string > (),yystack_[3].value.as < Type > (),yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[4].location)} };
  }
#line 1211 "dwislpy-bison.tab.cc"
    break;

  case 22:
#line 211 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Stmt_ptr > () = Asgn_ptr { new Asgn {yystack_[3].value.as < std::string > (),yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[2].location)} };
  }
#line 1219 "dwislpy-bison.tab.cc"
    break;

  case 23:
#line 214 "dwislpy-bison.yy"
            {
      yylhs.value.as < Stmt_ptr > () = Pass_ptr { new Pass {lexer.locate(yystack_[1].location)} };
  }
#line 1227 "dwislpy-bison.tab.cc"
    break;

  case 24:
#line 217 "dwislpy-bison.yy"
                           {
      yylhs.value.as < Stmt_ptr > () = Prnt_ptr { new Prnt {yystack_[2].value.as < Expn_ptr > (),lexer.locate(yystack_[4].location)} };
  }
#line 1235 "dwislpy-bison.tab.cc"
    break;

  case 25:
#line 220 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Stmt_ptr > () = FRtn_ptr { new FRtn {yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[2].location)} };
  }
#line 1243 "dwislpy-bison.tab.cc"
    break;

  case 26:
#line 223 "dwislpy-bison.yy"
            {
      yylhs.value.as < Stmt_ptr > () = PRtn_ptr { new PRtn {lexer.locate(yystack_[1].location)} };
  }
#line 1251 "dwislpy-bison.tab.cc"
    break;

  case 27:
#line 229 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Plus_ptr { new Plus {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1259 "dwislpy-bison.tab.cc"
    break;

  case 28:
#line 232 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Less_ptr { new Less {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1267 "dwislpy-bison.tab.cc"
    break;

  case 29:
#line 235 "dwislpy-bison.yy"
                {
      yylhs.value.as < Expn_ptr > () = And_ptr { new And {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1275 "dwislpy-bison.tab.cc"
    break;

  case 30:
#line 238 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {yystack_[0].value.as < int > ()},lexer.locate(yystack_[0].location)} };
  }
#line 1283 "dwislpy-bison.tab.cc"
    break;

  case 31:
#line 241 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {de_escape(yystack_[0].value.as < std::string > ())},lexer.locate(yystack_[0].location)} };
  }
#line 1291 "dwislpy-bison.tab.cc"
    break;

  case 32:
#line 244 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {true},lexer.locate(yystack_[0].location)} };
  }
#line 1299 "dwislpy-bison.tab.cc"
    break;

  case 33:
#line 247 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {false},lexer.locate(yystack_[0].location)} };
  }
#line 1307 "dwislpy-bison.tab.cc"
    break;

  case 34:
#line 250 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {None},lexer.locate(yystack_[0].location)} };
  }
#line 1315 "dwislpy-bison.tab.cc"
    break;

  case 35:
#line 253 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Expn_ptr > () = Inpt_ptr { new Inpt {yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[3].location)} };
  }
#line 1323 "dwislpy-bison.tab.cc"
    break;

  case 36:
#line 256 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Lkup_ptr { new Lkup {yystack_[0].value.as < std::string > (),lexer.locate(yystack_[0].location)} };
  }
#line 1331 "dwislpy-bison.tab.cc"
    break;

  case 37:
#line 259 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = yystack_[1].value.as < Expn_ptr > ();
  }
#line 1339 "dwislpy-bison.tab.cc"
    break;


#line 1343 "dwislpy-bison.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -39;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
       2,     1,    -7,    -6,    -1,    39,    58,   -39,     2,   -39,
     -39,     4,   -39,   -39,    11,    31,   -39,    57,    11,   -39,
     -39,   -39,   -39,   -39,   -39,    41,    11,    42,   -39,   -39,
     -39,   -39,    40,    26,    11,    52,   -39,    11,    11,    11,
      53,   -39,   -39,   -39,   -39,    61,    86,   -17,    59,    -4,
      63,   -39,   -16,   -39,    51,   -39,    11,   -39,    42,    87,
      42,    -2,    55,   -39,    56,    64,    92,   -39,    42,    95,
      66,   -39,    97,     4,   -39,    68,    92,    42,    92,    98,
      99,   -39,   -39,   -39,   -39,    92,   -39
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     2,     0,     5,
       3,    18,    20,    23,     0,     0,    26,     0,     0,    34,
      32,    33,    30,    36,    31,     0,     0,     0,     1,     6,
       4,    19,     0,     0,     0,     0,    25,     0,     0,     0,
       0,    15,    13,    14,    16,     0,     0,     0,     0,     0,
       0,    37,    29,    27,    28,    22,     0,    24,     0,     0,
       0,     0,     0,    35,     0,     0,     0,    11,     0,     0,
       0,    21,     0,     0,     8,     0,     0,     0,     0,     0,
       0,    10,    12,     7,    17,     0,     9
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -39,   -39,   -39,   -39,    96,   -39,   -38,    10,    -8,   -39,
      94,   -13
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     6,     7,     8,     9,    49,    45,    74,    10,    11,
      12,    25
  };

  const signed char
  Parser::yytable_[] =
  {
      30,    32,    16,    58,    13,    35,    38,    17,     1,     2,
       1,     2,    39,    40,     3,     4,    59,     4,    68,    17,
      65,    50,    67,    14,    52,    53,    54,    61,    62,    18,
      75,    69,    15,    19,    20,    21,    22,    23,    24,    82,
       5,    18,     5,    64,    36,    19,    20,    21,    22,    23,
      24,    41,    42,    43,    37,    37,    55,    47,    28,    71,
      26,    33,    38,    38,    48,    79,    37,    37,    39,    39,
      37,    46,    27,    38,    38,    38,    44,    37,    38,    -1,
      39,    39,    56,    51,    39,    38,    81,    34,    83,    57,
      66,    39,    60,    70,    63,    86,    73,    72,    76,    77,
      78,    80,    85,    84,    29,    31
  };

  const signed char
  Parser::yycheck_[] =
  {
       8,    14,     3,    20,     3,    18,    22,     8,     6,     7,
       6,     7,    28,    26,    12,    13,    33,    13,    20,     8,
      58,    34,    60,    30,    37,    38,    39,    31,    32,    30,
      68,    33,    38,    34,    35,    36,    37,    38,    39,    77,
      38,    30,    38,    56,     3,    34,    35,    36,    37,    38,
      39,     9,    10,    11,    14,    14,     3,    31,     0,     3,
      21,    30,    22,    22,    38,    73,    14,    14,    28,    28,
      14,    31,    33,    22,    22,    22,    34,    14,    22,    28,
      28,    28,    21,    31,    28,    22,    76,    30,    78,     3,
       3,    28,    33,    38,    31,    85,     4,    33,     3,    33,
       3,    33,     3,     5,     8,    11
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     6,     7,    12,    13,    38,    41,    42,    43,    44,
      48,    49,    50,     3,    30,    38,     3,     8,    30,    34,
      35,    36,    37,    38,    39,    51,    21,    33,     0,    44,
      48,    50,    51,    30,    30,    51,     3,    14,    22,    28,
      51,     9,    10,    11,    34,    46,    31,    31,    38,    45,
      51,    31,    51,    51,    51,     3,    21,     3,    20,    33,
      33,    31,    32,    31,    51,    46,     3,    46,    20,    33,
      38,     3,    33,     4,    47,    46,     3,    33,     3,    48,
      33,    47,    46,    47,     5,     3,    47
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    40,    41,    42,    42,    43,    43,    44,    44,    44,
      44,    45,    45,    46,    46,    46,    46,    47,    48,    49,
      49,    50,    50,    50,    50,    50,    50,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     1,     2,     9,     7,    10,
       8,     3,     5,     1,     1,     1,     1,     3,     1,     2,
       1,     6,     4,     2,     5,     3,     2,     3,     3,     3,
       1,     1,     1,     1,     1,     4,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "EOFL", "error", "$undefined", "EOLN", "INDT", "DEDT", "\"pass\"",
  "\"print\"", "\"input\"", "\"bool\"", "\"int\"", "\"str\"", "\"def\"",
  "\"return\"", "\"and\"", "\"or\"", "\"not\"", "\"if\"", "\"else\"",
  "\"while\"", "\"->\"", "\"=\"", "\"+\"", "\"-\"", "\"*\"", "\"//\"",
  "\"%\"", "\"<=\"", "\"<\"", "\"==\"", "\"(\"", "\")\"", "\",\"", "\":\"",
  "\"None\"", "\"True\"", "\"False\"", "NMBR", "NAME", "STRG", "$accept",
  "main", "prgm", "defs", "defn", "fmls", "type", "nest", "blck", "stms",
  "stmt", "expn", YY_NULLPTR
  };

#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   104,   104,   110,   115,   122,   128,   137,   141,   145,
     148,   154,   159,   167,   170,   173,   176,   182,   188,   195,
     200,   208,   211,   214,   217,   220,   223,   229,   232,   235,
     238,   241,   244,   247,   250,   253,   256,   259
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
    };
    const int user_token_number_max_ = 294;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

#line 5 "dwislpy-bison.yy"
} // DWISLPY
#line 1832 "dwislpy-bison.tab.cc"

#line 264 "dwislpy-bison.yy"

       
void DWISLPY::Parser::error(const location_type &loc, const std::string &msg) {
    throw DwislpyError { lexer.locate(loc), msg };
}
