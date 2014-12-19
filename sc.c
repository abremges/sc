/* The MIT License

   Copyright (c) 2014 Andreas Bremges <andreas@cebitec.uni-bielefeld.de>

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include <inttypes.h>
#include <stdio.h>
#include <zlib.h>

#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[]) {
	if (argc > 1) {
		uintmax_t total_count = 0;
		uintmax_t total_length = 0;
		int i;
		for(i=1; i<argc; ++i) {
			uintmax_t count = 0;
			uintmax_t length = 0;
			gzFile fp = gzopen(argv[i], "r");
			kseq_t *seq = kseq_init(fp);
			while (kseq_read(seq) >= 0) {
				++count;
				length += seq->seq.l;
			}
			kseq_destroy(seq);
			gzclose(fp);
			total_count += count;
			total_length += length;
			printf("%" PRIuMAX " \t%" PRIuMAX "\t%s\n", count, length, argv[i]);
		}
		if (argc > 2) printf("%" PRIuMAX "\t%" PRIuMAX "\ttotal\n", total_count, total_length);
	} else {
		uintmax_t count = 0;
		uintmax_t length = 0;
		gzFile fp = gzdopen(fileno(stdin), "r");
		kseq_t *seq = kseq_init(fp);
		while (kseq_read(seq) >= 0) {
			++count;
			length += seq->seq.l;
		}
		kseq_destroy(seq);
		gzclose(fp);
		printf("%" PRIuMAX "\t%" PRIuMAX "\n", count, length);
	}
	return 0;
}
