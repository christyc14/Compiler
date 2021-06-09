C90 to MIPS Compiler


Two components:
- C to Python translator:
Build using the command:     make bin/c_compiler
Run using the command: bin/c_compiler --translate [source-file.c] -o [dest-file.py]
- C to MIPS compiler
Build using same command
Run using: bin/c_compiler -S [source-file.c] -o [dest-file.s]
