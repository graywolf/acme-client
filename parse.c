/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 26 "parse.y"

#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#define ACMECLIENT_PARSER 1
#include "compat.h"
#include "parse.h"
#include "extern.h"

TAILQ_HEAD(files, file)		 files = TAILQ_HEAD_INITIALIZER(files);
static struct file {
	TAILQ_ENTRY(file)	 entry;
	FILE			*stream;
	char			*name;
	size_t			 ungetpos;
	size_t			 ungetsize;
	u_char			*ungetbuf;
	int			 eof_reached;
	int			 lineno;
	int			 errors;
} *file, *topfile;
struct file	*pushfile(const char *);
int		 popfile(void);
int		 yyparse(void);
int		 yylex(void);
int		 yyerror(const char *, ...)
#ifdef __GNUC__
    __attribute__((__format__ (printf, 1, 2)))
    __attribute__((__nonnull__ (1)));
#else
    ;
#endif
int		 kw_cmp(const void *, const void *);
int		 lookup(char *);
int		 igetc(void);
int		 lgetc(int);
void		 lungetc(int);
int		 findeol(void);

struct authority_c	*conf_new_authority(struct acme_conf *, char *);
struct domain_c		*conf_new_domain(struct acme_conf *, char *);
struct keyfile		*conf_new_keyfile(struct acme_conf *, char *);
void			 clear_config(struct acme_conf *);
const char*		 kt2txt(enum keytype);
void			 print_config(struct acme_conf *);
int			 conf_check_file(char *);

TAILQ_HEAD(symhead, sym)	 symhead = TAILQ_HEAD_INITIALIZER(symhead);
struct sym {
	TAILQ_ENTRY(sym)	 entry;
	int			 used;
	int			 persist;
	char			*nam;
	char			*val;
};
int		 symset(const char *, const char *, int);
char		*symget(const char *);

static struct acme_conf		*conf;
static struct authority_c	*auth;
static struct domain_c		*domain;
static int			 errors = 0;

typedef struct {
	union {
		int64_t		 number;
		char		*string;
	} v;
	int lineno;
} YYSTYPE;


