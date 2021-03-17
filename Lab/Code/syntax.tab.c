/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "./syntax.y" /* yacc.c:339  */

    #include "extern.h"
    #include "treeNode.h"
    // int yydebug = 1;
    int syntaxError = 0;
    void missing(char* c)
    {
        printf("missing %s",c);
    }
    void fault(int _id)
    {
        printf("    fault id:%d\n",_id);
    }

    void my_yyerror(char* msg) {
        printf("Error type B at Line %d: syntax error: %s.\n", yylineno, msg);
    }

#line 85 "./syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    ID = 260,
    SEMI = 261,
    COMMA = 262,
    ASSIGNOP = 263,
    RELOP = 264,
    PLUS = 265,
    MINUS = 266,
    STAR = 267,
    DIV = 268,
    AND = 269,
    OR = 270,
    DOT = 271,
    NOT = 272,
    TYPE = 273,
    LP = 274,
    RP = 275,
    LB = 276,
    RB = 277,
    LC = 278,
    RC = 279,
    STRUCT = 280,
    RETURN = 281,
    IF = 282,
    ELSE = 283,
    WHILE = 284,
    NEG = 285,
    LOWER_THAN_ELSE = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "./syntax.y" /* yacc.c:355  */

    node type_node;

#line 161 "./syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 192 "./syntax.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   585

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,   101,   108,   112,   116,   123,   127,   131,
     135,   139,   143,   149,   153,   159,   163,   167,   175,   179,
     183,   186,   192,   196,   202,   206,   211,   215,   219,   225,
     229,   233,   237,   241,   245,   251,   255,   259,   263,   270,
     274,   281,   286,   290,   294,   298,   306,   310,   316,   320,
     324,   328,   332,   336,   340,   344,   348,   352,   356,   360,
     364,   368,   372,   376,   380,   384,   388,   394,   398,   404,
     408,   412,   418,   422,   429,   433,   440,   444,   448,   452,
     456,   460,   464,   468,   472,   476,   480,   484,   488,   492,
     496,   500,   504,   508,   512,   516,   520,   524,   528,   532,
     536,   540,   544,   548,   552,   556,   560,   566,   570
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "DOT",
  "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "NEG", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

#define YYPACT_NINF -65

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-65)))

