CFLAGS += -Wall
CFLAGS += -Wmissing-declarations
CC = gcc
# Uncomment to demo c99 parametric testing.

# Uncomment to disable setjmp()/longjmp().
#CFLAGS += -DGREATEST_USE_LONGJMP=0

# Uncomment to disable clock() / time.h.
#CFLAGS += -DGREATEST_USE_TIME=0

all: test_suite

test_suite: tests.o q.o
	${CC} -o $@ tests.o q.o ${CFLAGS} ${LDFLAGS}

tests.o: q.h greatest.h tests.c
	${CC} -c tests.c ${CFLAGS} ${LDFLAGS}

q.o: q.c
	${CC} -c q.c ${CFLAGS} ${LDFLAGS}

clean:
	rm -f example *.o *.core