#line 153 "parse.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    AUTHORITY = 258,               /* AUTHORITY  */
    URL = 259,                     /* URL  */
    API = 260,                     /* API  */
    ACCOUNT = 261,                 /* ACCOUNT  */
    CONTACT = 262,                 /* CONTACT  */
    DOMAIN = 263,                  /* DOMAIN  */
    ALTERNATIVE = 264,             /* ALTERNATIVE  */
    NAME = 265,                    /* NAME  */
    NAMES = 266,                   /* NAMES  */
    CERT = 267,                    /* CERT  */
    FULL = 268,                    /* FULL  */
    CHAIN = 269,                   /* CHAIN  */
    KEY = 270,                     /* KEY  */
    SIGN = 271,                    /* SIGN  */
    WITH = 272,                    /* WITH  */
    CHALLENGEDIR = 273,            /* CHALLENGEDIR  */
    YES = 274,                     /* YES  */
    NO = 275,                      /* NO  */
    INCLUDE = 276,                 /* INCLUDE  */
    ERROR = 277,                   /* ERROR  */
    RSA = 278,                     /* RSA  */
    ECDSA = 279,                   /* ECDSA  */
    STRING = 280,                  /* STRING  */
    NUMBER = 281                   /* NUMBER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define AUTHORITY 258
#define URL 259
#define API 260
#define ACCOUNT 261
#define CONTACT 262
#define DOMAIN 263
#define ALTERNATIVE 264
#define NAME 265
#define NAMES 266
#define CERT 267
#define FULL 268
#define CHAIN 269
#define KEY 270
#define SIGN 271
#define WITH 272
#define CHALLENGEDIR 273
#define YES 274
#define NO 275
#define INCLUDE 276
#define ERROR 277
#define RSA 278
#define ECDSA 279
#define STRING 280
#define NUMBER 281

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_AUTHORITY = 3,                  /* AUTHORITY  */
  YYSYMBOL_URL = 4,                        /* URL  */
  YYSYMBOL_API = 5,                        /* API  */
  YYSYMBOL_ACCOUNT = 6,                    /* ACCOUNT  */
  YYSYMBOL_CONTACT = 7,                    /* CONTACT  */
  YYSYMBOL_DOMAIN = 8,                     /* DOMAIN  */
  YYSYMBOL_ALTERNATIVE = 9,                /* ALTERNATIVE  */
  YYSYMBOL_NAME = 10,                      /* NAME  */
  YYSYMBOL_NAMES = 11,                     /* NAMES  */
  YYSYMBOL_CERT = 12,                      /* CERT  */
  YYSYMBOL_FULL = 13,                      /* FULL  */
  YYSYMBOL_CHAIN = 14,                     /* CHAIN  */
  YYSYMBOL_KEY = 15,                       /* KEY  */
  YYSYMBOL_SIGN = 16,                      /* SIGN  */
  YYSYMBOL_WITH = 17,                      /* WITH  */
  YYSYMBOL_CHALLENGEDIR = 18,              /* CHALLENGEDIR  */
  YYSYMBOL_YES = 19,                       /* YES  */
  YYSYMBOL_NO = 20,                        /* NO  */
  YYSYMBOL_INCLUDE = 21,                   /* INCLUDE  */
  YYSYMBOL_ERROR = 22,                     /* ERROR  */
  YYSYMBOL_RSA = 23,                       /* RSA  */
  YYSYMBOL_ECDSA = 24,                     /* ECDSA  */
  YYSYMBOL_STRING = 25,                    /* STRING  */
  YYSYMBOL_NUMBER = 26,                    /* NUMBER  */
  YYSYMBOL_27_n_ = 27,                     /* '\n'  */
  YYSYMBOL_28_ = 28,                       /* '='  */
  YYSYMBOL_29_ = 29,                       /* ','  */
  YYSYMBOL_30_ = 30,                       /* '{'  */
  YYSYMBOL_31_ = 31,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_grammar = 33,                   /* grammar  */
  YYSYMBOL_include = 34,                   /* include  */
  YYSYMBOL_string = 35,                    /* string  */
  YYSYMBOL_varset = 36,                    /* varset  */
  YYSYMBOL_optnl = 37,                     /* optnl  */
  YYSYMBOL_nl = 38,                        /* nl  */
  YYSYMBOL_comma = 39,                     /* comma  */
  YYSYMBOL_authority = 40,                 /* authority  */
  YYSYMBOL_41_1 = 41,                      /* $@1  */
  YYSYMBOL_authorityopts_l = 42,           /* authorityopts_l  */
  YYSYMBOL_authorityoptsl = 43,            /* authorityoptsl  */
  YYSYMBOL_domain = 44,                    /* domain  */
  YYSYMBOL_45_2 = 45,                      /* $@2  */
  YYSYMBOL_keytype = 46,                   /* keytype  */
  YYSYMBOL_domainopts_l = 47,              /* domainopts_l  */
  YYSYMBOL_domainoptsl = 48,               /* domainoptsl  */
  YYSYMBOL_altname_l = 49,                 /* altname_l  */
  YYSYMBOL_altname = 50                    /* altname  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   80

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  42
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  88

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    29,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,    31,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   121,   121,   122,   123,   124,   125,   126,   127,   130,
     145,   155,   158,   178,   179,   182,   185,   186,   189,   189,
     213,   214,   217,   227,   238,   250,   250,   286,   287,   288,
     291,   292,   295,   296,   306,   326,   346,   361,   376,   391,
     403,   404,   407
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "AUTHORITY", "URL",
  "API", "ACCOUNT", "CONTACT", "DOMAIN", "ALTERNATIVE", "NAME", "NAMES",
  "CERT", "FULL", "CHAIN", "KEY", "SIGN", "WITH", "CHALLENGEDIR", "YES",
  "NO", "INCLUDE", "ERROR", "RSA", "ECDSA", "STRING", "NUMBER", "'\\n'",
  "'='", "','", "'{'", "'}'", "$accept", "grammar", "include", "string",
  "varset", "optnl", "nl", "comma", "authority", "$@1", "authorityopts_l",
  "authorityoptsl", "domain", "$@2", "keytype", "domainopts_l",
  "domainoptsl", "altname_l", "altname", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    10,    61,    44,
     123,   125
};
#endif

#define YYPACT_NINF (-28)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-42)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -28,     3,   -28,   -26,   -20,    -2,     1,     6,   -28,     5,
      11,    19,    20,   -28,   -28,   -28,   -28,    23,   -28,   -28,
     -28,   -28,    -1,    21,   -28,    24,    25,    25,   -28,    25,
      38,     9,   -28,    46,    16,    28,     2,    25,    27,    43,
      39,    30,     4,    25,    32,    33,   -28,   -28,    34,   -28,
      35,    37,    45,    51,    40,    36,    42,   -28,   -28,    34,
     -28,   -28,    -9,    25,   -28,   -28,   -28,    52,    44,    -9,
      47,   -28,   -28,   -28,   -28,   -28,   -28,    48,   -28,   -28,
     -28,    49,   -10,   -28,   -28,   -28,    47,   -28
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     5,     0,
       0,     0,     0,     8,    18,    25,     9,     0,     3,     4,
       6,     7,     0,     0,    11,    12,    14,    14,    10,    14,
       0,     0,    13,     0,     0,     0,     0,    14,     0,     0,
       0,     0,     0,    14,     0,     0,    24,    19,     0,    21,
       0,     0,     0,     0,     0,     0,     0,    39,    26,     0,
      31,    22,    29,    14,    20,    33,    35,     0,     0,    29,
       0,    38,    30,    27,    28,    23,    15,     0,    36,    34,
      42,     0,    17,    37,    32,    16,     0,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -28,   -28,   -28,   -28,   -28,   -27,    12,   -28,   -28,   -28,
     -28,    41,   -28,   -28,     7,   -28,    26,   -16,   -28
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     9,    25,    10,    30,    64,    86,    11,    22,
      36,    37,    12,    23,    75,    42,    43,    81,    82
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      31,    13,    32,     2,     3,    14,     4,    33,    34,    35,
      49,     5,    38,    39,    73,    74,    60,    38,    39,    85,
      40,   -41,    41,    15,     6,    40,    16,    41,     7,    26,
       8,    45,    18,    47,    17,    58,    76,    50,    19,    51,
      52,    53,    54,    33,    34,    35,    20,    21,    24,    28,
      44,    27,    29,    46,    55,    57,    56,    61,    62,    67,
      65,    63,    66,    68,    77,    69,    70,    71,    59,    78,
      87,    72,    80,    83,     0,     0,    79,    48,     0,     0,
      84
};

static const yytype_int8 yycheck[] =
{
      27,    27,    29,     0,     1,    25,     3,     5,     6,     7,
      37,     8,     8,     9,    23,    24,    43,     8,     9,    29,
      16,    31,    18,    25,    21,    16,    25,    18,    25,    30,
      27,    15,    27,    31,    28,    31,    63,    10,    27,    12,
      13,    14,    15,     5,     6,     7,    27,    27,    25,    25,
       4,    30,    27,    25,    11,    25,    17,    25,    25,    14,
      25,    27,    25,    12,    12,    25,    30,    25,    42,    25,
      86,    59,    25,    25,    -1,    -1,    69,    36,    -1,    -1,
      31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    33,     0,     1,     3,     8,    21,    25,    27,    34,
      36,    40,    44,    27,    25,    25,    25,    28,    27,    27,
      27,    27,    41,    45,    25,    35,    30,    30,    25,    27,
      37,    37,    37,     5,     6,     7,    42,    43,     8,     9,
      16,    18,    47,    48,     4,    15,    25,    31,    43,    37,
      10,    12,    13,    14,    15,    11,    17,    25,    31,    48,
      37,    25,    25,    27,    38,    25,    25,    14,    12,    25,
      30,    25,    38,    23,    24,    46,    37,    12,    25,    46,
      25,    49,    50,    25,    31,    29,    39,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    33,    33,    33,    33,    33,    33,    34,
      35,    35,    36,    37,    37,    38,    39,    39,    41,    40,
      42,    42,    43,    43,    43,    45,    44,    46,    46,    46,
      47,    47,    48,    48,    48,    48,    48,    48,    48,    48,
      49,    49,    50
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     3,     2,     3,     3,     3,     2,
       2,     1,     3,     2,     0,     2,     1,     0,     0,     7,
       3,     2,     3,     4,     2,     0,     7,     1,     1,     0,
       3,     2,     5,     3,     4,     3,     4,     5,     3,     2,
       3,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8: /* grammar: grammar error '\n'  */
