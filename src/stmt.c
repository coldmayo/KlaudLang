#include "include/defs.h"
#include "include/data.h"
#include "include/funCall.h"

void printAss(void) {
  struct ASTnode *tree;
  int reg;
  match(T_PRINT, "krint");
  tree = binexpr(0);
  reg = genAST(tree, -1);
  genprintint(reg);
  genfreeregs();

  semi();
}

void varAssignment(void) {
  struct ASTnode *left, *right, *tree;
  int id;
  ident();
  if ((id = findglob(Text)) == -1) {
    printf("Undeclared variable");
    exit(1);
  }
  right = mkastleaf(A_LVIDENT, id);
  match(T_ASSIGN, "=");
  left = binexpr(0);
  tree = mkastnode(A_ASSIGN, left, right, 0);
  genAST(tree, -1);
  genfreeregs();
  semi();
}

void statements(void) {

  while (1) {
    switch (Token.token) {
    case T_PRINT:
      printAss();
      break;
    case T_INT:
      var_declaration();
      break;
    case T_IDENT:
      varAssignment();
      break;
    case T_EOF:
      return;
    default:
      printf("Syntax error, token, %d", Token.token);
      exit(1);
    }
  }
}
