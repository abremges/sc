sc = sequence count
==
Quick & dirty hack to count #seqs and #bps in FastQ or FastA files, optionally gzipped.

Reads any files passed as arguments or, if none is specified, attempts to read from stdin.

Only dependency is kseq.h (included) from klib: https://github.com/attractivechaos/klib
