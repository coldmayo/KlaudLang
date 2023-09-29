#include "include/defs.h"
#include "include/data.h"
#include "include/funCall.h"

void match(int t, char *what) {
  if (Token.token == t) {
    scan(&Token);
  } else {
    printf("%s expected on line %d\n", what, Line);
    exit(1);
  }
}

void semi(void) {
  match(T_SEMI, "@");
}

void ident(void) {
  match(T_IDENT, "identifier");
}