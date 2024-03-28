# Lexical Analyzer

### Overview

This script performs lexical analysis on a given source code file. It processes the input file to identify and classify tokens according to their type, such as identifiers, numbers, and various operators. 
The script can handle comments, ignore whitespace, and validate tokens to ensure they meet specific criteria.

### Features

- Comment Handling: Strips comments from the source code to focus on the lexical elements.
- File Operations: Reads from and writes to specified files, handling input and output of the lexical analysis.
- Token Identification: Recognizes and classifies various tokens like arithmetic operators, assignment operators, parentheses, numbers, keywords, and identifiers.
- Error Handling: Detects invalid tokens and provides appropriate error messages, halting execution when necessary.
- Display Options: Allows displaying the original or the cleaned (comments removed) source code based on command-line flags.
- Token Cataloging: Outputs a list of identified tokens along with their corresponding type codes.


### Output Files

1) input3.txt: Contains the source code with comments removed.
2) input4.txt: Lists the tokens identified along with a brief description.
3) input5.txt: Provides a comprehensive list of tokens and their classifications.

### Compilation

gcc Lex.c -o Lex
