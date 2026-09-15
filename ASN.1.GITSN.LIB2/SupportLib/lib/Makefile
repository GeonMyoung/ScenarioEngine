all:
	for ccc in `ls *.a`; do \
	ar x $$ccc; \
	rm -f $$ccc; \
	done;
	ar rc libasn1gitsn.a *.o;
	rm -f *.o;

clean:
	rm -f *.a;
