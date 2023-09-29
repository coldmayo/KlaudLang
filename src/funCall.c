#include "include/defs.h"
#include "include/data.h"
#include "include/funCall.h"

void var_declaration(void) {
  
  match(T_INT, "int");
  ident();
  addglob(Text);
  genglobsym(Text);
  semi();
}