#define YYTABLE_NINF -69

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      78,    11,   -65,    60,    18,   -65,   105,    70,   -65,   -65,
     -65,    64,   -65,   186,    12,   -65,   -65,    19,   -65,    41,
      80,   -65,   133,    91,    63,   -65,    14,    14,   -65,   132,
     159,   -65,   120,   101,   126,    90,   153,   -65,   117,   144,
     113,     6,   119,   -65,   120,   136,   131,   158,   -65,     8,
     -65,   -65,   142,   165,   129,   117,   160,    89,    21,   173,
     180,   -65,   -65,   174,   280,   297,   302,   319,   110,   182,
     -65,   178,   117,   198,   -65,   -65,   -65,   -65,   184,   -65,
      44,    44,   -65,   -65,   -65,   -65,   -65,   -65,    22,   -65,
     438,   -65,   -65,   120,   -65,   275,   -65,    56,   -65,    56,
     183,   480,   210,   214,   438,   324,   438,   341,   -65,   -65,
     211,   -65,   346,   363,   368,   385,   390,   407,   412,   429,
     213,   434,   -65,   -65,   -65,   -65,   522,   -65,   201,   -65,
     451,   212,   -65,   -65,   -65,   -65,   -65,   494,   216,   230,
     508,   217,   246,   -65,   -65,   522,   -65,   564,   -65,   529,
     -65,   529,   -65,    56,   -65,    56,   -65,   557,   -65,   544,
     -65,   226,   465,   -65,   438,   -65,   171,   171,   171,   171,
     171,   171,   171,   171,   -65,   -65,   -65,   -65,   -65,   -65,
     205,   -65,   -65,   -65,   -65,   171,   -65
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    15,     0,     0,     2,     0,     0,    16,    17,
      10,     0,    25,    22,     0,    19,     1,     0,     4,     0,
      26,     8,     0,    13,     0,    12,     0,     0,    11,     0,
       0,     7,     0,     0,    45,     0,     0,     9,     0,     0,
       0,     0,    38,    34,     0,     0,     0,    17,    30,     0,
      26,    14,     0,     0,    17,     0,     0,    74,     0,    72,
      45,    92,    93,    91,     0,     0,     0,     0,     0,     0,
      49,     0,     0,     0,    67,    21,    20,    18,    39,    33,
       0,     0,    32,    31,    29,    28,    27,    43,     0,    70,
       0,    71,    69,     0,    63,     0,   103,    85,   104,    86,
       0,     0,    56,     0,     0,     0,     0,     0,    44,    46,
      54,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,    35,    42,    41,    75,    73,     0,    88,
     108,     0,   102,    84,    66,    55,    50,     0,     0,     0,
       0,     0,     0,    64,    94,    76,    97,    79,    98,    80,
      99,    81,   100,    82,   101,    83,    95,    77,    96,    78,
      90,     0,     0,   105,     0,    87,     0,     0,     0,     0,
       0,     0,     0,     0,   106,    89,   107,    59,    58,    57,
      51,    62,    61,    60,    53,     0,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -65,   -65,   228,   -65,   220,     4,   -65,   -65,   -65,   -30,
     -65,   -22,   -65,   225,     1,   102,   513,   -65,   170,   -65,
     -64,   100
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    22,    36,     8,    14,    15,    23,
      24,    45,    46,    70,    71,    72,    38,    39,    58,    59,
      73,   131
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      97,    99,   101,   103,     7,    11,    57,    76,    49,    83,
       7,    -3,     9,    26,    78,     9,   -17,    10,    16,    -6,
       9,    11,    91,   124,   -17,    10,   126,    92,    84,     2,
      77,   130,     2,    44,    44,    27,     3,     2,   -68,     3,
     137,   139,   140,   142,     3,    42,   125,    28,   145,   147,
     149,   151,   153,   155,   157,   159,    88,   162,   122,   123,
      29,    12,     2,    57,    34,    13,   -68,   -68,   -68,     3,
      25,    19,   120,   109,   -68,    20,    21,   121,    -5,     1,
     -68,     2,   -68,   -23,    44,    44,    35,   -68,     3,   -68,
     -68,    54,   -68,   -68,   -68,   -68,     2,    90,    32,    30,
     130,   -68,    52,     3,    53,    -5,    17,   -68,     2,   -68,
      33,   104,    33,   -68,   -68,     3,   -68,   -68,    60,   -68,
      61,    62,    63,     2,   -17,    50,   -40,   -17,    64,   105,
       3,   -17,    80,    42,    65,     2,    66,    75,    81,    31,
      35,   -47,     3,    67,    68,     9,    69,   -68,   -68,   -68,
       2,   -36,    43,    87,    56,   -68,    79,     3,    50,   -38,
      47,   -68,     2,   -68,    85,   -40,    89,   -68,   -68,     3,
     -68,   -68,    60,   -68,    61,    62,    63,     2,    82,    48,
      93,   -17,    64,   106,     3,   -17,    94,    86,    65,     2,
      66,   -24,   -24,    95,    35,   -68,     3,    67,    68,   110,
      69,   107,   108,   132,   111,    33,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   135,   134,   143,   160,   121,
     136,   163,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   168,   165,   185,    18,   121,   167,   171,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   172,   174,    37,
     169,   121,    51,     0,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   127,   176,     0,   173,   121,   177,   178,
     179,   180,   181,   182,   183,   184,   128,     0,    61,    62,
      63,    96,     0,    61,    62,    63,    64,   186,     0,     0,
       0,    64,    65,     0,    66,   129,     0,    65,    98,    66,
      61,    62,    63,   100,     0,    61,    62,    63,    64,     0,
       0,     0,     0,    64,    65,     0,    66,     0,     0,    65,
     102,    66,    61,    62,    63,   138,     0,    61,    62,    63,
      64,     0,     0,     0,     0,    64,    65,     0,    66,     0,
       0,    65,   141,    66,    61,    62,    63,   144,     0,    61,
      62,    63,    64,     0,     0,     0,     0,    64,    65,     0,
      66,     0,     0,    65,   146,    66,    61,    62,    63,   148,
       0,    61,    62,    63,    64,     0,     0,     0,     0,    64,
      65,     0,    66,     0,     0,    65,   150,    66,    61,    62,
      63,   152,     0,    61,    62,    63,    64,     0,     0,     0,
       0,    64,    65,     0,    66,     0,     0,    65,   154,    66,
      61,    62,    63,   156,     0,    61,    62,    63,    64,     0,
       0,     0,     0,    64,    65,     0,    66,     0,     0,    65,
     158,    66,    61,    62,    63,   161,     0,    61,    62,    63,
      64,    61,    62,    63,     0,    64,    65,     0,    66,    64,
       0,    65,     0,    66,     0,    65,     0,    66,   164,   112,
     113,   114,   115,   116,   117,   118,   119,   120,     0,     0,
       0,     0,   121,   112,   113,   114,   115,   116,   117,   118,
     119,   120,     0,     0,     0,     0,   121,   175,   112,   113,
     114,   115,   116,   117,   118,   119,   120,     0,     0,     0,
     133,   121,   112,   113,   114,   115,   116,   117,   118,   119,
     120,     0,     0,     0,   166,   121,   112,   113,   114,   115,
     116,   117,   118,   119,   120,     0,     0,     0,   170,   121,
     112,   113,   114,   115,   116,   117,   118,   119,   120,    40,
      41,   116,   117,   121,     0,   120,     0,     0,    55,     0,
     121,     0,    74,   113,   114,   115,   116,   117,   118,     0,
     120,     0,     0,     0,     0,   121,   113,   114,   115,   116,
     117,     0,     0,   120,   114,   115,   116,   117,   121,     0,
     120,     0,     0,     0,     0,   121
};

