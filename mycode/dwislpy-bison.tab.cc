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
      case 51: // blck
        value.move< Blck_ptr > (std::move (that.value));
        break;

      case 50: // defn
        value.move< Defn_ptr > (std::move (that.value));
        break;

      case 49: // defs
        value.move< Defs > (std::move (that.value));
        break;

      case 54: // expn
        value.move< Expn_ptr > (std::move (that.value));
        break;

      case 57: // xpns
        value.move< Expn_vec > (std::move (that.value));
        break;

      case 47: // nest
        value.move< Nest_ptr > (std::move (that.value));
        break;

      case 48: // prgm
        value.move< Prgm_ptr > (std::move (that.value));
        break;

      case 53: // stmt
        value.move< Stmt_ptr > (std::move (that.value));
        break;

      case 52: // stms
        value.move< Stmt_vec > (std::move (that.value));
        break;

      case 55: // nmes
        value.move< SymT > (std::move (that.value));
        break;

      case 56: // type
        value.move< Type > (std::move (that.value));
        break;

      case 41: // NMBR
        value.move< int > (std::move (that.value));
        break;

      case 42: // NAME
      case 43: // STRG
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
      case 51: // blck
        value.copy< Blck_ptr > (YY_MOVE (that.value));
        break;

      case 50: // defn
        value.copy< Defn_ptr > (YY_MOVE (that.value));
        break;

      case 49: // defs
        value.copy< Defs > (YY_MOVE (that.value));
        break;

      case 54: // expn
        value.copy< Expn_ptr > (YY_MOVE (that.value));
        break;

      case 57: // xpns
        value.copy< Expn_vec > (YY_MOVE (that.value));
        break;

      case 47: // nest
        value.copy< Nest_ptr > (YY_MOVE (that.value));
        break;

      case 48: // prgm
        value.copy< Prgm_ptr > (YY_MOVE (that.value));
        break;

      case 53: // stmt
        value.copy< Stmt_ptr > (YY_MOVE (that.value));
        break;

      case 52: // stms
        value.copy< Stmt_vec > (YY_MOVE (that.value));
        break;

      case 55: // nmes
        value.copy< SymT > (YY_MOVE (that.value));
        break;

      case 56: // type
        value.copy< Type > (YY_MOVE (that.value));
        break;

      case 41: // NMBR
        value.copy< int > (YY_MOVE (that.value));
        break;

      case 42: // NAME
      case 43: // STRG
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
      case 51: // blck
        value.move< Blck_ptr > (YY_MOVE (s.value));
        break;

      case 50: // defn
        value.move< Defn_ptr > (YY_MOVE (s.value));
        break;

      case 49: // defs
        value.move< Defs > (YY_MOVE (s.value));
        break;

      case 54: // expn
        value.move< Expn_ptr > (YY_MOVE (s.value));
        break;

      case 57: // xpns
        value.move< Expn_vec > (YY_MOVE (s.value));
        break;

      case 47: // nest
        value.move< Nest_ptr > (YY_MOVE (s.value));
        break;

      case 48: // prgm
        value.move< Prgm_ptr > (YY_MOVE (s.value));
        break;

      case 53: // stmt
        value.move< Stmt_ptr > (YY_MOVE (s.value));
        break;

      case 52: // stms
        value.move< Stmt_vec > (YY_MOVE (s.value));
        break;

      case 55: // nmes
        value.move< SymT > (YY_MOVE (s.value));
        break;

      case 56: // type
        value.move< Type > (YY_MOVE (s.value));
        break;

      case 41: // NMBR
        value.move< int > (YY_MOVE (s.value));
        break;

      case 42: // NAME
      case 43: // STRG
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
      case 51: // blck
        value.YY_MOVE_OR_COPY< Blck_ptr > (YY_MOVE (that.value));
        break;

      case 50: // defn
        value.YY_MOVE_OR_COPY< Defn_ptr > (YY_MOVE (that.value));
        break;

      case 49: // defs
        value.YY_MOVE_OR_COPY< Defs > (YY_MOVE (that.value));
        break;

      case 54: // expn
        value.YY_MOVE_OR_COPY< Expn_ptr > (YY_MOVE (that.value));
        break;

      case 57: // xpns
        value.YY_MOVE_OR_COPY< Expn_vec > (YY_MOVE (that.value));
        break;

      case 47: // nest
        value.YY_MOVE_OR_COPY< Nest_ptr > (YY_MOVE (that.value));
        break;

      case 48: // prgm
        value.YY_MOVE_OR_COPY< Prgm_ptr > (YY_MOVE (that.value));
        break;

      case 53: // stmt
        value.YY_MOVE_OR_COPY< Stmt_ptr > (YY_MOVE (that.value));
        break;

      case 52: // stms
        value.YY_MOVE_OR_COPY< Stmt_vec > (YY_MOVE (that.value));
        break;

      case 55: // nmes
        value.YY_MOVE_OR_COPY< SymT > (YY_MOVE (that.value));
        break;

      case 56: // type
        value.YY_MOVE_OR_COPY< Type > (YY_MOVE (that.value));
        break;

      case 41: // NMBR
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 42: // NAME
      case 43: // STRG
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
      case 51: // blck
        value.move< Blck_ptr > (YY_MOVE (that.value));
        break;

      case 50: // defn
        value.move< Defn_ptr > (YY_MOVE (that.value));
        break;

      case 49: // defs
        value.move< Defs > (YY_MOVE (that.value));
        break;

      case 54: // expn
        value.move< Expn_ptr > (YY_MOVE (that.value));
        break;

      case 57: // xpns
        value.move< Expn_vec > (YY_MOVE (that.value));
        break;

      case 47: // nest
        value.move< Nest_ptr > (YY_MOVE (that.value));
        break;

      case 48: // prgm
        value.move< Prgm_ptr > (YY_MOVE (that.value));
        break;

      case 53: // stmt
        value.move< Stmt_ptr > (YY_MOVE (that.value));
        break;

      case 52: // stms
        value.move< Stmt_vec > (YY_MOVE (that.value));
        break;

      case 55: // nmes
        value.move< SymT > (YY_MOVE (that.value));
        break;

      case 56: // type
        value.move< Type > (YY_MOVE (that.value));
        break;

      case 41: // NMBR
        value.move< int > (YY_MOVE (that.value));
        break;

      case 42: // NAME
      case 43: // STRG
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
      case 51: // blck
        value.copy< Blck_ptr > (that.value);
        break;

      case 50: // defn
        value.copy< Defn_ptr > (that.value);
        break;

      case 49: // defs
        value.copy< Defs > (that.value);
        break;

      case 54: // expn
        value.copy< Expn_ptr > (that.value);
        break;

      case 57: // xpns
        value.copy< Expn_vec > (that.value);
        break;

      case 47: // nest
        value.copy< Nest_ptr > (that.value);
        break;

      case 48: // prgm
        value.copy< Prgm_ptr > (that.value);
        break;

      case 53: // stmt
        value.copy< Stmt_ptr > (that.value);
        break;

      case 52: // stms
        value.copy< Stmt_vec > (that.value);
        break;

      case 55: // nmes
        value.copy< SymT > (that.value);
        break;

      case 56: // type
        value.copy< Type > (that.value);
        break;

      case 41: // NMBR
        value.copy< int > (that.value);
        break;

      case 42: // NAME
      case 43: // STRG
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
      case 51: // blck
        value.move< Blck_ptr > (that.value);
        break;

      case 50: // defn
        value.move< Defn_ptr > (that.value);
        break;

      case 49: // defs
        value.move< Defs > (that.value);
        break;

      case 54: // expn
        value.move< Expn_ptr > (that.value);
        break;

      case 57: // xpns
        value.move< Expn_vec > (that.value);
        break;

      case 47: // nest
        value.move< Nest_ptr > (that.value);
        break;

      case 48: // prgm
        value.move< Prgm_ptr > (that.value);
        break;

      case 53: // stmt
        value.move< Stmt_ptr > (that.value);
        break;

      case 52: // stms
        value.move< Stmt_vec > (that.value);
        break;

      case 55: // nmes
        value.move< SymT > (that.value);
        break;

      case 56: // type
        value.move< Type > (that.value);
        break;

      case 41: // NMBR
        value.move< int > (that.value);
        break;

      case 42: // NAME
      case 43: // STRG
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
      case 51: // blck
        yylhs.value.emplace< Blck_ptr > ();
        break;

      case 50: // defn
        yylhs.value.emplace< Defn_ptr > ();
        break;

      case 49: // defs
        yylhs.value.emplace< Defs > ();
        break;

      case 54: // expn
        yylhs.value.emplace< Expn_ptr > ();
        break;

      case 57: // xpns
        yylhs.value.emplace< Expn_vec > ();
        break;

      case 47: // nest
        yylhs.value.emplace< Nest_ptr > ();
        break;

      case 48: // prgm
        yylhs.value.emplace< Prgm_ptr > ();
        break;

      case 53: // stmt
        yylhs.value.emplace< Stmt_ptr > ();
        break;

      case 52: // stms
        yylhs.value.emplace< Stmt_vec > ();
        break;

      case 55: // nmes
        yylhs.value.emplace< SymT > ();
        break;

      case 56: // type
        yylhs.value.emplace< Type > ();
        break;

      case 41: // NMBR
        yylhs.value.emplace< int > ();
        break;

      case 42: // NAME
      case 43: // STRG
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
#line 113 "dwislpy-bison.yy"
       {
      main.set(yystack_[0].value.as < Prgm_ptr > ());
  }