#line 127 "parse.y"
                                                { file->errors++; }
#line 1318 "parse.c"
    break;

  case 9: /* include: INCLUDE STRING  */
#line 130 "parse.y"
                                                {
			struct file	*nfile;

			if ((nfile = pushfile((yyvsp[0].v.string))) == NULL) {
				yyerror("failed to include file %s", (yyvsp[0].v.string));
				free((yyvsp[0].v.string));
				YYERROR;
			}
			free((yyvsp[0].v.string));

			file = nfile;
			lungetc('\n');
		}
#line 1336 "parse.c"
    break;

  case 10: /* string: string STRING  */
#line 145 "parse.y"
                                {
			if (asprintf(&(yyval.v.string), "%s %s", (yyvsp[-1].v.string), (yyvsp[0].v.string)) == -1) {
				free((yyvsp[-1].v.string));
				free((yyvsp[0].v.string));
				yyerror("string: asprintf");
				YYERROR;
			}
			free((yyvsp[-1].v.string));
			free((yyvsp[0].v.string));
		}
#line 1351 "parse.c"
    break;

  case 12: /* varset: STRING '=' string  */
#line 158 "parse.y"
                                                {
			char *s = (yyvsp[-2].v.string);
			if (conf->opts & ACME_OPT_VERBOSE)
				printf("%s = \"%s\"\n", (yyvsp[-2].v.string), (yyvsp[0].v.string));
			while (*s++) {
				if (isspace((unsigned char)*s)) {
					yyerror("macro name cannot contain "
					    "whitespace");
					free((yyvsp[-2].v.string));
					free((yyvsp[0].v.string));
					YYERROR;
				}
			}
			if (symset((yyvsp[-2].v.string), (yyvsp[0].v.string), 0) == -1)
				errx(EXIT_FAILURE, "cannot store variable");
			free((yyvsp[-2].v.string));
			free((yyvsp[0].v.string));
		}
#line 1374 "parse.c"
    break;

  case 18: /* $@1: %empty  */
