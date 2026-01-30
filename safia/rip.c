#include "rip.h"

/* while-only */
int ft_strlen(const char *s)
{
    int i = 0;
    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

/* valide en ignorant les espaces ' ' */
int is_valid(const char *s)
{
    int bal = 0;
    int i = 0;

    while (s[i])
    {
        char c = s[i];
        if (c == '(')
            bal++;
        else if (c == ')')
        {
            if (bal == 0)
                return 0;
            bal--;
        }
        i++;
    }
    return (bal == 0);
}

/* nb minimal de parenthèses à retirer (remplacer par ' ') */
int count_invalid(const char *s)
{
    int i = 0;
    int bal = 0;
    int extra_close = 0;

    while (s[i])
    {
        char c = s[i];
        if (c == '(')
            bal++;
        else if (c == ')')
        {
            if (bal > 0)
                bal--;
            else
                extra_close++;
        }
        i++;
    }
    /* bal = ouvrantes en trop ; extra_close = fermantes en trop */
    return bal + extra_close;
}

/*
  Backtracking sans for, avec "pruning" anti-doublons :
  à un même niveau (pos fixe), si on a s[i] == s[i-1], on saute pour éviter
  de supprimer deux fois la même parenthèse adjacente (dédoublonnage).
*/
void solve(char *s, int len, int max_remove, int removed, int pos)
{
    int i;

    if (removed > max_remove)
        return;

    if (removed == max_remove)
    {
        if (is_valid(s))
            puts(s); /* n'imprime que des solutions minimales */
        return;
    }

    i = pos;
    while (i < len)
    {
      if (s[i] == '(' || s[i] == ')')
      {
        if (!(i > pos && s[i] == s[i - 1]))
        {
            char save = s[i];
            s[i] = ' ';
            solve(s, len, max_remove, removed + 1, i + 1);
            s[i] = save;
        }
      }
      i++;
    }

}

int main(int ac, char **av)
{
    char        buf[MAX_LEN + 1];
    const char *in;
    int         len;
    int         i;
    int         max_remove;

    if (ac != 2)
        return 1;

    in = av[1];
    len = ft_strlen(in);
    if (len > MAX_LEN)
        return 1; /* protection simple */

    /* copie en while (pas de VLA, pas de malloc) */
    i = 0;
    while (i < len)
    {
        buf[i] = in[i];
        i++;
    }
    buf[len] = '\0';

    max_remove = count_invalid(buf);

    /* si déjà valide, il faut aussi l'imprimer (cf. énoncé/exemples) */
    if (max_remove == 0)
    {
        puts(buf);
        return 0;
    }

    solve(buf, len, max_remove, 0, 0);
    return 0;
}