#line 1094 "dwislpy-bison.tab.cc"
    break;

  case 3:
#line 119 "dwislpy-bison.yy"
                   {
      Defs ds { };
      Blck_ptr b = yystack_[1].value.as < Blck_ptr > (); 
      yylhs.value.as < Nest_ptr > () = Nest_ptr { new Nest {ds, b, b->where()} };
    }
#line 1104 "dwislpy-bison.tab.cc"
    break;

  case 4:
#line 124 "dwislpy-bison.yy"
                     {
      Defs ds { };
      Blck_ptr b = yystack_[1].value.as < Blck_ptr > (); 
      yylhs.value.as < Nest_ptr > () = Nest_ptr { new Nest {ds, b, b->where()} };
    }
#line 1114 "dwislpy-bison.tab.cc"
    break;

  case 5:
#line 132 "dwislpy-bison.yy"
            {
    Defs ds = yystack_[1].value.as < Defs > ();
    Blck_ptr b = yystack_[0].value.as < Blck_ptr > ();
    yylhs.value.as < Prgm_ptr > () = Prgm_ptr { new Prgm {ds, b, b->where()} }; 
  }
#line 1124 "dwislpy-bison.tab.cc"
    break;

  case 6:
#line 137 "dwislpy-bison.yy"
       {
      Defs ds { };
      Blck_ptr b = yystack_[0].value.as < Blck_ptr > (); 
      yylhs.value.as < Prgm_ptr > () = Prgm_ptr { new Prgm {ds, b, b->where()} };
  }
