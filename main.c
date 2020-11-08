#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct expo Expo;
struct expo {
    char tag;
    int ex;
    int ey;
    int ez;
};

typedef struct node Node;
struct node {
    Expo EXPO;
    int COEF;
    Node* LINK;
};

typedef struct poly Polynomial;
struct poly {
    Node *NODE;
    Node *l;
    char* name[];
};

void POLYREAD(Polynomial *P, char* name[]);
void ZEROPOLY(Polynomial *P, char* name[]);
bool expGreaterThan(Expo alpha, Expo beta);
bool expEquals(Expo alpha, Expo beta);
bool expLessThan(Expo alpha, Expo beta);
void POLYADD(Polynomial *P, Polynomial *Q, char *name[]);

int main() {
    Polynomial *P = malloc(sizeof(Polynomial));
    Polynomial *Q = malloc(sizeof(Polynomial));
    char *name_1 = "addend_1";
    char *name_2 = "addend_2";
    char *name_3 = "sum";
    POLYREAD(P, &name_1);
    POLYREAD(Q, &name_2);
    POLYADD(P, Q, &name_3);
    Node* toPrint = Q->l->LINK;
    while (toPrint->EXPO.tag != '-') {
        printf("%d %d %d %.3f\n", toPrint->EXPO.ex, toPrint->EXPO.ey, toPrint->EXPO.ez, (float)toPrint->COEF);
        toPrint = toPrint->LINK;
    }
    return EXIT_SUCCESS;
}

void ZEROPOLY(Polynomial *P, char *name[]) {
    Node *node = malloc(sizeof(Node));
    P->l=node;
    strcpy((char *) P->name, (const char *) name);
    node->EXPO.tag = '-';
    node->EXPO.ex = 0;
    node->EXPO.ey = 0;
    node->EXPO.ez = 1;
    node->LINK = node;
}
void POLYREAD(Polynomial *P, char* name[]) {
    int number_of_terms, ex,ey,ez, coef;
    char string[1028];
    ZEROPOLY(P,name);
    scanf("%d\n", &number_of_terms);
    for (int i = 0; i < number_of_terms; i++) {
        sscanf(fgets(string, 1028, stdin), "%d %d %d %d\n", &ex,&ey,&ez,&coef);
        Node *temp_node = malloc(sizeof(Node));
        temp_node->EXPO.tag='+';
        temp_node->EXPO.ex = ex;
        temp_node->EXPO.ey = ey;
        temp_node->EXPO.ez = ez;
        temp_node->COEF = coef;
        Node *beta = P->l;
        Node *alpha = beta->LINK;
        while (expGreaterThan(alpha->EXPO, temp_node->EXPO)) {
            beta = alpha;
            alpha = alpha->LINK;
        }
        beta->LINK = temp_node;
        temp_node->LINK = alpha;
    }
}

bool expGreaterThan(Expo alpha, Expo beta) {
    if (alpha.ex > beta.ex) {
        return true;
    } else if (alpha.ex == beta.ex) {
        if (alpha.ey > beta.ey) {
            return true;
        } else if (alpha.ey == beta.ey) {
            if (alpha.ez > beta.ez) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool expEquals(Expo alpha, Expo beta) {
    if (alpha.ex == beta.ex && alpha.ey == beta.ey && alpha.ez == beta.ez) {
        return true;
    } else {
        return false;
    }
}

bool expLessThan(Expo alpha, Expo beta) {
    if (alpha.ex < beta.ex) {
        return true;
    } else if (alpha.ex == beta.ex) {
        if (alpha.ey < beta.ey) {
            return true;
        } else if (alpha.ey == beta.ey) {
            if (alpha.ez < beta.ez) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void POLYADD(Polynomial *P, Polynomial *Q, char *name[]) {
    Node *alpha = P->l->LINK;
    Node *beta =Q->l->LINK;
    Node *sigma = Q->l;
    while (true) {
        if (expLessThan(alpha->EXPO, beta->EXPO)) {
            sigma = beta;
            beta = beta->LINK;
        } else if (expEquals(alpha->EXPO, beta->EXPO)) {
            if (alpha->EXPO.tag == '-') {
                strcpy((char *) Q->name, (const char *) name);
                return;
            }
            beta->COEF += alpha->COEF;
            if (beta->COEF == 0)  {
                Node *tau = beta;
                sigma->LINK = beta->LINK;
                beta = beta->LINK;
                free(tau);
            } else {
                sigma = beta;
                beta = beta->LINK;
            }
            alpha = alpha->LINK;
        } else if (expGreaterThan(alpha->EXPO,beta->EXPO)) {
            Node *tau = malloc(sizeof(Node));
            tau->COEF = alpha->COEF;
            tau->EXPO = alpha->EXPO;
            sigma->LINK = tau;
            tau->LINK = beta;
            sigma = tau;
            alpha = alpha->LINK;
        }
    }
}