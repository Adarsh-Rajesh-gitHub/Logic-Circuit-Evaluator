set -e
gcc -std=c11 -O2 -Wall -Wextra src/Parser.c src/function.c -o hw2 -lm