#line 1134 "dwislpy-bison.tab.cc"
    break;

  case 7:
#line 142 "dwislpy-bison.yy"
       {
    Defs ds = yystack_[0].value.as < Defs > ();
    yylhs.value.as < Prgm_ptr > () = Prgm_ptr { new Prgm {ds, Blck_ptr{nullptr}, lexer.locate(yystack_[0].location)} };
  }
#line 1143 "dwislpy-bison.tab.cc"
    break;

  case 8:
#line 149 "dwislpy-bison.yy"
            {
    Defs dd = yystack_[1].value.as < Defs > ();
    dd.push_back(yystack_[0].value.as < Defn_ptr > ());
    yylhs.value.as < Defs > () = dd;
  }
#line 1153 "dwislpy-bison.tab.cc"
    break;

  case 9:
#line 154 "dwislpy-bison.yy"
       {
    Defs dd { };
    dd.push_back(yystack_[0].value.as < Defn_ptr > ());
    yylhs.value.as < Defs > () = dd;
  }
#line 1163 "dwislpy-bison.tab.cc"
    break;

  case 10:
#line 162 "dwislpy-bison.yy"
                                                    {
    yylhs.value.as < Defn_ptr > () = Defn_ptr { new Defn {yystack_[8].value.as < std::string > (), yystack_[6].value.as < SymT > (), yystack_[3].value.as < Type > (), yystack_[0].value.as < Nest_ptr > (), lexer.locate(yystack_[9].location) } };
  }
#line 1171 "dwislpy-bison.tab.cc"
    break;

  case 11:
#line 165 "dwislpy-bison.yy"
                                          {
    yylhs.value.as < Defn_ptr > () = Defn_ptr { new Defn {yystack_[6].value.as < std::string > (), yystack_[4].value.as < SymT > (), NoneTy {}, yystack_[0].value.as < Nest_ptr > (), lexer.locate(yystack_[7].location) } };
  }
#line 1179 "dwislpy-bison.tab.cc"
    break;

  case 12:
#line 171 "dwislpy-bison.yy"
       {
      Stmt_vec ss = yystack_[0].value.as < Stmt_vec > ();
      yylhs.value.as < Blck_ptr > () = Blck_ptr { new Blck {ss, ss[0]->where()} };
  }
#line 1188 "dwislpy-bison.tab.cc"
    break;

  case 13:
#line 178 "dwislpy-bison.yy"
            {
      Stmt_vec ss = yystack_[1].value.as < Stmt_vec > ();
      ss.push_back(yystack_[0].value.as < Stmt_ptr > ());
      yylhs.value.as < Stmt_vec > () = ss;
  }
