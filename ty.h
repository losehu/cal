#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_len 60
char ans[max_len];
int keep_point = 10;
void Add(char *ch1, char *ch2, char *ch3);
void add_sign(char a[], char sign);
void cut(char *a, int mode);//去首多余0，mode=1去小数点
void Div(char *ch1, char *ch2, char *ch3);
void fun2(char *str); //翻转字符串
void Minus(char *ch1, char *ch2, char *ch3);
void add_reduce(char a[]);//给无符号数加负号
void add_plus(char a[]);//正数加正号
void cheng(char a[], char b[], char *result);
void cut_plus(char a[]);//去除正号
void cut_sign(char a[]);//去除任意标点
int cmp_char(char a[], char b[]);//比较大小
void chu(char aa[], char bb[], char *result);
int cmp(char *ch1, char *ch2);
int change(int a);//结果模转数
void divide(char a[], char b[], char ans1[]);
int find_point(char a[], int mode);//小数点下标，找不到0，mode=1找到多个返回-1
void jia(char a[], char b[], char *result);
void jian(char a[], char b[], char *result);
int max(int a, int b);//最大值
void mid(const char a[], int start, int end, char *result);
void substract(char a[], char b[]);    //进行减法操作
void exact_decimal(char *a) {
    int local_point = find_point(a, 0);
    int a_len = (int) strlen(a);
    if (local_point == 0) //没找到小数点
    {
        a[a_len] = '.';
        for (int i = 1 + a_len; i <= keep_point + a_len; i++)
            a[i] = '0';
        a[a_len + keep_point + 1] = '\0';
    } else {
        int point_num = a_len - local_point - 1;
        if (keep_point >= point_num) {
            for (int i = 0; i < keep_point - point_num; i++)
                a[a_len + i] = '0';
            a[a_len + keep_point - point_num] = '\0';
        } else {
            int cnt = point_num - keep_point, add_up = 0;
            int sign = local_point + point_num - 2;
            if (a[local_point + point_num - 1] >= '5')add_up = 1;
            while (add_up == 1 && a[sign] != '.') {
                if (a[sign] < '9')a[sign]++, add_up = 0;
                else a[sign] = '0';
                cnt--;
                sign--;
            }
            a[1 + local_point + keep_point] = '\0';
            char c[5] = "+1";
            if (add_up) jia(a, c, a);
            exact_decimal(a);
        }
    }
}
void add_sign(char a[], char sign) {
    int d = (int) strlen(a);
    for (int i = d; i >= 1; i--) {
        a[i] = a[i - 1];
    }
    a[0] = sign;
    a[d + 1] = '\0';
}
int change(int a) {
    if (a > 0)return 1;
    else if (a < 0)return -1;
    else return 0;
}
void mid(const char a[], int start, int end, char *result) {
    memset(result, 0, sizeof(*result));
    for (int i = start; i <= end; i++) {
        result[i - start] = a[i];
    }
    result[end - start + 1] = '\0';
}
int cmp_char(char a[], char b[]) {
    int a_len = (int) strlen(a), b_len = (int) strlen(b);
    char a_cmp[a_len], b_cmp[b_len];
    int a_point = find_point(a, 0), b_point = find_point(b, 0);
    if (a_point == 0)a_point = (int) strlen(a);
    if (b_point == 0)b_point = (int) strlen(b);
    if (a_point > b_point)return 1;
    else if (a_point < b_point)return -1;
    else {
        mid(a, 0, a_point - 1, a_cmp);
        mid(b, 0, b_point - 1, b_cmp);
        if (strcmp(a_cmp, b_cmp) == 0)//整数部分完全相同
        {
            if (a_point == a_len) {
                if (b_point == b_len)return 0;
                else return -1;
            } else {
                if (b_point == b_len)return 1;
                else {
                    mid(a, a_point + 1, a_len - 1, a_cmp);
                    mid(b, b_point + 1, b_len - 1, b_cmp);
                    return change(strcmp(a_cmp, b_cmp));
                }
            }
        } else {
            mid(a, 0, a_point - 1, a_cmp);
            mid(b, 0, b_point - 1, b_cmp);
            return change(strcmp(a_cmp, b_cmp));
        }
    }
}
int max(int a, int b) {
    return a > b ? a : b;
}
void cut(char *a, int mode) {
    int cnt0_start = 0, cnt0_end = 0, result_sign = 1;
    if (a[1] == '0' && a[2] != '.') {
        cnt0_start++;
        for (int i = 2; a[i] == '0' && a[i + 1] != '.'; i++) {
            cnt0_start++;
        }
    }
    if (!mode) {
        for (int i = (int) strlen(a) - 1; a[i] == '0'; i--) {
            if (a[i - 1] != '.')cnt0_end++;
        }
    } else {
        if (find_point(a, 0)) {
            for (int i = (int) strlen(a) - 1; a[i] == '0' || a[i] == '.'; i--) {
                cnt0_end++;
                if (a[i] == '.')break;
            }
        }
    }
    for (int i = cnt0_start + 1; i < (int) strlen(a) - cnt0_end; i++) {
        a[result_sign++] = a[i];
    }
    a[(int) strlen(a) - cnt0_start - cnt0_end] = '\0';
}
int find_point(char a[], int mode) {
    int a_len = (int) strlen(a);
    if (!mode) {
        for (int i = 0; i < a_len; i++) {
            if (a[i] == '.')return i;
        }
    } else {
        int flag = 1;
        int local = 0;
        for (int i = 0; i < a_len; i++) {
            if (a[i] == '.' && flag) {
                local = i;
                flag = 0;
            } else if (a[i] == '.' && !flag) {
                return -1;
            }
        }
        return local;
    }
    return 0;
}
void jia(char a[], char b[], char *result) {
    add_plus(a);
    add_plus(b);
    char sign = a[0];
    if (a[0] != b[0]) {
        if (a[0] == '+') {
            cut_sign(a);
            cut_sign(b);
            jian(a, b, result);
            return;
        } else {
            cut_sign(a);
            cut_sign(b);
            jian(b, a, result);
            return;
        }
    }
    int a_len = (int) strlen(a), b_len = (int) strlen(b);
    int a_point = find_point(a, 0), b_point = find_point(b, 0);
    if (!a_point) {
        a_point = a_len;
        a[a_point] = '.';
        a[a_point + 1] = '0';
        a[a_point + 2] = '\0';
    }
    if (!b_point) {
        b_point = b_len;
        b[b_point] = '.';
        b[b_point + 1] = '0';
        b[b_point + 2] = '\0';
    }
    cut(a, 0);
    cut(b, 0);
    a_point = find_point(a, 0), b_point = find_point(b, 0);
    a_len = (int) strlen(a);
    b_len = (int) strlen(b);
    int result_len = 1 + max(a_point, b_point) + max(a_len - a_point, b_len - b_point);
    memset(result, 48, sizeof(*result));
    int a_sign = a_len - 1, b_sign = b_len - 1, add = 0;
    for (int i = result_len - 1; i >= 1; i--) {
        if (i >= result_len - abs(a_len - a_point - b_len + b_point)) {
            if (a_len - a_point > b_len - b_point) {
                result[i] = a[a_sign--];
            } else result[i] = b[b_sign--];
        } else if (i == max(a_point + 1, b_point + 1)) {
            a_sign--;
            b_sign--;
        } else if (a[a_sign] != sign && b[b_sign] != sign || i > max(a_point + 1, b_point + 1)) {
            result[i] = (char) ((a[a_sign] + b[b_sign] - 96 + add) % 10 + 48);
            add = (a[a_sign--] + b[b_sign--] - 96 + add) / 10;
        } else if (a[a_sign] != sign && b[b_sign] == sign) {
            result[i] = (char) ((a[a_sign] - 48 + add) % 10 + 48);
            add = (a[a_sign--] - 48 + add) / 10;
        } else if (a[a_sign] == sign && b[b_sign] != sign) {
            result[i] = (char) ((b[b_sign] - 48 + add) % 10 + 48);
            add = (b[b_sign--] - 48 + add) / 10;
        } else {
            result[i] = (char) ((add) % 10 + 48);
        }
    }
    result[0] = sign;
    result[1 + max(a_point, b_point)] = '.';
    result[result_len] = '\0';
    cut(result, 0);
    strcpy(ans, result);
}
void add_plus(char a[]) {
    if (a[0] != '+' && a[0] != '-') {
        int a_len = (int) strlen(a);
        a[a_len] = '\0';
        for (int i = a_len; i >= 1; i--) {
            a[i] = a[i - 1];
        }
        a[0] = '+';
        a[a_len + 1] = '\0';
    }
}
void add_reduce(char a[]) {
    if (a[0] != '+' && a[0] != '-') {
        unsigned int a_len = (int) strlen(a);
        a[a_len] = '\0';
        for (unsigned int i = a_len; i >= 1; i--) {
            a[i] = a[i - 1];
        }
        a[0] = '-';
        a[a_len + 1] = '\0';
    }
}
void cut_plus(char a[]) {
    if (a[0] == '+') {
        unsigned int a_len = (int) strlen(a);
        for (int i = 0; i < a_len - 1; i++) {
            a[i] = a[i + 1];
        }
        a[a_len - 1] = '\0';
    }
}
void cut_sign(char a[]) {
    if (a[0] == '+' || a[0] == '-') {
        int d = (int) strlen(a);
        for (int i = 0; i < d - 1; i++) a[i] = a[i + 1];
        a[d - 1] = '\0';
        return;
    } else return;
}
void jian(char a[], char b[], char *result) {
    add_plus(a);
    add_plus(b);
    if (a[0] != b[0]) {
        if (a[0] == '+') {
            cut_sign(b);
            jia(a, b, result);
            return;
        } else {
            cut_sign(b);
            add_reduce(b);
            jia(a, b, result);
            return;
        }
    }
    char sign;
    int a_len = (int) strlen(a), b_len = (int) strlen(b);
    int a_point = find_point(a, 0), b_point = find_point(b, 0);
    if (!a_point) {
        a_point = a_len;
        a[a_point] = '.';
        a[a_point + 1] = '0';
        a[a_point + 2] = '\0';
    }
    if (!b_point) {
        b_point = b_len;
        b[b_point] = '.';
        b[b_point + 1] = '0';
        b[b_point + 2] = '\0';
    }
    cut(a, 0);
    cut(b, 0);
    a_len = (int) strlen(a);
    b_len = (int) strlen(b);
    if (a[0] == '-') {
        int flag;
        if (b[0] == '+') flag = 1;
        else flag = 0;
        cut_sign(a);
        cut_sign(b);
        if (cmp_char(b, a) == 1) {
            add_reduce(a);
            if (flag)add_plus(b);
            else add_reduce(b);
            char temp[max_len];
            strcpy(temp, a);
            strcpy(a, b);
            strcpy(b, temp);
            a[b_len] = '\0';
            b[a_len] = '\0';
            sign = '+';
        } else {
            add_reduce(a);
            if (flag)add_plus(b);
            else add_reduce(b);
            sign = '-';
        }
    } else {
        int flag;
        if (b[0] == '+') flag = 1;
        else flag = 0;
        if (cmp_char(b, a) == 1) {
            add_plus(a);
            if (flag)add_plus(b);
            else add_reduce(b);
            char temp[max_len];
            strcpy(temp, a);
            strcpy(a, b);
            strcpy(b, temp);
            a[b_len] = '\0';
            b[a_len] = '\0';
            sign = '-';
        } else {
            add_reduce(a);
            if (flag)add_plus(b);
            else add_reduce(b);
            sign = '+';
        }
    }
    a_len = (int) strlen(a), b_len = (int) strlen(b);
    a_point = find_point(a, 0), b_point = find_point(b, 0);
    int result_len = max(a_point, b_point) + max((a_len - a_point), (b_len - b_point));
    memset(result, 48, sizeof(*result));
    int a_sign = a_len - 1, b_sign = b_len - 1, reduce = 0;
    for (int i = result_len - 1; i >= 1; i--) {
        if (i >= result_len - abs((a_len - a_point - b_len + b_point))) {
            if (a_len - a_point > b_len - b_point) {
                result[i] = a[a_sign--];
            } else {
                result[i] = (char) (106 - reduce - b[b_sign--]);
                reduce = 1;
            }
        } else if (i == max(a_point, b_point)) {
            a_sign--;
            b_sign--;
        } else if (a[a_sign] != a[0] && b[b_sign] != b[0] || i > max(a_point, b_point)) {
            result[i] = (char) ((a[a_sign] + 10 - b[b_sign] - reduce) % 10 + 48);
            reduce = 1 - (a[a_sign--] + 10 - b[b_sign--] - reduce) / 10;
        } else if (a[a_sign] != a[0] && b[b_sign] == b[0]) {
            result[i] = (char) ((a[a_sign] - 48 + 10 - reduce) % 10 + 48);
            reduce = 1 - (a[a_sign--] - 48 + 10 - reduce) / 10;
        } else if (a[a_sign] == a[0] && b[b_sign] != b[0]) {
            result[i] = (char) ((b[b_sign] - 48 + 10 - reduce) % 10 + 48);
            reduce = 1 - (b[b_sign--] - 48 + 10 - reduce) / 10;
        } else {
            result[i] = (char) (10 - reduce + 48);
        }
    }
    result[0] = sign;
    result[max(a_point, b_point)] = '.';
    result[result_len] = '\0';
    cut(result, 0);
    strcpy(ans, result);
}
void fun2(char *str) {
    int len = (int) strlen(str);
    char temp;
    for (int i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
    str[len] = '\0';
}
void cheng(char a[], char b[], char *result) {
    add_plus(a);
    add_plus(b);   //正数加正号，实战可以去除
    int a_len = (int) strlen(a), b_len = (int) strlen(b);
    int a_point = find_point(a, 0), b_point = find_point(b, 0);
    if (!a_point) {
        a_point = a_len;
        a[a_point] = '.';
        a[a_point + 1] = '0';
        a[a_point + 2] = '\0';
    }
    if (!b_point) {
        b_point = b_len;
        b[b_point] = '.';
        b[b_point + 1] = '0';
        b[b_point + 2] = '\0';
    }
    cut(a, 1);
    cut(b, 1);
    char sign;
    int point_len = 0;
    int a_point1 = find_point(a, 0);
    if (!a_point1)point_len += 0;
    else {
        point_len += (int) strlen(a) - a_point1 - 1;
    }
    a_point1 = find_point(b, 0);
    if (!a_point1)point_len += 0;
    else {
        point_len += (int) strlen(b) - a_point1 - 1;
    }
    if (a[0] == b[0] || (a[0] >= '0' && a[0] <= '9' && b[0] == '+') || (b[0] >= '0' && b[0] <= '9' && a[0] == '+'))
        sign = '+';
    else sign = '-';
    a_point = find_point(a, 0), b_point = find_point(b, 0);
    if (a_point) {
        for (int i = a_point; i < (int) strlen(a) - 1; i++)a[i] = a[i + 1];
        a[(int) strlen(a) - 1] = '\0';
    }
    if (b_point) {
        for (int i = b_point; i < (int) strlen(b) - 1; i++)b[i] = b[i + 1];
        b[(int) strlen(b) - 1] = '\0';
    }
    cut_sign(a);
    cut_sign(b);
    a_len = (int) strlen(a);
    b_len = (int) strlen(b);
    int c[a_len + b_len + 2];
    memset(c, 0, sizeof(c));
    fun2(a);
    fun2(b);
    if (strcmp(a, "0") == 0 || strcmp(b, "0") == 0) {
        strcpy(result, "+0");
        return;
    }
    for (int i = 0; i < a_len; i++)
        for (int j = 0; j < b_len; j++) {
            c[i + j] += (a[i] - 48) * (b[j] - 48);       //运算（这个就有一点复杂了）
            c[i + j + 1] += c[i + j] / 10;    //保证每一位的数都只有一位，并进位
            c[i + j] = c[i + j] % 10;
        }
    int l = a_len + b_len - 1;    //l是结果的最高位数
    if (c[l] > 0) l++;     //保证最高位数是对的
    while (c[l - 1] >= 10) {
        c[l] = c[l - 1] / 10;
        c[l - 1] %= 10;
        l++;
    }
    while (c[l - 1] == 0 && l > 1) l--;    //while去零法
    int add_zero = 0;
    if (point_len >= l) add_zero = point_len - l + 1;
    for (int i = 0; i < strlen(result); i++)result[i] = '0';
    for (int i = 0; i < l + add_zero; i++) result[i] = (char) (c[i] + 48);
    result[l + add_zero] = sign;
    result[l + 1 + add_zero] = '\0';
    fun2(result);
    if (point_len) {
        for (int i = l + 1 + add_zero; i >= l - point_len + 2 + add_zero; i--) {
            result[i] = result[i - 1];
        }
        result[l - point_len + 1 + add_zero] = '.';
        result[l + 2 + add_zero] = '\0';
    }
    strcpy(ans, result);
}
int lleenn;
void Add(char *ch1, char *ch2, char *ch3) {
    int len1 = (int) strlen(ch1), len2 = (int) strlen(ch2), len3, i, tmp, num1[lleenn], num2[lleenn], num3[lleenn];
    memset(num1, 0, sizeof(num1));
    memset(num2, 0, sizeof(num2));
    memset(num3, 0, sizeof(num3));
    for (i = len1 - 1; i >= 0; i--) num1[len1 - 1 - i] = ch1[i] - 48;
    for (i = len2 - 1; i >= 0; i--) num2[len2 - 1 - i] = ch2[i] - 48;
    i = 0, tmp = 0, len3 = len1 > len2 ? len1 : len2;
    while (i < len3) {
        num3[i] = num1[i] + num2[i] + tmp;
        tmp = 0;
        if (num3[i] >= 10) {
            tmp = num3[i] / 10;
            num3[i] %= 10;
        }
        i++;
    }
    if (tmp != 0) {
        num3[i] = tmp;
        i++;
    }
    len3 = i;
    for (i = len3 - 1; i >= 0; i--) ch3[len3 - 1 - i] = (char) (num3[i] + 48);
    ch3[len3] = '\0';
}
void Minus(char *ch1, char *ch2, char *ch3) {
    int i, tmp, len1 = (int) strlen(ch1), len2 = (int) strlen(ch2), len3, num1[lleenn], num2[lleenn], num3[lleenn];
    memset(num1, 0, sizeof(num1));
    memset(num2, 0, sizeof(num2));
    memset(num3, 0, sizeof(num3));
    for (i = 0; i < len1; i++) num1[len1 - 1 - i] = ch1[i] - '0';
    for (i = 0; i < len2; i++) num2[len2 - 1 - i] = ch2[i] - '0';
    i = 0, tmp = 0, len3 = len1 > len2 ? len1 : len2;
    while (i < len3) {
        num3[i] = num1[i] - num2[i] - tmp;
        if (num3[i] < 0) {
            num3[i] += 10, tmp = 1;
        } else tmp = 0;
        i++;
    }
    while (len3 > 1 && num3[len3 - 1] == 0) len3--;
    for (i = 0; i < len3; i++) ch3[i] = (char) (num3[len3 - 1 - i] + '0');
    ch3[len3] = '\0';
}
int cmp(char *ch1, char *ch2) {
    int i, len1 = (int) strlen(ch1), len2 = (int) strlen(ch2);
    if (len1 > len2) return 1;
    if (len2 > len1) return -1;
    for (i = 0; i < len1; i++) {
        if (ch1[i] > ch2[i]) return 1;
        if (ch1[i] < ch2[i]) return -1;
    }
    return 0;
}
void Div(char *ch1, char *ch2, char *ch3) {
    int i, len1, len2, tmp;
    char ch4[lleenn], ch5[lleenn];
    ch3[0] = '0', ch3[1] = '\0';
    while (cmp(ch1, ch2) >= 0) {
        len1 = (int) strlen(ch1), len2 = (int) strlen(ch2);
        ch2[len2] = '\0';
        ch1[len1] = '\0';
        tmp = len1 - len2 - 1 > 0 ? len1 - len2 - 1 : 0;
        ch4[0] = '1';
        memcpy(ch5, ch2, (len2 + 1) * sizeof(char));
        for (i = 0; i < tmp; i++) {
            ch4[1 + i] = '0', ch5[len2 + i] = '0';
        }
        ch4[1 + i] = '\0';
        ch5[len2 + i] = '\0';
        Add(ch3, ch4, ch3);   // ch3 += ch4;
        Minus(ch1, ch5, ch1);   // ch1 -= ch5;
    }
}
void chu(char aa[], char bb[], char *result) {
    char a[(int) strlen(aa) + 1], b[(int) strlen(bb) + 1];
    strcpy(a, aa);
    strcpy(b, bb);
    add_plus(a);
    add_plus(b);
    char sign;
    if (a[0] == b[0] || (a[0] >= '0' && a[0] <= '9' && b[0] == '+') ||
        (b[0] >= '0' && b[0] <= '9' && a[0] == '+'))
        sign = '+';
    else sign = '-';
    cut(a, 1);
    cut(b, 1);
    cut_sign(a);
    cut_sign(b);
    int a_point = find_point(a, 0), b_point = find_point(b, 0);
    if (a_point || b_point) {
        int len1 = (int) strlen(a), len2 = (int) strlen(b);
        int point_len;
        if (a_point == 0) {
            point_len = (int) strlen(b) - b_point - 1;
            for (int i = len1; i < len1 + point_len; i++) {
                a[i] = '0';
            }
            a[len1 + point_len] = '\0';
            for (int i = b_point; i < len2 - 1; i++) {
                b[i] = b[i + 1];
            }
            b[len2 - 1] = '\0';
        } else if (b_point == 0) {
            point_len = (int) strlen(a) - a_point - 1;
            for (int i = len2; i < len2 + point_len; i++) {
                b[i] = '0';
            }
            b[len2 + point_len] = '\0';
            for (int i = a_point; i < len1 - 1; i++) {
                a[i] = a[i + 1];
            }
            a[len1 - 1] = '\0';
        } else {
            //  point_len = max(len1 - a_point, len2 - b_point) - 1;
            for (int i = a_point; i < len1 - 1; i++) {
                a[i] = a[i + 1];
            }
            a[len1 - 1] = '\0';
            for (int i = b_point; i < len2 - 1; i++) {
                b[i] = b[i + 1];
            }
            b[len2 - 1] = '\0';
            if (len1 - a_point > len2 - b_point) {
                for (int i = len2 - 1; i < len2 + abs(len1 - a_point - len2 + b_point) - 1; i++) {
                    b[i] = '0';
                }
                b[len2 + abs(len1 - a_point - len2 + b_point) - 1] = '\0';
            } else {
                for (int i = len1 - 1; i < len1 + abs(len1 - a_point - len2 + b_point) - 1; i++) {
                    a[i] = '0';
                }
                a[len1 + abs(len1 - a_point - len2 + b_point) - 1] = '\0';
            }
        }
    }
    lleenn = max((int) strlen(a), (int) strlen(b)) + keep_point + 2 + 5;
    memset(result, 0, sizeof(*result));
    while (a[0] == '0') {
        for (int i = 0; i < (int) strlen(a); i++)
            a[i] = a[i + 1];
    }
    while (b[0] == '0') {
        for (int i = 0; i < (int) strlen(b); i++)
            b[i] = b[i + 1];
    }
    if (a[0] == '\0') a[0] = '0';
    if (b[0] == '\0') b[0] = '0';
    Div(a, b, result);
    add_sign(result, sign);
    if (a[0] != '0') {
        char tmp[keep_point + 2 + 10];
        divide(a, b, tmp);
        strcat(result, tmp);
        strcpy(ans, result);
        return;
    } else {
        strcpy(ans, result);
        return;
    }
}
void substract(char a[], char b[]) {
    if (strcmp(a, b) == 0) {
        strcpy(a, "0");
        return;
    }
    fun2(a);
    fun2(b);
    for (int i = 0; i < (int) strlen(b); i++) {
        if (a[i] >= b[i]) {
            a[i] = (char) (a[i] - b[i] + '0');
        } else {
            int k = 1;
            while (a[i + k] == '0') {
                a[i + k] = '9';
                k++;
            }
            a[i + k] = (char) (a[i + k] - '1' + '0');
            a[i] = (char) (a[i] - '0' + 10 - (b[i] - '0') + '0');
        }
    }
    int i;
    for (i = (int) strlen(a) - 1; a[i] == '0'; i--) {}
    if (i != (int) strlen(a) - 1)a[i + 1] = '\0';
    fun2(a);
    fun2(b);
}
void divide(char a[], char b[], char ans1[]) {
    ans1[keep_point + 2 + 10] = '\0';
    ans1[0] = '.';
    int sign = 1;
    for (int i = 0; i < keep_point + 2 + 1; i++) {
        int d = (int) strlen(a);
        a[d] = '0';
        a[d + 1] = '\0';
        int t = 0;
        while (cmp(a, b) >= 0) {
            substract(a, b);
            t++;
        }
        ans1[sign++] = (char) (t + '0');
        if (a[0] == '0')break;
    }
    ans1[sign] = '\0';
}