static const yytype_int16 yycheck[] =
{
      64,    65,    66,    67,     0,     1,    36,     1,    30,     1,
       6,     0,     1,     1,    44,     1,     5,     6,     0,     0,
       1,    17,     1,     1,     5,     6,    90,     6,    20,    18,
      24,    95,    18,    29,    30,    23,    25,    18,    24,    25,
     104,   105,   106,   107,    25,     1,    24,     6,   112,   113,
     114,   115,   116,   117,   118,   119,    55,   121,    80,    81,
      19,     1,    18,    93,     1,     5,     3,     4,     5,    25,
       6,     1,    16,    72,    11,     5,     6,    21,     0,     1,
      17,    18,    19,    23,    80,    81,    23,    24,    25,    26,
      27,     1,    29,     3,     4,     5,    18,     8,     7,    19,
     164,    11,     1,    25,     3,     0,     1,    17,    18,    19,
      21,     1,    21,    23,    24,    25,    26,    27,     1,    29,
       3,     4,     5,    18,     5,     5,     7,     1,    11,    19,
      25,     5,     1,     1,    17,    18,    19,    24,     7,     6,
      23,    24,    25,    26,    27,     1,    29,     3,     4,     5,
      18,    20,    20,    24,     1,    11,    20,    25,     5,     1,
       1,    17,    18,    19,    22,     7,     6,    23,    24,    25,
      26,    27,     1,    29,     3,     4,     5,    18,    20,    20,
       7,     1,    11,     1,    25,     5,     6,    22,    17,    18,
      19,     5,     6,    19,    23,    24,    25,    26,    27,     1,
      29,    19,    24,    20,     6,    21,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     1,     6,     6,     5,    21,
       6,    20,     8,     9,    10,    11,    12,    13,    14,    15,
      16,     1,    20,    28,     6,    21,    20,    20,     8,     9,
      10,    11,    12,    13,    14,    15,    16,     1,    22,    24,
      20,    21,    32,    -1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    93,   164,    -1,    20,    21,   166,   167,
     168,   169,   170,   171,   172,   173,     1,    -1,     3,     4,
       5,     1,    -1,     3,     4,     5,    11,   185,    -1,    -1,
      -1,    11,    17,    -1,    19,    20,    -1,    17,     1,    19,
       3,     4,     5,     1,    -1,     3,     4,     5,    11,    -1,
      -1,    -1,    -1,    11,    17,    -1,    19,    -1,    -1,    17,
       1,    19,     3,     4,     5,     1,    -1,     3,     4,     5,
      11,    -1,    -1,    -1,    -1,    11,    17,    -1,    19,    -1,
      -1,    17,     1,    19,     3,     4,     5,     1,    -1,     3,
       4,     5,    11,    -1,    -1,    -1,    -1,    11,    17,    -1,
      19,    -1,    -1,    17,     1,    19,     3,     4,     5,     1,
      -1,     3,     4,     5,    11,    -1,    -1,    -1,    -1,    11,
      17,    -1,    19,    -1,    -1,    17,     1,    19,     3,     4,
       5,     1,    -1,     3,     4,     5,    11,    -1,    -1,    -1,
      -1,    11,    17,    -1,    19,    -1,    -1,    17,     1,    19,
       3,     4,     5,     1,    -1,     3,     4,     5,    11,    -1,
      -1,    -1,    -1,    11,    17,    -1,    19,    -1,    -1,    17,
       1,    19,     3,     4,     5,     1,    -1,     3,     4,     5,
      11,     3,     4,     5,    -1,    11,    17,    -1,    19,    11,
      -1,    17,    -1,    19,    -1,    17,    -1,    19,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    21,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    21,    22,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    21,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    20,    21,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    20,    21,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    26,
      27,    12,    13,    21,    -1,    16,    -1,    -1,    35,    -1,
      21,    -1,    39,     9,    10,    11,    12,    13,    14,    -1,
      16,    -1,    -1,    -1,    -1,    21,     9,    10,    11,    12,
      13,    -1,    -1,    16,    10,    11,    12,    13,    21,    -1,
      16,    -1,    -1,    -1,    -1,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    18,    25,    33,    34,    35,    37,    38,     1,
       6,    37,     1,     5,    39,    40,     0,     1,    34,     1,
       5,     6,    36,    41,    42,     6,     1,    23,     6,    19,
      19,     6,     7,    21,     1,    23,    37,    45,    48,    49,
      48,    48,     1,    20,    37,    43,    44,     1,    20,    43,
       5,    36,     1,     3,     1,    48,     1,    41,    50,    51,
       1,     3,     4,     5,    11,    17,    19,    26,    27,    29,
      45,    46,    47,    52,    48,    24,     1,    24,    41,    20,
       1,     7,    20,     1,    20,    22,    22,    24,    46,     6,
       8,     1,     6,     7,     6,    19,     1,    52,     1,    52,
       1,    52,     1,    52,     1,    19,     1,    19,    24,    46,
       1,     6,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    21,    43,    43,     1,    24,    52,    50,     1,    20,
      52,    53,    20,    20,     6,     1,     6,    52,     1,    52,
      52,     1,    52,     6,     1,    52,     1,    52,     1,    52,
       1,    52,     1,    52,     1,    52,     1,    52,     1,    52,
       5,     1,    52,    20,     7,    20,    20,    20,     1,    20,
      20,    20,     1,    20,    22,    22,    53,    47,    47,    47,
      47,    47,    47,    47,    47,    28,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    33,    34,    34,    34,    35,    35,    35,
      35,    35,    35,    36,    36,    37,    37,    37,    38,    38,
      38,    38,    39,    39,    40,    40,    41,    41,    41,    42,
      42,    42,    42,    42,    42,    43,    43,    43,    43,    44,
      44,    45,    45,    45,    45,    45,    46,    46,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    48,    48,    49,
      49,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     0,     1,     3,     2,     3,
       2,     3,     3,     1,     3,     1,     1,     1,     5,     2,
       5,     5,     1,     0,     1,     1,     1,     4,     4,     4,
       3,     4,     4,     4,     3,     3,     1,     3,     1,     2,
       1,     4,     4,     3,     3,     1,     2,     0,     2,     1,
       3,     5,     7,     5,     2,     3,     2,     5,     5,     5,
       5,     5,     5,     2,     3,     3,     3,     2,     0,     3,
       3,     3,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     4,     3,     4,
       3,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     4,     4,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 96 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Program", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
    ROOT = (yyval.type_node);
}
#line 1571 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 102 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("StructSpecifier error");fault(162001);
}
#line 1580 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 108 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("ExtDefList", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 2, (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1589 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 112 "./syntax.y" /* yacc.c:1646  */
    {
        (yyloc).first_line = yylineno;
    (yyval.type_node) = NULL;
}
#line 1598 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 117 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("StructSpecifier error");fault(162001);
}
#line 1607 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 123 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("ExtDef", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1616 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 127 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("ExtDef", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 2, (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1625 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 131 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("ExtDef", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1634 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 135 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("error 0");
}
#line 1643 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 139 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("initialized or invalid global variable");
}
#line 1652 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 143 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("error 2");
}
#line 1661 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 149 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("ExtDecList", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 1670 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 153 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("ExtDecList", " ", (yyloc).first_line, 0);
}
#line 1678 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 159 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Specifier", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 1687 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 163 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Specifier", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 1696 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 168 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("Specifier error");fault(162000);
}
#line 1705 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 175 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("StructSpecifier", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 5, (yyvsp[-4].type_node), (yyvsp[-3].type_node), (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1714 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 179 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("StructSpecifier", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 2, (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1723 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 183 "./syntax.y" /* yacc.c:1646  */
    {
    missing("RC");fault(1613);
}
#line 1731 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 186 "./syntax.y" /* yacc.c:1646  */
    {
    missing("LC");fault(1616);
}
#line 1739 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 192 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("OptTag", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 1748 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 196 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = NULL;
}
#line 1756 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 202 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Tag", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 1765 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 206 "./syntax.y" /* yacc.c:1646  */
    {
    printf("OptTag error");fault(1618);
}
#line 1773 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 211 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("VarDec", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 1782 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 215 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("VarDec", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 4, (yyvsp[-3].type_node), (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1791 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 219 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid expression between \'[]\'");
}
#line 1800 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 225 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("FunDec", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 4, (yyvsp[-3].type_node), (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1809 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 229 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("FunDec", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1818 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 233 "./syntax.y" /* yacc.c:1646  */
    {
    missing("RP");
    fault(1622);
}
#line 1827 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 237 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid varlist");
}
#line 1836 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 241 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid function name");
}
#line 1845 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 245 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid function name");
}
#line 1854 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 251 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("VarList", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1863 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 255 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("VarList", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 1872 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 259 "./syntax.y" /* yacc.c:1646  */
    {
    missing("COMMA");
    fault(1628);
}
#line 1881 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 264 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("VarList error");fault(162002);
}
#line 1890 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 270 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("ParamDec", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 2, (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1899 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 275 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("ParamDec error");fault(162003);
}
#line 1908 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 281 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("CompSt", " ", (yyloc).first_line, 0);
    
    insertNode((yyval.type_node), 4, (yyvsp[-3].type_node), (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1918 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 286 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("missing \"}\"");fault(161942);
}
#line 1927 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 290 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("contents between \"{ }\" gets wrong");fault(161944);
}
#line 1936 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 294 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("missing \"{\"");fault(161945);
}
#line 1945 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 299 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("CompSt error");fault(1620031);
}
#line 1954 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 306 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("StmtList", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 2, (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 1963 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 310 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = NULL;
}
#line 1971 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 316 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Stmt", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 2, (yyvsp[-1].type_node), (yyvsp[0].type_node)); 
}
#line 1980 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 320 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Stmt", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 1989 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 324 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Stmt", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node)); 
}
#line 1998 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 328 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Stmt", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 5, (yyvsp[-4].type_node), (yyvsp[-3].type_node), (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2007 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 332 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Stmt", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 7, (yyvsp[-6].type_node), (yyvsp[-5].type_node), (yyvsp[-4].type_node), (yyvsp[-3].type_node), (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2016 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 336 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Stmt", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 5, (yyvsp[-4].type_node), (yyvsp[-3].type_node), (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2025 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 340 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("missing \";\"");fault(161850);
}
#line 2034 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 344 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("missing \";\"");fault(161850);
}
#line 2043 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 348 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("missing returning value and \";\"");fault(161900);
}
#line 2052 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 352 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("missing \')\'");fault(161911);
}
#line 2061 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 356 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("condition for \"if\" gets wrong");fault(161916);
}
#line 2070 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 360 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("missing left parenthesis");fault(161917);
}
#line 2079 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 364 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("missing right parenthesis");fault(161925);
}
#line 2088 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 368 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("condition for \"while\" gets wrong");fault(161929);
}
#line 2097 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 372 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("missing \'(\'");fault(161929);
}
#line 2106 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 376 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid statement or cannot define variable before \';\'");
}
#line 2115 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 380 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid expression near \';\'");
}
#line 2124 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 384 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid expression near \'return\'");
}
#line 2133 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 388 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid expression between \'return\' and \';\'");
}
#line 2142 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 394 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("DefList", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 2, (yyvsp[-1].type_node), (yyvsp[0].type_node)); 
}
#line 2151 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 398 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = NULL;
}
#line 2159 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 404 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Def", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2168 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 408 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid variable or expected expression before \';\'");
}
#line 2177 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 412 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("missing \';\' or invalid token");
}
#line 2186 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 418 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("DecList", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 2195 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 422 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("DecList", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2204 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 429 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Dec", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 2213 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 433 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Dec", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2222 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 440 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2231 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 444 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2240 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 448 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2249 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 452 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2258 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 456 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2267 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 460 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0); 
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2276 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 464 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2285 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 468 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2294 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 472 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0); 
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2303 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 476 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 2, (yyvsp[-1].type_node), (yyvsp[0].type_node)); 
}
#line 2312 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 480 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 2, (yyvsp[-1].type_node), (yyvsp[0].type_node)); 
}
#line 2321 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 484 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 4, (yyvsp[-3].type_node), (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2330 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 488 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0); 
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2339 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 492 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 4, (yyvsp[-3].type_node), (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2348 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 496 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2357 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 500 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 2366 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 504 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 2375 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 508 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Exp", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 2384 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 512 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token near \'=\'");
}
#line 2393 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 516 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token near \'&&\'");
}
#line 2402 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 520 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token near \'||\'");
}
#line 2411 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 524 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token near \'RELOP\'");
}
#line 2420 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 528 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token near \'+\'");
}
#line 2429 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 532 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token near \'-\'");
}
#line 2438 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 536 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token near \'*\'");
}
#line 2447 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 540 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token near \'/\'");
}
#line 2456 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 544 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token between \'()\'");
}
#line 2465 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 548 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token after \'-\'");
}
#line 2474 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 552 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid token after \'!\'");
}
#line 2483 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 556 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid tokens between \'()\'");
}
#line 2492 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 560 "./syntax.y" /* yacc.c:1646  */
    {
    syntaxError += 1;
    my_yyerror("invalid expression between \'[]\'");
}
#line 2501 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 566 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Args", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 3, (yyvsp[-2].type_node), (yyvsp[-1].type_node), (yyvsp[0].type_node));
}
#line 2510 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 570 "./syntax.y" /* yacc.c:1646  */
    {
    (yyval.type_node) = createNode("Args", " ", (yyloc).first_line, 0);
    insertNode((yyval.type_node), 1, (yyvsp[0].type_node));
}
#line 2519 "./syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2523 "./syntax.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 576 "./syntax.y" /* yacc.c:1906  */

#include "lex.yy.c"
void yyerror(char* msg) {
    // syntaxError += 1;
    // printf("Error type B at Line %d: %s.\n", yylineno, msg);
}