#line 1198 "dwislpy-bison.tab.cc"
    break;

  case 14:
#line 183 "dwislpy-bison.yy"
       {
      Stmt_vec ss { };
      ss.push_back(yystack_[0].value.as < Stmt_ptr > ());
      yylhs.value.as < Stmt_vec > () = ss;
  }
#line 1208 "dwislpy-bison.tab.cc"
    break;

  case 15:
#line 191 "dwislpy-bison.yy"
                                {
    yylhs.value.as < Stmt_ptr > () = Ntro_ptr { new Ntro { yystack_[5].value.as < std::string > (), yystack_[3].value.as < Type > (), yystack_[1].value.as < Expn_ptr > (), lexer.locate(yystack_[4].location)} };
  }
#line 1216 "dwislpy-bison.tab.cc"
    break;

  case 16:
#line 194 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Stmt_ptr > () = Asgn_ptr { new Asgn {yystack_[3].value.as < std::string > (),yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[2].location)} };
  }
#line 1224 "dwislpy-bison.tab.cc"
    break;

  case 17:
#line 197 "dwislpy-bison.yy"
                                               {
      yylhs.value.as < Stmt_ptr > () = Ifif_ptr { new Ifif {yystack_[7].value.as < Expn_ptr > (), yystack_[4].value.as < Nest_ptr > (), yystack_[0].value.as < Nest_ptr > (), lexer.locate(yystack_[7].location)} };
  }
#line 1232 "dwislpy-bison.tab.cc"
    break;

  case 18:
#line 200 "dwislpy-bison.yy"
                           {
      yylhs.value.as < Stmt_ptr > () = Ifif_ptr { new Ifif {yystack_[3].value.as < Expn_ptr > (), yystack_[0].value.as < Nest_ptr > (), nullptr, lexer.locate(yystack_[3].location)} };
  }
#line 1240 "dwislpy-bison.tab.cc"
    break;

  case 19:
#line 203 "dwislpy-bison.yy"
                                     {
      yylhs.value.as < Stmt_ptr > () = Untl_ptr { new Untl {yystack_[3].value.as < Nest_ptr > (), yystack_[1].value.as < Expn_ptr > (), lexer.locate(yystack_[6].location)} };
  }
#line 1248 "dwislpy-bison.tab.cc"
    break;

  case 20:
#line 206 "dwislpy-bison.yy"
                           {
      yylhs.value.as < Stmt_ptr > () = Whil_ptr { new Whil {yystack_[3].value.as < Expn_ptr > (), yystack_[0].value.as < Nest_ptr > (), lexer.locate(yystack_[3].location)} };
  }
#line 1256 "dwislpy-bison.tab.cc"
    break;

  case 21:
#line 209 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Stmt_ptr > () = PlEq_ptr { new PlEq {yystack_[3].value.as < std::string > (), yystack_[1].value.as < Expn_ptr > (), lexer.locate(yystack_[2].location)} };
  }
#line 1264 "dwislpy-bison.tab.cc"
    break;

  case 22:
#line 212 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Stmt_ptr > () = MnEq_ptr { new MnEq {yystack_[3].value.as < std::string > (), yystack_[1].value.as < Expn_ptr > (), lexer.locate(yystack_[2].location)} };
  }
#line 1272 "dwislpy-bison.tab.cc"
    break;

  case 23:
#line 215 "dwislpy-bison.yy"
            {
      yylhs.value.as < Stmt_ptr > () = Pass_ptr { new Pass {lexer.locate(yystack_[1].location)} };
  }
#line 1280 "dwislpy-bison.tab.cc"
    break;

  case 24:
#line 218 "dwislpy-bison.yy"
                           {
      yylhs.value.as < Stmt_ptr > () = Prnt_ptr { new Prnt {yystack_[2].value.as < Expn_vec > (),lexer.locate(yystack_[4].location)} };
  }
#line 1288 "dwislpy-bison.tab.cc"
    break;

  case 25:
#line 221 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Stmt_ptr > () = Rtrn_ptr { new Rtrn {yystack_[1].value.as < Expn_ptr > (), lexer.locate(yystack_[2].location)} };
  }
#line 1296 "dwislpy-bison.tab.cc"
    break;

  case 26:
#line 224 "dwislpy-bison.yy"
            {
      yylhs.value.as < Stmt_ptr > () = Rtrn_ptr { new Rtrn {Expn_ptr{nullptr}, lexer.locate(yystack_[1].location)} };
  }
