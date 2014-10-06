export PATH := ../bin:${PATH}
.PRECIOUS: %.out

bin:
	cd ../bin;make all

EMBEDDINGS=../embeddings/
%.reps: $(EMBEDDINGS)%.embeddings
	cp $(EMBEDDINGS)$*.embeddings .
	echo `wc -l $*.embeddings | tr -t ' ' '\t' | cut -f1` `head -1 $*.embeddings | awk '{print NF-1}'` > $*.header
	cat $*.header $*.embeddings > $@
	rm $*.header $*.embeddings

DSET=msr
%.result: %.reps
	offset $*.reps ../data/$(DSET).questions `wc -l ../data/$(DSET).questions`> $*.output 2> $*.unk
	cut -f4 $*.output > $*.out
	rm $*.output

	score.pl $*.out ../data/$(DSET).answers > $@
%.wordsim.result: %.reps
	wordsim $*.reps ../data/wordsim365.tab > $*.wsim.out 2> $*.wsim.unk

	rm $*.reps
	rho.py $*.wsim.out > $@
