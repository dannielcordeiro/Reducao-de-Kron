#include <stdio.h>
#include <stdlib.h>

typedef struct complex_s {
    float real;
    float imaginary;
} complex ;


complex* multiplicar(complex* n1, complex* n2){
    complex* resposta = malloc(sizeof(complex));

    resposta->real = n1->real * n2->real - n1->imaginary * n2->imaginary;
    resposta->imaginary = n1->real * n2->imaginary + n2->real * n1->imaginary;

    return resposta;
}

complex* dividir(complex* n1, complex* n2){
    complex* resposta = malloc(sizeof(complex));

    resposta->real = (((n1->real)*(n2->real))+((n1->imaginary)*(n2->imaginary)))/(pow(n2->real,2)+pow(n2->imaginary,2));
    resposta->imaginary = (((n2->real)*(n1->imaginary))-((n1->real)*(n2->imaginary)))/(pow(n2->real,2)+pow(n2->imaginary,2));

    return resposta;
}

complex* subtrair(complex* n1, complex* n2){
    complex* resposta = malloc(sizeof(complex));

    resposta->real = n1->real - n2->real;
    resposta->imaginary = n1->imaginary - n2->imaginary;

    return resposta;
}

complex* montar(float real, float img){
    complex* c = malloc(sizeof(complex));

    c->real = real;
    c->imaginary = img;

    return c;
}

complex* calcularNovoElemento(complex* c1, complex* c2, complex* c3, complex* c4){
    complex* m = multiplicar(c2, c3);
    m = dividir(m, c4);
    m = subtrair(c1, m);

    return m;
}

complex*** montarMatriz(int n, int temReal){
    complex*** matriz = malloc(n * sizeof(complex**));

    for(int i = 0; i < n; i++){
        matriz[i] = malloc(n * sizeof(complex*));

        for(int j = 0; j < n; j++){
            float real = 0;
            float img;

            if(temReal){
                printf("Real %dx%d: ", i+1, j+1);
                scanf("%f", &real);
            }

            printf("Imaginario %dx%d: ", i+1, j+1);
            scanf("%f", &img);

            complex* c = montar(real, img);
            matriz[i][j] = c;
        }

    }

    return matriz;

}

char* formatComplex(complex* c){
    char* s = malloc(100 * sizeof(char));


    if(c->imaginary >= 0) {
        sprintf(s, "%.5f + %.5f j", c->real, c->imaginary);
    } else {
        sprintf(s, "%.5f %.5f j", c->real, c->imaginary);
    }

    return s;
}

void printMatriz(complex*** matriz, int n){
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
             printf("%s     ", formatComplex(matriz[i][j]));
        }
        printf("\n");
    }
}

complex*** reduzirMatriz(complex*** m, int pi, int pj, int n){
    complex*** novaMatriz = malloc((n-1) * sizeof(complex**));

    for(int i = 0; i < n; i++){
        if(i == pi){
            continue;
        }
        int iNovo = i > pi ? i-1 : i;

        novaMatriz[iNovo] = malloc((n-1) * sizeof(complex*));

        for(int j = 0; j < n; j++){
            if(j == pj){
                continue;
            }
            int jNovo = j > pj ? j-1 : j;
            complex* no = calcularNovoElemento(m[i][j], m[i][pj], m[pi][j], m[pi][pj]);

            novaMatriz[iNovo][jNovo] = no;
        }
    }

    return novaMatriz;
}

void calculoDeReducao(int n, complex*** matriz){
    printMatriz(matriz, n);

    int pi;
    int pj;


    printf("Linha do pivo: ");
    scanf("%d", &pi);
    printf("Coluna do pivo: ");
    scanf("%d", &pj);

    complex*** matrizReduzida = reduzirMatriz(matriz, pi-1, pj-1, n);
    printMatriz(matrizReduzida, n-1);
    printf("-----------------------------------------------------------");

    int continuar;
    printf("Deseja continuar reduzindo essa matriz? (0/1): ");
    scanf("%d", &continuar);
    if(continuar){
        calculoDeReducao(n-1, matrizReduzida);
    }

    return;
}

int main()
{
    int temReal;
    printf("Tem real? (0/1): ");
    scanf("%d", &temReal);

    int n;
    printf("Tamanho ta matriz nxn: ");
    scanf("%d", &n);

    complex*** matriz = montarMatriz(n, temReal);
    calculoDeReducao(n, matriz);

    return 0;
}