#line 1304 "dwislpy-bison.tab.cc"
    break;

  case 27:
#line 227 "dwislpy-bison.yy"
                           {
      yylhs.value.as < Stmt_ptr > () = Proc_ptr { new Proc {yystack_[4].value.as < std::string > (), yystack_[2].value.as < Expn_vec > (), lexer.locate(yystack_[4].location)} };
  }
#line 1312 "dwislpy-bison.tab.cc"
    break;

  case 28:
#line 233 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Expn_ptr > () = Func_ptr { new Func {yystack_[3].value.as < std::string > (), yystack_[1].value.as < Expn_vec > (), lexer.locate(yystack_[3].location)} };
  }
#line 1320 "dwislpy-bison.tab.cc"
    break;

  case 29:
#line 236 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Conj_ptr { new Conj {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1328 "dwislpy-bison.tab.cc"
    break;

  case 30:
#line 239 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Disj_ptr { new Disj {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1336 "dwislpy-bison.tab.cc"
    break;

  case 31:
#line 242 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Less_ptr { new Less {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1344 "dwislpy-bison.tab.cc"
    break;

  case 32:
#line 245 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = LsEq_ptr { new LsEq {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1352 "dwislpy-bison.tab.cc"
    break;

  case 33:
#line 248 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Equl_ptr { new Equl {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1360 "dwislpy-bison.tab.cc"
    break;

  case 34:
#line 251 "dwislpy-bison.yy"
            {
      yylhs.value.as < Expn_ptr > () = LNot_ptr { new LNot {yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[0].location)} };
  }
#line 1368 "dwislpy-bison.tab.cc"
    break;

  case 35:
#line 254 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Plus_ptr { new Plus {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1376 "dwislpy-bison.tab.cc"
    break;

  case 36:
#line 257 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Mnus_ptr { new Mnus {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1384 "dwislpy-bison.tab.cc"
    break;

  case 37:
#line 260 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = Tmes_ptr { new Tmes {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1392 "dwislpy-bison.tab.cc"
    break;

  case 38:
#line 263 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = IDiv_ptr { new IDiv {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1400 "dwislpy-bison.tab.cc"
    break;

  case 39:
#line 266 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = IMod_ptr { new IMod {yystack_[2].value.as < Expn_ptr > (),yystack_[0].value.as < Expn_ptr > (),lexer.locate(yystack_[1].location)} };
  }
#line 1408 "dwislpy-bison.tab.cc"
    break;

  case 40:
#line 269 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {yystack_[0].value.as < int > ()}, IntTy{}, lexer.locate(yystack_[0].location)} };
  }
#line 1416 "dwislpy-bison.tab.cc"
    break;

  case 41:
#line 272 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {de_escape(yystack_[0].value.as < std::string > ())}, StrTy{}, lexer.locate(yystack_[0].location)} };
  }
#line 1424 "dwislpy-bison.tab.cc"
    break;

  case 42:
#line 275 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {true}, BoolTy{}, lexer.locate(yystack_[0].location)} };
  }
#line 1432 "dwislpy-bison.tab.cc"
    break;

  case 43:
#line 278 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {false}, BoolTy{}, lexer.locate(yystack_[0].location)} };
  }
#line 1440 "dwislpy-bison.tab.cc"
    break;

  case 44:
#line 281 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Ltrl_ptr { new Ltrl {Valu {None}, NoneTy{}, lexer.locate(yystack_[0].location)} };
  }
#line 1448 "dwislpy-bison.tab.cc"
    break;

  case 45:
#line 284 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Expn_ptr > () = Inpt_ptr { new Inpt {yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[3].location)} };
  }
#line 1456 "dwislpy-bison.tab.cc"
    break;

  case 46:
#line 287 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Expn_ptr > () = IntC_ptr { new IntC {yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[3].location)} };
  }
#line 1464 "dwislpy-bison.tab.cc"
    break;

  case 47:
#line 290 "dwislpy-bison.yy"
                      {
      yylhs.value.as < Expn_ptr > () = StrC_ptr { new StrC {yystack_[1].value.as < Expn_ptr > (),lexer.locate(yystack_[3].location)} };
  }
#line 1472 "dwislpy-bison.tab.cc"
    break;

  case 48:
#line 293 "dwislpy-bison.yy"
       {
      yylhs.value.as < Expn_ptr > () = Lkup_ptr { new Lkup {yystack_[0].value.as < std::string > (),lexer.locate(yystack_[0].location)} };
  }
#line 1480 "dwislpy-bison.tab.cc"
    break;

  case 49:
