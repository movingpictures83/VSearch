# VSearch
# Language: C++
# Input: TXT
# Output: PREFIX
# Tested with: PluMA 1.1, GCC 4.8.4
# Dependency: Qiime 2 2020.11, Conda 4.9.2

VSearch algorithm for nucleotide-based alignment (Rognes et al, 2016).

The input file is a TXT file of tab-delimited keyword-value pairs:

table: Table of sequences
sequences: Input sequences
referencesequences: Sequence database to which sequences are aligning (i.e. SILVA)
percidentity: Threshold percentage for identity to align

Output files will be generated using names that include the user-specified output prefix and percidentity:

prefix-new-ref-seqs-or-percidentity.qza: Aligned sequences 
prefix-table-or-percidentity.qza: Table of seequences
prefix-rep-seqs-or-percidentity.qza: Sequences


