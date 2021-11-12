#include <stdio.h>
#include <stdlib.h>
#include"stack.h"
#include "ty.h"
#define C ' '
unsigned int express_len = 0;
int suan_cnt = 0;
char operator[50];
void operator_init() {
    operator[40] = 10;// (
    operator[41] = 10;// )
    operator[42] = 5; // *
    operator[47] = 5; // /
    operator[43] = 1; // +
    operator[45] = 1; // -
}
void removeLastZero(char *numstr) {
    if (NULL == strchr(numstr, '.'))
        return;
    unsigned int length = strlen(numstr);
    for (unsigned int i = length - 1; i > 0; --i) {
        if ('\0' == numstr[i]) {
            continue;
        } else if ('0' == numstr[i]) {
            numstr[i] = '\0';
        } else if ('.' == numstr[i]) {
            numstr[i] = '\0';
            break;
        } else {
            break;
        }
    }
}
void scan(char *a, int start, char *result) {
    express_len = 0;
    memset(result, 0, sizeof(*result));
    unsigned int cnt = 0, a_len = strlen(a);
    if (a[start] <= '9' && a[start] >= '0') {
        for (int i = start; (a[i] <= '9' && a[i] >= '0' || a[i] == '.') && i < a_len; i++) {
            result[cnt++] = a[i];
        }
    } else {
        if (a[start] == '(' || a[start] == ')' || a[start] == '*' || a[start] == '/') {
            result[cnt++] = a[start];
        } else if (a[start] == '+' || a[start] == '-') {
            if (a[start + 1] > '9' || a[start + 1] < '0') {
                result[cnt++] = a[start];
            } else {
                if (start > 0) {
                    if (a[start - 1] <= '9' && a[start - 1] >= '0' || a[start - 1] == ')') {
                        result[cnt++] = a[start];
                    } else {
                        result[cnt++] = a[start];
                        for (int i = start + 1; (a[i] <= '9' && a[i] >= '0' || a[i] == '.') && i < a_len; i++) {
                            result[cnt++] = a[i];
                        }
                    }
                } else {
                    result[cnt++] = a[start];
                    for (int i = start + 1; (a[i] <= '9' && a[i] >= '0' || a[i] == '.') && i < a_len; i++) {
                        result[cnt++] = a[i];
                    }
                }
            }
        }
    }
    result[cnt] = '\0';
    express_len += cnt;
}
int is_num(char *a) {
    unsigned int d = strlen(a);
    if (d == 1) {
        if (a[0] <= '9' && a[0] >= '0')return 1;
        else return 0;
    } else {
        for (int i = 1; i < d; i++) {
            if (!(a[i] <= '9' && a[i] >= '0' || a[i] == '.'))
                return 0;
        }
        return 1;
    }
}
int is_fuhao(char *a) {
    unsigned int d = strlen(a);
    if (d == 1) {
        if (a[0] <= '9' && a[0] >= '0')return 0;
        else return 1;
    } else return 0;
}
void add_char(char *result11, char *p) {
    strcat(result11, p);
    unsigned int result_len = strlen(result11);
    result11[result_len] = C;
    result11[result_len + 1] = '\0';
}
void exp_change(char express1[], char end[]) {
    char express[strlen(express1) + 1];
    strcpy(express, express1);
    unsigned int qq = strlen(express);
    if (is_num(express)) {
        strcpy(end, express);
    }
    initstack();
    for (int i = 0; i < qq; i++) {
        char a[3];
        if (express[i] == '(') {
            a[0] = '(';
            a[1] = '\0';
            push(a);
        } else if (express[i] == ')') {
            if (zhen == 0 || stack[zhen - 1][0] != '(') {
                strcpy(end, "=>?@A");
                return;
            } else if (stack[zhen - 1][0] == '(') {
                pop();
            }
        }
    }
    if (zhen) {
        strcpy(end, "=>?@A");
        return;
    }
    char express2[(int) strlen(express1) * 2];
    initstack();
    operator_init();
    char tmp[(int) strlen(express1) + 10];
    memset(express2, 0, sizeof(express2));
    char *fuhao = "0";
    for (int i = 0; i < qq; i++) {
        scan(express, i, tmp);
        if (is_num(tmp)) {
            add_char(express2, tmp);
        } else {
            if (strcmp(tmp, ")") != 0) {
                if (isEmpty()) fuhao = stack[zhen - 1];
                while (isEmpty() && operator[fuhao[0]] >= operator[tmp[0]] && fuhao[0] != '(') {
                    add_char(express2, fuhao);
                    pop();
                    if (isEmpty()) fuhao = stack[zhen - 1];
                }
                char a[80];
                strcpy(a, tmp);
                push(a);
            } else {
                if (isEmpty()) fuhao = stack[zhen - 1];
                while (isEmpty() && fuhao[0] != '(') {
                    add_char(express2, fuhao);
                    pop();
                    if (isEmpty()) fuhao = stack[zhen - 1];
                }
                if (isEmpty()) pop();
            }
        }
        i = i + (int) express_len - 1;
    }
    while (isEmpty()) {
        fuhao = stack[zhen - 1];
        add_char(express2, fuhao);
        if (isEmpty()) pop();
    }
    initstack();
    for (int i = 0; i < strlen(express2); i++) {
        memset(tmp, 0, sizeof(tmp));
        int cnt = 0, j;
        for (j = i; express2[j] != C && j < strlen(express2); j++) {
            tmp[cnt++] = express2[j];
        }
        tmp[cnt] = '\0';
        i = j;
        if (!is_fuhao(tmp)) {
            push(tmp);
        } else {
            if (zhen == 1) {
                fuhao = stack[zhen - 1];
                pop();
                if (tmp[0] == '-') {
                    add_reduce(fuhao);
                } else if (tmp[0] == '+') {}
                push(fuhao);
            } else if (zhen > 1) {
                fuhao = stack[zhen - 1];
                pop();
                if (tmp[0] == '+') {
                    jia(stack[zhen - 1], fuhao, fuhao);
                } else if (tmp[0] == '-') {
                    jian(stack[zhen - 1], fuhao, fuhao);
                } else if (tmp[0] == '*') {
                    cheng(stack[zhen - 1], fuhao, fuhao);
                } else if (tmp[0] == '/') {
                    if (atof(fuhao) == 0.0) {
                        strcpy(end, "B0DE");
                        return;
                    }
                    chu(stack[zhen - 1], fuhao, fuhao);
                }
                pop();
                suan_cnt++;
                push(fuhao);
            }
        }
    }
    strcpy(end, stack[zhen - 1]);
    removeLastZero(end);
    exact_decimal(end);
    strcpy(ans, end);
}