#line 296 "dwislpy-bison.yy"
                 {
      yylhs.value.as < Expn_ptr > () = yystack_[1].value.as < Expn_ptr > ();
  }
#line 1488 "dwislpy-bison.tab.cc"
    break;

  case 50:
#line 302 "dwislpy-bison.yy"
                           {
    SymT st = yystack_[4].value.as < SymT > ();
    st.add_frml(yystack_[2].value.as < std::string > (),yystack_[0].value.as < Type > ()); 
    yylhs.value.as < SymT > () = st; 
  }
#line 1498 "dwislpy-bison.tab.cc"
    break;

  case 51:
#line 307 "dwislpy-bison.yy"
                 {
    SymT st = { };
    st.add_frml(yystack_[2].value.as < std::string > (),yystack_[0].value.as < Type > ());
    yylhs.value.as < SymT > () = st;
  }
#line 1508 "dwislpy-bison.tab.cc"
    break;

  case 52:
#line 312 "dwislpy-bison.yy"
  {
    SymT st = { };
    yylhs.value.as < SymT > () = st;
  }
#line 1517 "dwislpy-bison.tab.cc"
    break;

  case 53:
#line 319 "dwislpy-bison.yy"
       { yylhs.value.as < Type > () = IntTy {}; }
#line 1523 "dwislpy-bison.tab.cc"
    break;

  case 54:
#line 320 "dwislpy-bison.yy"
       { yylhs.value.as < Type > () = StrTy {}; }
#line 1529 "dwislpy-bison.tab.cc"
    break;

  case 55:
#line 321 "dwislpy-bison.yy"
       { yylhs.value.as < Type > () = BoolTy {}; }
#line 1535 "dwislpy-bison.tab.cc"
    break;

  case 56:
#line 322 "dwislpy-bison.yy"
       { yylhs.value.as < Type > () = NoneTy {}; }
#line 1541 "dwislpy-bison.tab.cc"
    break;

  case 57:
#line 328 "dwislpy-bison.yy"
                 {
    Expn_vec ee = yystack_[2].value.as < Expn_vec > ();
    ee.push_back(yystack_[0].value.as < Expn_ptr > ()); 
    yylhs.value.as < Expn_vec > () = ee; 
  }
#line 1551 "dwislpy-bison.tab.cc"
    break;

  case 58:
#line 333 "dwislpy-bison.yy"
       {
    Expn_vec ee = { };
    ee.push_back(yystack_[0].value.as < Expn_ptr > ());
    yylhs.value.as < Expn_vec > () = ee;
  }
#line 1561 "dwislpy-bison.tab.cc"
    break;

  case 59:
#line 338 "dwislpy-bison.yy"
  {
    Expn_vec ee = { };
    yylhs.value.as < Expn_vec > () = ee;
  }
#line 1570 "dwislpy-bison.tab.cc"
    break;


