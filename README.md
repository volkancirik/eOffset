eOffset - Syntactic/Semantic Similarity Tasks for Word Vectors
=========

Basic benchmarks for Mikolov's work.

Here is a better and general version : http://wordvectors.org/suite.php

First unzip the sample word vector file :

    cd embeddings
    zcat rnn80.gz > rnn80.embeddings

Compile the binaries

    cd run
    make bin

Then run the bencmark

    make rnn80.result
   
Take a look at the results. It should be exactly the same as in [this paper](http://research.microsoft.com/pubs/189726/rvecs.pdf).
