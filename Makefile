CC=gcc
CFLAGS=-Wall -O3

sc:sc.c kseq.h
	$(CC) $(CFLAGS) sc.c -o $@ -lz

clean:
	rm -fr gmon.out *.o ext/*.o a.out sc *~ *.a *.dSYM session*
