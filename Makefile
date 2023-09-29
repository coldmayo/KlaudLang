SRCS= src/cg.c src/funCall.c src/expr.c src/gen.c src/main.c src/misc.c src/lex.c src/stmt.c src/symbol.c src/ast.c

compile: $(SRCS)
	cc -o comp1 -g $(SRCS)

clean:
	rm -f comp1 *.o *.s out

test: comp1 $(filename)
	./comp1 $(filename)
	cc -o out out.s
	./out