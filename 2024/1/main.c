#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 0x200
#define MAX_LST_SIZE 0x3e8

int cmp(const void *lhs, const void *rhs)
{
    const int *liptr = (const int *)lhs, *riptr = (const int *)rhs;
    return (*liptr > *riptr) - (*liptr < *riptr);
}

int *lower_bound(const int *lst, size_t size, int v)
{
    int *found = (int *)bsearch(&v, lst, size, sizeof(int), cmp);
    if (!found) return NULL;
    while (found != lst) {
        if (*found == v) --found;
        else return ++found;
    }
    return found;
}

int score(const int *lst, size_t size, int v)
{
    int *lower = lower_bound(lst, size, v);
    int result = 0;
    ptrdiff_t dist;

    if (lower == NULL) return 0;
    dist = lower - lst;
    while (lst[dist++] == v) {
        result += v;
    }
    return result;
}

int main(int argc, char **argv)
{
    char line[MAX_LENGTH];
    int line_count = 0;
    int l, r;
    int llst[MAX_LST_SIZE], rlst[MAX_LST_SIZE];
    int i;
    int acc = 0, score_acc = 0;

    while (fgets(line, MAX_LENGTH, stdin) != NULL) {
        sscanf(line, "%d%d", &l, &r);
        llst[line_count] = l;
        rlst[line_count] = r;
        ++line_count;
    }

    qsort(llst, line_count, sizeof(int), cmp);
    qsort(rlst, line_count, sizeof(int), cmp);

    for (i = 0; i < line_count; ++i) {
        acc += abs(llst[i] - rlst[i]);
        score_acc += score(rlst, line_count, llst[i]);
    }

    printf("%d %d\n", acc, score_acc);

    return 0;
}
