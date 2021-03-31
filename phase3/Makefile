CXX		= g++ -std=c++11
CXXFLAGS	= -g -Wall
OBJS		= lexer.o string.o parser.o type.o symbol.o scope.o checker.o
PROG		= scc

all:		$(PROG)

$(PROG):	$(OBJS)
		$(CXX) -o $(PROG) $(OBJS)

clean:;		$(RM) $(PROG) core *.o