#line 1574 "dwislpy-bison.tab.cc"

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


  const signed char Parser::yypact_ninf_ = -73;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
      -1,     8,   -23,    98,   -16,    98,    62,   -14,    33,    35,
     -73,    -1,   -73,   -73,    68,   -73,   -73,    98,     4,     6,
      28,    98,    98,   -73,   -73,   -73,   -73,    31,   -73,   254,
      34,   274,   -73,   111,    32,    98,    98,    98,    -2,    98,
     -73,   -73,   -73,   -73,   279,   -17,    98,    98,    98,   279,
     187,    98,    98,    98,    98,    98,    98,    73,    98,    98,
      98,    98,    98,    77,    79,   -73,    43,   132,   152,   157,
     -73,   -73,   -73,   -73,    74,     1,    98,    83,   217,   224,
     246,   -73,     2,   304,   299,   304,   304,   304,    77,    45,
      45,   -73,   -73,   -73,    68,    64,    77,    61,    25,   -73,
     -73,   -73,    98,    93,   279,   -73,   -73,   -73,   -73,   -73,
      88,    10,    98,   -73,    -2,    55,    -8,   177,   -73,    82,
     -73,   -73,   197,   -73,    85,    -2,   110,   -73,   113,   -73,
      -2,    87,    77,    77,   -73,   115,   -73,   -73,    77,   -73
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     7,     9,     6,    12,    14,    23,    59,     0,     0,
       0,     0,     0,    44,    42,    43,    40,    48,    41,     0,
       0,     0,    26,     0,     0,     0,     0,     0,     0,    59,
       1,     8,     5,    13,    58,     0,     0,     0,     0,    34,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    25,    52,     0,     0,     0,
      53,    54,    55,    56,     0,     0,     0,     0,     0,     0,
       0,    49,     0,    29,    30,    31,    32,    33,     0,    35,
      36,    37,    38,    39,     0,     0,     0,     0,     0,    16,
      21,    22,     0,     0,    57,    24,    45,    46,    47,    28,
      18,     0,     0,    20,     0,     0,     0,     0,    27,     0,
       4,     3,     0,    51,     0,     0,     0,    15,     0,    19,
       0,     0,     0,     0,    50,     0,    11,    17,     0,    10
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -73,   -73,   -72,   -73,   -73,   109,   -10,   -73,   107,    -3,
     -73,   -37,   -22
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     9,    95,    10,    11,    12,    13,    14,    15,    44,
      98,    74,    45
  };

  const unsigned char
  Parser::yytable_[] =
  {
      29,    42,    31,    33,   125,     1,     2,    70,    71,    72,
     120,    16,    76,    17,    30,   121,   110,    75,    49,    50,
      77,     3,   126,     4,   113,     5,     6,     7,    34,    82,
      76,    76,    67,    68,    69,    40,    73,    63,   103,   109,
      46,     8,    47,    78,    79,    80,    35,    36,    37,    83,
      84,    85,    86,    87,   115,    89,    90,    91,    92,    93,
     136,   137,   116,    38,    48,    32,   139,    51,    66,    39,
      18,    19,    20,   104,     1,     2,    88,   123,    60,    61,
      62,    94,    96,    21,   111,    97,   105,   102,   131,   112,
       3,   114,     4,   134,     5,     6,   118,   124,    22,   117,
      23,    24,    25,    26,    27,    28,    18,    19,    20,   122,
       8,   119,   128,   132,    65,   130,   133,   135,   138,    21,
      41,    43,     0,     0,     0,     0,     0,    52,    53,    54,
      55,    56,     0,     0,    22,    99,    23,    24,    25,    26,
      27,    28,    58,    59,    60,    61,    62,     0,    52,    53,
      54,    55,    56,     0,     0,   100,     0,     0,     0,     0,
     101,     0,     0,    58,    59,    60,    61,    62,    52,    53,
      54,    55,    56,    52,    53,    54,    55,    56,     0,     0,
     127,     0,     0,    58,    59,    60,    61,    62,    58,    59,
      60,    61,    62,    52,    53,    54,    55,    56,     0,     0,
     129,     0,     0,    52,    53,    54,    55,    56,    58,    59,
      60,    61,    62,    52,    53,    54,    55,    56,    58,    59,
      60,    61,    62,     0,    81,     0,     0,     0,    58,    59,
      60,    61,    62,    52,    53,    54,    55,    56,     0,     0,
      52,    53,    54,    55,    56,     0,     0,     0,    58,    59,
      60,    61,    62,     0,   106,    58,    59,    60,    61,    62,
       0,   107,    52,    53,    54,    55,    56,     0,     0,     0,
      52,    53,    54,    55,    56,     0,     0,    58,    59,    60,
      61,    62,     0,   108,    57,    58,    59,    60,    61,    62,
      52,    53,    54,    55,    56,    52,    53,    54,    55,    56,
       0,     0,     0,     0,    64,    58,    59,    60,    61,    62,
      58,    59,    60,    61,    62,    52,     0,    54,    55,    56,
       0,     0,    54,    55,    56,     0,     0,     0,     0,     0,
      58,    59,    60,    61,    62,    58,    59,    60,    61,    62
  };

  const short
  Parser::yycheck_[] =
  {
       3,    11,     5,     6,    12,     6,     7,     9,    10,    11,
       0,     3,    29,    36,    30,     5,    88,    39,    21,    22,
      37,    22,    30,    24,    96,    26,    27,    28,    42,    51,
      29,    29,    35,    36,    37,     0,    38,     3,    37,    37,
      36,    42,    36,    46,    47,    48,    13,    14,    15,    52,
      53,    54,    55,    56,    29,    58,    59,    60,    61,    62,
     132,   133,    37,    30,    36,     3,   138,    36,    36,    36,
       8,     9,    10,    76,     6,     7,     3,   114,    33,    34,
      35,     4,     3,    21,    94,    42,     3,    13,   125,    25,
      22,    30,    24,   130,    26,    27,     3,    42,    36,   102,
      38,    39,    40,    41,    42,    43,     8,     9,    10,   112,
      42,    23,    30,     3,     3,    30,     3,    30,     3,    21,
      11,    14,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,
      19,    20,    -1,    -1,    36,     3,    38,    39,    40,    41,
      42,    43,    31,    32,    33,    34,    35,    -1,    16,    17,
      18,    19,    20,    -1,    -1,     3,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    31,    32,    33,    34,    35,    16,    17,
      18,    19,    20,    16,    17,    18,    19,    20,    -1,    -1,
       3,    -1,    -1,    31,    32,    33,    34,    35,    31,    32,
      33,    34,    35,    16,    17,    18,    19,    20,    -1,    -1,
       3,    -1,    -1,    16,    17,    18,    19,    20,    31,    32,
      33,    34,    35,    16,    17,    18,    19,    20,    31,    32,
      33,    34,    35,    -1,    37,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    16,    17,    18,    19,    20,    -1,    -1,
      16,    17,    18,    19,    20,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    -1,    37,    31,    32,    33,    34,    35,
      -1,    37,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      16,    17,    18,    19,    20,    -1,    -1,    31,    32,    33,
      34,    35,    -1,    37,    30,    31,    32,    33,    34,    35,
      16,    17,    18,    19,    20,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      31,    32,    33,    34,    35,    16,    -1,    18,    19,    20,
      -1,    -1,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    35,    31,    32,    33,    34,    35
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     6,     7,    22,    24,    26,    27,    28,    42,    46,
      48,    49,    50,    51,    52,    53,     3,    36,     8,     9,
      10,    21,    36,    38,    39,    40,    41,    42,    43,    54,
      30,    54,     3,    54,    42,    13,    14,    15,    30,    36,
       0,    50,    51,    53,    54,    57,    36,    36,    36,    54,
      54,    36,    16,    17,    18,    19,    20,    30,    31,    32,
      33,    34,    35,     3,    30,     3,    36,    54,    54,    54,
       9,    10,    11,    38,    56,    57,    29,    37,    54,    54,
      54,    37,    57,    54,    54,    54,    54,    54,     3,    54,
      54,    54,    54,    54,     4,    47,     3,    42,    55,     3,
       3,     3,    13,    37,    54,     3,    37,    37,    37,    37,
      47,    51,    25,    47,    30,    29,    37,    54,     3,    23,
       0,     5,    54,    56,    42,    12,    30,     3,    30,     3,
      30,    56,     3,     3,    56,    30,    47,    47,     3,    47
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    45,    46,    47,    47,    48,    48,    48,    49,    49,
      50,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    56,    56,    56,    56,    57,    57,    57
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     3,     3,     2,     1,     1,     2,     1,
      10,     8,     1,     2,     1,     6,     4,     9,     5,     7,
       5,     4,     4,     2,     5,     3,     2,     5,     4,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     4,     4,     4,     1,     3,
       5,     3,     0,     1,     1,     1,     1,     3,     1,     0
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "EOFL", "error", "$undefined", "EOLN", "INDT", "DEDT", "\"pass\"",
  "\"print\"", "\"input\"", "\"int\"", "\"str\"", "\"bool\"", "\"->\"",
  "\"=\"", "\"+=\"", "\"-=\"", "\"and\"", "\"or\"", "\"<\"", "\"<=\"",
  "\"==\"", "\"not\"", "\"if\"", "\"else\"", "\"repeat\"", "\"until\"",
  "\"while\"", "\"return\"", "\"def\"", "\",\"", "\":\"", "\"+\"", "\"-\"",
  "\"*\"", "\"//\"", "\"%\"", "\"(\"", "\")\"", "\"None\"", "\"True\"",
  "\"False\"", "NMBR", "NAME", "STRG", "NOT", "$accept", "main", "nest",
  "prgm", "defs", "defn", "blck", "stms", "stmt", "expn", "nmes", "type",
  "xpns", YY_NULLPTR
  };

#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   113,   113,   119,   124,   132,   137,   142,   149,   154,
     162,   165,   171,   178,   183,   191,   194,   197,   200,   203,
     206,   209,   212,   215,   218,   221,   224,   227,   233,   236,
     239,   242,   245,   248,   251,   254,   257,   260,   263,   266,
     269,   272,   275,   278,   281,   284,   287,   290,   293,   296,
     302,   307,   312,   319,   320,   321,   322,   328,   333,   338
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
    };
    const int user_token_number_max_ = 299;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

#line 5 "dwislpy-bison.yy"
} // DWISLPY
#line 2131 "dwislpy-bison.tab.cc"

#line 344 "dwislpy-bison.yy"

       
void DWISLPY::Parser::error(const location_type &loc, const std::string &msg) {
    std::cout<<"over there"<<std::endl;
    throw DwislpyError { lexer.locate(loc), msg };
}
