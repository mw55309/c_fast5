Compile (tested on Ubuntu):

gcc -I/usr/include f5.c -L/usr/lib/i386-linux-gnu/ -lhdf5 -o f5

Run:

f5 omi1_110414_MVA_3719_1_ch222_file26_strand.fast5

What does it do?

Checks for existence of /Analyses/Basecall_2D_000/BaseCalled_2D, and if it exists, prints /Analyses/Basecall_2D_000/BaseCalled_2D/Fastq to STDOUT
