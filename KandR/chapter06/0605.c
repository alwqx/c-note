/* page 121 6.5 Self-referential Structure */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100


struct tnode{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while(getword(word, MAXWORD) != EOF)
        if(isalpha(word[0]))
            root = addtree(root, word);
        
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
/* addtree: add node w to p or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if(p == NULL){
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }else if((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if(cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    
    return p;
}

/* treeprint: print tree in order */
void treeprint(struct tnode *p){
    if(p != NULL){
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc: create tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* getword: read next word fron input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while(isspace(c = getch()))
        ;
    if(c != EOF)
        *w++ = c;
    if(!isalpha(c)){
        *w = '\0';
        return c;
    }

    for(; --lim>0; w++)
        if(!isalnum(*w = getch())){
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 1000
static char buf[BUFSIZE];
static int bufp = 0;       /* next position in buf */

int getch(void){
    return (bufp>0)?buf[--bufp]:getchar();
}

void ungetch(int c){
    if(bufp>=BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* strdup: copy s to somewhere */
// char *strdup(char *s)
// {
//     char *p;

//     p = (char *) malloc(strlen(s) + 1);
//     if(p != NULL)
//         strcpy(p, s);
    
//     return p;
// }