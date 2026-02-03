#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int read_file(const char *path, char *buf, size_t cap) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;
    size_t used = fread(buf, 1, cap - 1, f);
    buf[used] = '\0';
    fclose(f);
    return 1;
}

static void strip_trailing_ws(char *s) {
    int n = (int)strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r' || s[n-1] == ' ' || s[n-1] == '\t'))
        s[--n] = '\0';
}

int main() {
    const char *prog = "./hw2";

    const char *cases[] = { "input", "t1", "t2", "t3", "t4", "t5", "t6" };
    int ncases = (int)(sizeof(cases) / sizeof(cases[0]));

    
    const char *exp_input =
        "0 1 | 6 \n"
        "0 0 | 0 \n"
        "0 1 | 1 \n"
        "1 0 | 0 \n"
        "1 1 | 1";
    const char *exp_t1 =
        "0 1 | 3 \n"
        "0 0 | 0 \n"
        "0 1 | 0 \n"
        "1 0 | 1 \n"
        "1 1 | 1";
    const char *exp_t2 =
        "0 1 | 3 \n"
        "0 0 | 0 \n"
        "0 1 | 1 \n"
        "1 0 | 0 \n"
        "1 1 | 1";
    const char *exp_t3 =
        "0 | 1 \n"
        "0 | 0 \n"
        "1 | 1";
    const char *exp_t4 =
        "0 1 | 3 \n"
        "0 0 | 0 \n"
        "0 1 | 0 \n"
        "1 0 | 0 \n"
        "1 1 | 1";
    const char *exp_t5 =
        "0 1 | 3 \n"
        "0 0 | 0 \n"
        "0 1 | 1 \n"
        "1 0 | 1 \n"
        "1 1 | 0";
    const char *exp_t6 =
        "0 1 2 | 4 \n"
        "0 0 0 | 0 \n"
        "0 0 1 | 0 \n"
        "0 1 0 | 0 \n"
        "0 1 1 | 0 \n"
        "1 0 0 | 0 \n"
        "1 0 1 | 0 \n"
        "1 1 0 | 0 \n"
        "1 1 1 | 1";

    int fails = 0;

    for (int i = 0; i < ncases; i++) {
        char in_path[50], cmd[100];
        snprintf(in_path, sizeof(in_path), "testCases/%s.txt", cases[i]);

        snprintf(cmd, sizeof(cmd), "%s %s > out.txt", prog, in_path);
        int rc = system(cmd);

        char got[20000];
        if (!read_file("out.txt", got, sizeof(got))) {
            printf("fail %s could not read out.txt\n", cases[i]);
            fails++;
            continue;
        }
        strip_trailing_ws(got);
        char expbuf[20000];
        if (strcmp(cases[i], "input") == 0) {
            strcpy(expbuf, exp_input);
        }
        else if(strcmp(cases[i], "t1") == 0) {
            strcpy(expbuf, exp_t1);
        }
        else if(strcmp(cases[i], "t2") == 0) {
            strcpy(expbuf, exp_t2);
        }
        else if(strcmp(cases[i], "t3") == 0) {
            strcpy(expbuf, exp_t3);
        }
        else if(strcmp(cases[i], "t4") == 0) {
            strcpy(expbuf, exp_t4);
        }
        else if(strcmp(cases[i], "t5") == 0) {
            strcpy(expbuf, exp_t5);
        }
        else if(strcmp(cases[i], "t6") == 0) {
            strcpy(expbuf, exp_t6);
        }
        else {
            printf("No expected made for %s", cases[i]);
            continue;
        }
        strip_trailing_ws(expbuf);
        if (strcmp(got, expbuf) == 0) {
            printf("PASS %s\n", cases[i]);
        } else {
            printf("FAIL %s\n", cases[i]);
            printf("---- got ----\n%s\n", got);
            printf("---- exp ----\n%s\n", expbuf);
            fails++;
        }
    }

    printf("fails=%d\n", fails);
    return fails;
}