CFLAGS=-Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

all: ticker

ticker: ticker.c
	gcc $(CFLAGS) ticker.c -o ticker

debug: CFLAGS += -g
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f  ticker
