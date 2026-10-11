#include <stdio.h>
#include <string.h>

char rebus[8][64];
int  word_len[8];
int  number;
int  left_part;
char letters[26];
int  count;
int  all[26];
int  used[10];
int  first_let[26];

int perevod(char* w, int n) {
    int v = 0;
    for (int i = 0; i < n; i++) {
        v = v * 10 + all[w[i] - 'A'];
    }
    return v;
}

int check(void) {
    int right = perevod(rebus[left_part], word_len[left_part]);
    int sum = 0;
    for (int i = 0; i < left_part; i++)
    {
        sum += perevod(rebus[i], word_len[i]);
        if (sum > right)
        {
            return 0;
        }
    }
    return sum == right;
}

int solve(int i) {
    if (i == count)
    {
        return check();
    }
    for (int d = 0; d <= 9; d++)
    {
        if (used[d])
        {
            continue;
        }
        if (d == 0 && first_let[letters[i] - 'A'])
        {
            continue;
        }
        used[d] = 1;
        all[letters[i] - 'A'] = d;
        if (solve(i + 1) == 1)
        {
            return 1;
        }
        used[d] = 0;
    }
    return 0;
}

void parsing(const char* stroka)
{
    number = 0;
    int i = 0;
    while (stroka[i])
    {
        while (stroka[i] == ' ')
        {
            i++;
        }
        if (stroka[i] == 0)
        {
            break;
        }

        int k = 0;
        while (stroka[i] >= 'A' && stroka[i] <= 'Z')
        {
            rebus[number][k++] = stroka[i++];
        }
        if (k > 0)
        {
            word_len[number] = k;
            number++;
        }

        while (stroka[i] == ' ')
        {
            i++;
        }
        if (stroka[i] == '+' || stroka[i] == '=')
        {
            i++;
        }
    }
    left_part = number - 1;
}

char* mainpart(const char* stroka)
{
    static char ans[512];

    parsing(stroka);
    if (number < 3 || number > 8)
    {
        return NULL;
    }

    count = 0;
    for (int wi = 0; wi < number; wi++)
    {
        for (int ci = 0; ci < word_len[wi]; ci++)
        {
            char ch = rebus[wi][ci];
            int alr = 0;
            for (int j = 0; j < count; j++)
            {
                if (letters[j] == ch)
                {
                    alr = 1; break;
                }
            }
            if (!alr)
            {
                letters[count++] = ch;
            }
        }
    }

    for (int i = 0; i < 26; i++)
    {
        all[i] = -1;
        first_let[i] = 0;
    }
    for (int i = 0; i < 10; i++)
    {
        used[i] = 0;
    }
    for (int i = 0; i < number; i++)
    {
        first_let[rebus[i][0] - 'A'] = 1;
    }

    if (!solve(0))
    {
        return NULL;
    }

    int p = 0;
    for (int i = 0; stroka[i]; i++)
    {
        if (stroka[i] >= 'A' && stroka[i] <= 'Z')
        {
            ans[p++] = '0' + all[stroka[i] - 'A'];
        }
        else
        {
            ans[p++] = stroka[i];
        }
    }
    ans[p] = 0;
    return ans;
}

int main(int argc, char** argv)
{
    FILE* f = fopen("C:\\Users\\vladimir\\source\\PL\\PR2\\stroka.txt", "r");
    char line[512];

    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\r\n")] = 0;
        if (line[0] == 0)
        {
            continue;
        }

        char* res = mainpart(line);
        if (res) {
            printf("%s\n", res);
        }
        else {
            printf("not solution\n");
        }
    }
    fclose(f);
    return 0;
}