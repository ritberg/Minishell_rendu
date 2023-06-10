**TESTS**

**OK**
1. heredoc - segfault\
`cat << test | << test1 cat`\
`cat << coucou << g | cat << ''`

2. heredoc avec pipes - il faut créer plusieurs heredocs différents\
et pas écrire dans le même

3. `cat << d | wc > b`

4. les test du dossier `tester` ok

5. supprimer correctement les heredocs
il faut fermer heredoc dans le bon endroit, il reste.\
Le problème qui vient de là : si on change les permissions\
`chmod 000 .heredoc`, on pourra pas écrire dessus `cat << test`

**To do**
- `ls < myfile | cat > myfile | grep main < myfilel`
- tests de la feuille d'éval
