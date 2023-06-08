**TESTS**

**Done**
1. heredoc - segfault\
`cat << test  | << test1 cat`\
`cat << coucou << g | cat << ''`

2. heredoc avec pipes - il faut créer plusieurs heredocs différents\
et pas écrire dans le même

3. il faut fermer heredoc dans le bon endroit, il reste.\
Le problème qui vient de là : si on change les permissions `chmod 000 .heredoc`,\
on pourra pas écrire dessus `cat << test`

4. problème avec `cat << d| wc>b`

**To do**
- supprimer correctement les heredocs
- retester les signaux
- norminette
- tests de la feuille d'éval
