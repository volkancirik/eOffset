all: offset wordsim

offset: check
	test -e ../src/$@ || (cd ../src/; gcc -O3 -o $@ $@.c -lm; )
	test -e $@ || ln -s ../src/$@ .
wordsim: check

	test -e ../src/$@ || (cd ../src/; gcc -O3 -o $@ $@.c -lm; )
	test -e $@ || ln -s ../src/$@ .
check:
	true

clean:
	-rm offset wordsim