#line 189 "parse.y"
                                   {
			char *s;
			if ((s = strdup((yyvsp[0].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			if ((auth = conf_new_authority(conf, s)) == NULL) {
				free(s);
				yyerror("authority already defined");
				YYERROR;
			}
		}
#line 1389 "parse.c"
    break;

  case 19: /* authority: AUTHORITY STRING $@1 '{' optnl authorityopts_l '}'  */
#line 198 "parse.y"
                                                {
			if (auth->api == NULL) {
				yyerror("authority %s: no api URL specified",
				    auth->name);
				YYERROR;
			}
			if (auth->account == NULL) {
				yyerror("authority %s: no account key file "
				    "specified", auth->name);
				YYERROR;
			}
			auth = NULL;
		}
#line 1407 "parse.c"
    break;

  case 22: /* authorityoptsl: API URL STRING  */
#line 217 "parse.y"
                                 {
			char *s;
			if (auth->api != NULL) {
				yyerror("duplicate api");
				YYERROR;
			}
			if ((s = strdup((yyvsp[0].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			auth->api = s;
		}
#line 1422 "parse.c"
    break;

  case 23: /* authorityoptsl: ACCOUNT KEY STRING keytype  */
#line 227 "parse.y"
                                            {
			char *s;
			if (auth->account != NULL) {
				yyerror("duplicate account");
				YYERROR;
			}
			if ((s = strdup((yyvsp[-1].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			auth->account = s;
			auth->keytype = (yyvsp[0].v.number);
		}
#line 1438 "parse.c"
    break;

  case 24: /* authorityoptsl: CONTACT STRING  */
#line 238 "parse.y"
                                 {
			char *s;
			if (auth->contact != NULL) {
				yyerror("duplicate contact");
				YYERROR;
			}
			if ((s = strdup((yyvsp[0].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			auth->contact = s;
		}
#line 1453 "parse.c"
    break;

  case 25: /* $@2: %empty  */
#line 250 "parse.y"
                                {
			char *s;
			if ((s = strdup((yyvsp[0].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			if (!domain_valid(s)) {
				yyerror("%s: bad domain syntax", s);
				free(s);
				YYERROR;
			}
			if ((domain = conf_new_domain(conf, s)) == NULL) {
				free(s);
				yyerror("domain already defined");
				YYERROR;
			}
		}
#line 1473 "parse.c"
    break;

  case 26: /* domain: DOMAIN STRING $@2 '{' optnl domainopts_l '}'  */
#line 264 "parse.y"
                                             {
			if (domain->domain == NULL) {
				if ((domain->domain = strdup(domain->handle))
				    == NULL)
					err(EXIT_FAILURE, "strdup");
			}
			/* enforce minimum config here */
			if (domain->key == NULL) {
				yyerror("no domain key file specified for "
				    "domain %s", domain->domain);
				YYERROR;
			}
			if (domain->cert == NULL && domain->fullchain == NULL) {
				yyerror("at least certificate file or full "
				    "certificate chain file must be specified "
				    "for domain %s", domain->domain);
				YYERROR;
			}
			domain = NULL;
		}
#line 1498 "parse.c"
    break;

  case 27: /* keytype: RSA  */
#line 286 "parse.y"
                        { (yyval.v.number) = KT_RSA; }
#line 1504 "parse.c"
    break;

  case 28: /* keytype: ECDSA  */
#line 287 "parse.y"
                        { (yyval.v.number) = KT_ECDSA; }
#line 1510 "parse.c"
    break;

  case 29: /* keytype: %empty  */
#line 288 "parse.y"
                        { (yyval.v.number) = KT_RSA; }
#line 1516 "parse.c"
    break;

  case 33: /* domainoptsl: DOMAIN NAME STRING  */
#line 296 "parse.y"
                                     {
			char *s;
			if (domain->domain != NULL) {
				yyerror("duplicate domain name");
				YYERROR;
			}
			if ((s = strdup((yyvsp[0].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			domain->domain = s;
		}
#line 1531 "parse.c"
    break;

  case 34: /* domainoptsl: DOMAIN KEY STRING keytype  */
#line 306 "parse.y"
                                            {
			char *s;
			if (domain->key != NULL) {
				yyerror("duplicate key");
				YYERROR;
			}
			if ((s = strdup((yyvsp[-1].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			if (!conf_check_file(s)) {
				free(s);
				YYERROR;
			}
			if ((conf_new_keyfile(conf, s)) == NULL) {
				free(s);
				yyerror("domain key file already used");
				YYERROR;
			}
			domain->key = s;
			domain->keytype = (yyvsp[0].v.number);
		}
#line 1556 "parse.c"
    break;

  case 35: /* domainoptsl: DOMAIN CERT STRING  */
#line 326 "parse.y"
                                     {
			char *s;
			if (domain->cert != NULL) {
				yyerror("duplicate cert");
				YYERROR;
			}
			if ((s = strdup((yyvsp[0].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			if (s[0] != '/') {
				free(s);
				yyerror("not an absolute path");
				YYERROR;
			}
			if ((conf_new_keyfile(conf, s)) == NULL) {
				free(s);
				yyerror("domain cert file already used");
				YYERROR;
			}
			domain->cert = s;
		}
#line 1581 "parse.c"
    break;

  case 36: /* domainoptsl: DOMAIN CHAIN CERT STRING  */
#line 346 "parse.y"
                                           {
			char *s;
			if (domain->chain != NULL) {
				yyerror("duplicate chain");
				YYERROR;
			}
			if ((s = strdup((yyvsp[0].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			if ((conf_new_keyfile(conf, s)) == NULL) {
				free(s);
				yyerror("domain chain file already used");
				YYERROR;
			}
			domain->chain = s;
		}
#line 1601 "parse.c"
    break;

  case 37: /* domainoptsl: DOMAIN FULL CHAIN CERT STRING  */
#line 361 "parse.y"
                                                {
			char *s;
			if (domain->fullchain != NULL) {
				yyerror("duplicate full chain");
				YYERROR;
			}
			if ((s = strdup((yyvsp[0].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			if ((conf_new_keyfile(conf, s)) == NULL) {
				free(s);
				yyerror("domain full chain file already used");
				YYERROR;
			}
			domain->fullchain = s;
		}
#line 1621 "parse.c"
    break;

  case 38: /* domainoptsl: SIGN WITH STRING  */
#line 376 "parse.y"
                                   {
			char *s;
			if (domain->auth != NULL) {
				yyerror("duplicate sign with");
				YYERROR;
			}
			if ((s = strdup((yyvsp[0].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			if (authority_find(conf, s) == NULL) {
				yyerror("sign with: unknown authority");
				free(s);
				YYERROR;
			}
			domain->auth = s;
		}
#line 1641 "parse.c"
    break;

  case 39: /* domainoptsl: CHALLENGEDIR STRING  */
#line 391 "parse.y"
                                      {
			char *s;
			if (domain->challengedir != NULL) {
				yyerror("duplicate challengedir");
				YYERROR;
			}
			if ((s = strdup((yyvsp[0].v.string))) == NULL)
				err(EXIT_FAILURE, "strdup");
			domain->challengedir = s;
		}
#line 1656 "parse.c"
    break;

  case 42: /* altname: STRING  */
#line 407 "parse.y"
                         {
			char			*s;
			struct altname_c	*ac;
			if (!domain_valid((yyvsp[0].v.string))) {
				yyerror("bad domain syntax");
				YYERROR;
			}
			if ((ac = calloc(1, sizeof(struct altname_c))) == NULL)
				err(EXIT_FAILURE, "calloc");
			if ((s = strdup((yyvsp[0].v.string))) == NULL) {
				free(ac);
				err(EXIT_FAILURE, "strdup");
			}
			ac->domain = s;
			TAILQ_INSERT_TAIL(&domain->altname_list, ac, entry);
			domain->altname_count++;
			/*
			 * XXX we could check if altname is duplicate
			 * or identical to domain->domain
			*/
		}
#line 1682 "parse.c"
    break;


#line 1686 "parse.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 429 "parse.y"


struct keywords {
	const char	*k_name;
	int		 k_val;
};

int
yyerror(const char *fmt, ...)
{
	va_list		 ap;
	char		*msg;

	file->errors++;
	va_start(ap, fmt);
	if (vasprintf(&msg, fmt, ap) == -1)
		err(EXIT_FAILURE, "yyerror vasprintf");
	va_end(ap);
	fprintf(stderr, "%s:%d: %s\n", file->name, yylval.lineno, msg);
	free(msg);
	return (0);
}

int
kw_cmp(const void *k, const void *e)
{
	return strcmp(k, ((const struct keywords *)e)->k_name);
}

int
lookup(char *s)
{
	/* this has to be sorted always */
	static const struct keywords keywords[] = {
		{"account",		ACCOUNT},
		{"alternative",		ALTERNATIVE},
		{"api",			API},
		{"authority",		AUTHORITY},
		{"certificate",		CERT},
		{"chain",		CHAIN},
		{"challengedir",	CHALLENGEDIR},
		{"contact",		CONTACT},
		{"domain",		DOMAIN},
		{"ecdsa",		ECDSA},
		{"full",		FULL},
		{"include",		INCLUDE},
		{"key",			KEY},
		{"name",		NAME},
		{"names",		NAMES},
		{"rsa",			RSA},
		{"sign",		SIGN},
		{"url",			URL},
		{"with",		WITH},
	};
	const struct keywords	*p;

	p = bsearch(s, keywords, sizeof(keywords)/sizeof(keywords[0]),
	    sizeof(keywords[0]), kw_cmp);

	if (p != NULL)
		return p->k_val;
	else
		return STRING;
}

#define	START_EXPAND	1
#define	DONE_EXPAND	2

static int	expanding;

int
igetc(void)
{
	int	c;

	while (1) {
		if (file->ungetpos > 0)
			c = file->ungetbuf[--file->ungetpos];
		else
			c = getc(file->stream);

		if (c == START_EXPAND)
			expanding = 1;
		else if (c == DONE_EXPAND)
			expanding = 0;
		else
			break;
	}
	return c;
}

int
lgetc(int quotec)
{
	int		c, next;

	if (quotec) {
		if ((c = igetc()) == EOF) {
			yyerror("reached end of file while parsing "
			    "quoted string");
			if (file == topfile || popfile() == EOF)
				return (EOF);
			return quotec;
		}
		return c;
	}

	while ((c = igetc()) == '\\') {
		next = igetc();
		if (next != '\n') {
			c = next;
			break;
		}
		yylval.lineno = file->lineno;
		file->lineno++;
	}

	if (c == EOF) {
		/*
		 * Fake EOL when hit EOF for the first time. This gets line
		 * count right if last line in included file is syntactically
		 * invalid and has no newline.
		 */
		if (file->eof_reached == 0) {
			file->eof_reached = 1;
			return '\n';
		}
		while (c == EOF) {
			if (file == topfile || popfile() == EOF)
				return (EOF);
			c = igetc();
		}
	}
	return c;
}

void
lungetc(int c)
{
	if (c == EOF)
		return;

	if (file->ungetpos >= file->ungetsize) {
		void *p = reallocarray(file->ungetbuf, file->ungetsize, 2);
		if (p == NULL)
			err(1, "%s", __func__);
		file->ungetbuf = p;
		file->ungetsize *= 2;
	}
	file->ungetbuf[file->ungetpos++] = c;
}

int
findeol(void)
{
	int	c;

	/* skip to either EOF or the first real EOL */
	while (1) {
		c = lgetc(0);
		if (c == '\n') {
			file->lineno++;
			break;
		}
		if (c == EOF)
			break;
	}
	return ERROR;
}

int
yylex(void)
{
	u_char	 buf[8096];
	u_char	*p, *val;
	int	 quotec, next, c;
	int	 token;

top:
	p = buf;
	while ((c = lgetc(0)) == ' ' || c == '\t')
		; /* nothing */

	yylval.lineno = file->lineno;
	if (c == '#')
		while ((c = lgetc(0)) != '\n' && c != EOF)
			; /* nothing */
	if (c == '$' && !expanding) {
		while (1) {
			if ((c = lgetc(0)) == EOF)
				return 0;

			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return findeol();
			}
			if (isalnum(c) || c == '_') {
				*p++ = c;
				continue;
			}
			*p = '\0';
			lungetc(c);
			break;
		}
		val = (u_char *)symget((char *)buf);
		if (val == NULL) {
			yyerror("macro '%s' not defined", buf);
			return findeol();
		}
		p = val + strlen((char *)val) - 1;
		lungetc(DONE_EXPAND);
		while (p >= val) {
			lungetc(*p);
			p--;
		}
		lungetc(START_EXPAND);
		goto top;
	}

	switch (c) {
	case '\'':
	case '"':
		quotec = c;
		while (1) {
			if ((c = lgetc(quotec)) == EOF)
				return 0;
			if (c == '\n') {
				file->lineno++;
				continue;
			} else if (c == '\\') {
				if ((next = lgetc(quotec)) == EOF)
					return 0;
				if (next == quotec || next == ' ' ||
				    next == '\t')
					c = next;
				else if (next == '\n') {
					file->lineno++;
					continue;
				} else
					lungetc(next);
			} else if (c == quotec) {
				*p = '\0';
				break;
			} else if (c == '\0') {
				yyerror("syntax error");
				return findeol();
			}
			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return findeol();
			}
			*p++ = c;
		}
		yylval.v.string = strdup((char *)buf);
		if (yylval.v.string == NULL)
			err(EXIT_FAILURE, "%s", __func__);
		return STRING;
	}

#define allowed_to_end_number(x) \
	(isspace(x) || x == ')' || x ==',' || x == '/' || x == '}' || x == '=')

	if (c == '-' || isdigit(c)) {
		do {
			*p++ = c;
			if ((size_t)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return findeol();
			}
		} while ((c = lgetc(0)) != EOF && isdigit(c));
		lungetc(c);
		if (p == buf + 1 && buf[0] == '-')
			goto nodigits;
		if (c == EOF || allowed_to_end_number(c)) {
			const char *errstr = NULL;

			*p = '\0';
			yylval.v.number = strtonum((char *)buf, LLONG_MIN,
			    LLONG_MAX, &errstr);
			if (errstr != NULL) {
				yyerror("\"%s\" invalid number: %s",
				    buf, errstr);
				return (findeol());
			}
			return NUMBER;
		} else {
nodigits:
			while (p > buf + 1)
				lungetc(*--p);
			c = *--p;
			if (c == '-')
				return c;
		}
	}

#define allowed_in_string(x) \
	(isalnum(x) || (ispunct(x) && x != '(' && x != ')' && \
	x != '{' && x != '}' && \
	x != '!' && x != '=' && x != '#' && \
	x != ','))

	if (isalnum(c) || c == ':' || c == '_') {
		do {
			*p++ = c;
			if ((size_t)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(0)) != EOF && (allowed_in_string(c)));
		lungetc(c);
		*p = '\0';
		if ((token = lookup((char *)buf)) == STRING) {
			if ((yylval.v.string = strdup((char *)buf)) == NULL)
				err(EXIT_FAILURE, "%s", __func__);
		}
		return token;
	}
	if (c == '\n') {
		yylval.lineno = file->lineno;
		file->lineno++;
	}
	if (c == EOF)
		return 0;
	return c;
}

struct file *
pushfile(const char *name)
{
	struct file	*nfile;

	if ((nfile = calloc(1, sizeof(struct file))) == NULL) {
		warn("%s", __func__);
		return NULL;
	}
	if ((nfile->name = strdup(name)) == NULL) {
		warn("%s", __func__);
		free(nfile);
		return NULL;
	}
	if ((nfile->stream = fopen(nfile->name, "r")) == NULL) {
		warn("%s: %s", __func__, nfile->name);
		free(nfile->name);
		free(nfile);
		return NULL;
	}
	nfile->lineno = TAILQ_EMPTY(&files) ? 1 : 0;
	nfile->ungetsize = 16;
	nfile->ungetbuf = malloc(nfile->ungetsize);
	if (nfile->ungetbuf == NULL) {
		warn("%s", __func__);
		fclose(nfile->stream);
		free(nfile->name);
		free(nfile);
		return NULL;
	}
	TAILQ_INSERT_TAIL(&files, nfile, entry);
	return nfile;
}

int
popfile(void)
{
	struct file	*prev;

	if ((prev = TAILQ_PREV(file, files, entry)) != NULL)
		prev->errors += file->errors;

	TAILQ_REMOVE(&files, file, entry);
	fclose(file->stream);
	free(file->name);
	free(file->ungetbuf);
	free(file);
	file = prev;
	return (file ? 0 : EOF);
}

struct acme_conf *
parse_config(const char *filename, int opts)
{
	struct sym	*sym, *next;

	if ((conf = calloc(1, sizeof(struct acme_conf))) == NULL)
		err(EXIT_FAILURE, "%s", __func__);
	conf->opts = opts;

	if ((file = pushfile(filename)) == NULL) {
		free(conf);
		return NULL;
	}
	topfile = file;

	TAILQ_INIT(&conf->authority_list);
	TAILQ_INIT(&conf->domain_list);

	yyparse();
	errors = file->errors;
	popfile();

	/* Free macros and check which have not been used. */
	TAILQ_FOREACH_SAFE(sym, &symhead, entry, next) {
		if ((conf->opts & ACME_OPT_VERBOSE) && !sym->used)
			fprintf(stderr, "warning: macro '%s' not "
			    "used\n", sym->nam);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	if (errors != 0) {
		clear_config(conf);
		return NULL;
	}

	if (opts & ACME_OPT_CHECK) {
		if (opts & ACME_OPT_VERBOSE)
			print_config(conf);
		exit(0);
	}


	return conf;
}

int
symset(const char *nam, const char *val, int persist)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry) {
		if (strcmp(nam, sym->nam) == 0)
			break;
	}

	if (sym != NULL) {
		if (sym->persist == 1)
			return (0);
		else {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}
	if ((sym = calloc(1, sizeof(*sym))) == NULL)
		return -1;

	sym->nam = strdup(nam);
	if (sym->nam == NULL) {
		free(sym);
		return -1;
	}
	sym->val = strdup(val);
	if (sym->val == NULL) {
		free(sym->nam);
		free(sym);
		return -1;
	}
	sym->used = 0;
	sym->persist = persist;
	TAILQ_INSERT_TAIL(&symhead, sym, entry);
	return 0;
}

int
cmdline_symset(char *s)
{
	char	*sym, *val;
	int	ret;

	if ((val = strrchr(s, '=')) == NULL)
		return -1;
	sym = strndup(s, val - s);
	if (sym == NULL)
		errx(EXIT_FAILURE, "%s: strndup", __func__);
	ret = symset(sym, val + 1, 1);
	free(sym);

	return ret;
}

char *
symget(const char *nam)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry) {
		if (strcmp(nam, sym->nam) == 0) {
			sym->used = 1;
			return sym->val;
		}
	}
	return NULL;
}

struct authority_c *
conf_new_authority(struct acme_conf *c, char *s)
{
	struct authority_c *a;

	a = authority_find(c, s);
	if (a != NULL)
		return NULL;
	if ((a = calloc(1, sizeof(struct authority_c))) == NULL)
		err(EXIT_FAILURE, "%s", __func__);
	TAILQ_INSERT_TAIL(&c->authority_list, a, entry);

	a->name = s;
	return a;
}

struct authority_c *
authority_find(struct acme_conf *c, char *s)
{
	struct authority_c	*a;

	TAILQ_FOREACH(a, &c->authority_list, entry) {
		if (strncmp(a->name, s, AUTH_MAXLEN) == 0) {
			return a;
		}
	}
	return NULL;
}

struct authority_c *
authority_find0(struct acme_conf *c)
{
	return (TAILQ_FIRST(&c->authority_list));
}

struct domain_c *
conf_new_domain(struct acme_conf *c, char *s)
{
	struct domain_c *d;

	d = domain_find_handle(c, s);
	if (d != NULL)
		return (NULL);
	if ((d = calloc(1, sizeof(struct domain_c))) == NULL)
		err(EXIT_FAILURE, "%s", __func__);
	TAILQ_INSERT_TAIL(&c->domain_list, d, entry);

	d->handle = s;
	TAILQ_INIT(&d->altname_list);

	return d;
}

struct domain_c *
domain_find_handle(struct acme_conf *c, char *s)
{
	struct domain_c	*d;

	TAILQ_FOREACH(d, &c->domain_list, entry) {
		if (strncmp(d->handle, s, DOMAIN_MAXLEN) == 0) {
			return d;
		}
	}
	return NULL;
}

struct keyfile *
conf_new_keyfile(struct acme_conf *c, char *s)
{
	struct keyfile *k;

	LIST_FOREACH(k, &c->used_key_list, entry) {
		if (strncmp(k->name, s, PATH_MAX) == 0) {
			return NULL;
		}
	}

	if ((k = calloc(1, sizeof(struct keyfile))) == NULL)
		err(EXIT_FAILURE, "%s", __func__);
	LIST_INSERT_HEAD(&c->used_key_list, k, entry);

	k->name = s;
	return k;
}

void
clear_config(struct acme_conf *xconf)
{
	struct authority_c	*a;
	struct domain_c		*d;
	struct altname_c	*ac;

	while ((a = TAILQ_FIRST(&xconf->authority_list)) != NULL) {
		TAILQ_REMOVE(&xconf->authority_list, a, entry);
		free(a);
	}
	while ((d = TAILQ_FIRST(&xconf->domain_list)) != NULL) {
		while ((ac = TAILQ_FIRST(&d->altname_list)) != NULL) {
			TAILQ_REMOVE(&d->altname_list, ac, entry);
			free(ac);
		}
		TAILQ_REMOVE(&xconf->domain_list, d, entry);
		free(d);
	}
	free(xconf);
}

const char*
kt2txt(enum keytype kt)
{
	switch (kt) {
	case KT_RSA:
		return "rsa";
	case KT_ECDSA:
		return "ecdsa";
	default:
		return "<unknown>";
	}
}

void
print_config(struct acme_conf *xconf)
{
	struct authority_c	*a;
	struct domain_c		*d;
	struct altname_c	*ac;
	int			 f;

	TAILQ_FOREACH(a, &xconf->authority_list, entry) {
		printf("authority %s {\n", a->name);
		if (a->api != NULL)
			printf("\tapi url \"%s\"\n", a->api);
		if (a->account != NULL)
			printf("\taccount key \"%s\" %s\n", a->account,
			    kt2txt(a->keytype));
		printf("}\n\n");
	}
	TAILQ_FOREACH(d, &xconf->domain_list, entry) {
		f = 0;
		printf("domain %s {\n", d->handle);
		if (d->domain != NULL)
			printf("\tdomain name \"%s\"\n", d->domain);
		TAILQ_FOREACH(ac, &d->altname_list, entry) {
			if (!f)
				printf("\talternative names {");
			if (ac->domain != NULL) {
				printf("%s%s", f ? ", " : " ", ac->domain);
				f = 1;
			}
		}
		if (f)
			printf(" }\n");
		if (d->key != NULL)
			printf("\tdomain key \"%s\" %s\n", d->key, kt2txt(
			    d->keytype));
		if (d->cert != NULL)
			printf("\tdomain certificate \"%s\"\n", d->cert);
		if (d->chain != NULL)
			printf("\tdomain chain certificate \"%s\"\n", d->chain);
		if (d->fullchain != NULL)
			printf("\tdomain full chain certificate \"%s\"\n",
			    d->fullchain);
		if (d->auth != NULL)
			printf("\tsign with \"%s\"\n", d->auth);
		if (d->challengedir != NULL)
			printf("\tchallengedir \"%s\"\n", d->challengedir);
		printf("}\n\n");
	}
}

/*
 * This isn't RFC1035 compliant, but does the bare minimum in making
 * sure that we don't get bogus domain names on the command line, which
 * might otherwise screw up our directory structure.
 * Returns zero on failure, non-zero on success.
 */
int
domain_valid(const char *cp)
{

	for ( ; *cp != '\0'; cp++)
		if (!(*cp == '.' || *cp == '-' ||
		    *cp == '_' || isalnum((int)*cp)))
			return 0;
	return 1;
}

int
conf_check_file(char *s)
{
	struct stat st;

	if (s[0] != '/') {
		warnx("%s: not an absolute path", s);
		return 0;
	}
	if (stat(s, &st)) {
		if (errno == ENOENT)
			return 1;
		warn("cannot stat %s", s);
		return 0;
	}
	if (st.st_mode & (S_IRWXG | S_IRWXO)) {
		warnx("%s: group read/writable or world read/writable", s);
		return 0;
	}
	return 1;
}
