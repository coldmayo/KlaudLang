#include "include/defs.h"
#include "include/data.h"
#include "include/funCall.h"

static struct ASTnode *primary(void) {
  struct ASTnode *n;
  int id;

  switch (Token.token) {
    case T_INTLIT:
      n = mkastleaf(A_INTLIT, Token.intvalue);
      scan(&Token);
      return (n);
    case T_IDENT:
      id = findglob(Text);
      if (id == -1) {
        printf("Unknown variable");
        exit(1);
      }
      n = mkastleaf(A_IDENT, id);
      break;
    default:
      fprintf(stderr, "syntax error on line %d, token %d\n", Line,
	      Token.token);
      exit(1);
    }
    scan(&Token);
    return (n);
}

static int arithop(int tokentype) {
  if (tokentype > T_EOF && tokentype < T_INTLIT)
    return(tokentype);
  printf("Syntax error, token %d", tokentype);
  exit(1);
}

static int OpPrec[] = {
  0, 10, 10,			// T_EOF, T_PLUS, T_MINUS
  20, 20, 30,			// T_STAR, T_SLASH, T_EXP
  30, 30,			// T_EQ, T_NE
  40, 40, 40, 40		// T_LT, T_GT, T_LE, T_GE
};

static int op_precedence(int tokentype) {
  int prec = OpPrec[tokentype];
  if (prec == 0) {
    fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
    exit(1);
  }
  return (prec);
}

struct ASTnode *binexpr(int ptp) {
  struct ASTnode *left, *right;
  int tokentype;
  left = primary();
  tokentype = Token.token;
  if (tokentype == T_SEMI)
    return (left);
  while (op_precedence(tokentype) > ptp) {
    scan(&Token);
    right = binexpr(OpPrec[tokentype]);
    left = mkastnode(arithop(tokentype), left, right, 0);
    tokentype = Token.token;
    if (tokentype == T_SEMI)
      return (left);
  }
  
  return (left);
}
