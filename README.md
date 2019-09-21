# Welcome in Spire-Project.

It's aim is to provide a way to re-build a genom starting from casual reads of it's sections.

This program is part of a larger one and has the purpose of applying the so called 'flynn factorization' with some relative informations. My job was not to implement the factorization functions but to create a software capable of applying them to a large set of samples producing these informations. I was requested to do it specifically in C, cause the second section of the program was implemented through this lenguage. Tests and the program "sequential_program_main.c" and "run.c" are my products.

Following a description of how it works and how to run it.

# How it works
The program takes as first input a path to a location where the samples are contained. This location is a directory that I will call "bunch" for ease and has this structure.

>directory-bunch
  >subdirectory_samples1
    >file1.fasta
    >file2.fasta
    >file3.fasta
  >subdirectory_samples2
    >file4.fasta

The location must strictly respect this structure. The ".fasta" files contain the samples constisting of a set of "reads".

A "read" is a genom section made up of a identifying header and a body consisting of letters representing the four dna bases: A,G,C,T:

>header1
CGTTGCGGAAAGGTC

In each subdirectory and for each fasta file, a factorization file is created containing their reads substrings produced through one of the four possible factorization kinds, whose dimension is biased through the given maximum dimension given for them. The factorization process essentially breaks each read in substrings that respect some specific rules. Format of each read factorization is as the following:

>header1
[ "CGTTG" "CGG" "AAAGGTC" ]

For each factorization, a string describing the dimension of its factors (or substrings produced by the factorization process) is produced as the following:

>header1 5,3,7

It simply consists of the identifier header and dimensions of the read factors. Each factor dimension is called "fingerprint".

Finally a k-fingerprint file is created containing, for each fingerprint string, a set of strings as the following:

5 3 7 0 $ 0 0 0 0 $ >header1 0

It is made up of 4 sections. The first one before the first dollar contains the fingerprints, the second one a description of which factors have been produced through a second factorization (1 if yes, 0 if not) at the same positions of the fingerprint relative to each factor. The third section is the identifying header and the last one is the "iteration". This strings are produced through the concept of "rotating window". Consider the following set of fingerprints:

1,4,5,6,3,4,6

Suppose we have a window whose dimension is 4 (k-fingerprint stands of k as dimension of window applied to fingerprints). This window can only contain 4 fingerprints at a time and can move just one position to right for each iteration. At each iteration a substring made up of the contained fingerprints in the window is made. Let's see an example. Initially we have this state:

|1,4,5,6|,3,4,6   iteration 0

and the following is the subsection produced:

1,4,5,6

then the window moves of one position to right and we have the following state:

1,|4,5,6,3|,4,6    iteration 1

producing the string:

 4,5,6,3

and so on until the end.

Let's say we have the factor 'ACTGAC' produced after the first factorization process. In a second one it is broke into 'ACT' 'GAC'. We want to store the second break. We do that through 'flags' associated with them. These flags compose the second section of k-fingerprint. So if we have the following read:

>header1 'AGTCAGTATCT'

and we break it in a first factorization process in:
['AGT','CAGTA','TCT']
and again into another one:
['AGT','CA','GTA','TCT']
then we have the following fingerprints:

>header1 3,2,3,3

and having only one iteration(cause the window size is 4 and it can't move to right anymore), we have the following k-fingerprint:

   3 2 3 3      $ 0 1 1 0 $ >header1      0
|fingerprints|    |flags|            |iteration|

Why 0 1 1 0? Because the ones refer to 'CA', 'GTA' that have been produced in the second factorization process. Why iteration 0? Because window hasn't moved.

# How to run

To see the program in action enter into the directory, run "./run" in terminal. Give the path to the "testsample" (the same path of the directory in which you ran "./run"), select the factorization kind you want, define the dimension of the factors (30 or 50 are suggested), the k-fingerprint (4 is suggested). You will find all the results in the sample subdirectories.




