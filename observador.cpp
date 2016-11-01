#include "observador.h"

double** Observador::Mat_Aloc(int linhas, int colunas) {
    double **mat = NULL;

    mat = (double**)calloc(linhas, sizeof(double));

    assert(mat != NULL);

    for(int i=0; i<linhas; i++) {
        mat[i] = (double*)calloc(colunas, sizeof(double));
        assert(mat[i] != NULL);
    }

    return mat;
}

double** Observador::Observador::Mat_Free(int linhas, int colunas, double** mat) {
    if(mat == NULL) return NULL;

    for(int i=0; i<linhas; i++) {
        free(mat[i]);
    }
    free(mat);

    return NULL;
}

double** Observador::Mat_Mult(double **matrizA, int linhasMatrizA, int colunasMatrizA, \
    double **matrizB, int linhasMatrizB, int colunasMatrizB) {

    assert(colunasMatrizA == linhasMatrizB);

    double **matrizC = Mat_Aloc(linhasMatrizA, colunasMatrizB);
    double aux;

    for(int i=0; i<linhasMatrizA; i++) {
        for(int j=0; j<colunasMatrizB; j++) {
            matrizC[i][j]=0.0;
            aux=0;
            for(int k=0; k<linhasMatrizB; k++) {
                aux += matrizA[i][k] * matrizB[k][j];
            }
            matrizC[i][j]=aux;
        }
    }

    return matrizC;
}

double** Observador::Mat_MultEscalar(double **mat, int linhas, int colunas, int escalar) {
    double **matResul = Mat_Aloc(linhas, colunas);
    for(int i=0; i<linhas; i++) {
        for(int j=0; j<colunas; j++) {
            matResul[i][j] = mat[i][j] * escalar;
        }
    }
    return matResul;
}

double** Observador::Mat_Sum(double **matA, double **matB, int linhas, int colunas) {
    double **matSum = Mat_Aloc(linhas, colunas);
    for(int i=0; i<linhas; i++) {
        for(int j=0; j<colunas; j++) {
            matSum[i][j] = matA[i][j] + matB[i][j];
        }
    }
    return matSum;
}

double** Observador::Mat_Sum(double **matA, double **matB, double** matC, int linhas, int colunas) {
    double **matSum = Mat_Aloc(linhas, colunas);
    for(int i=0; i<linhas; i++) {
        for(int j=0; j<colunas; j++) {
            matSum[i][j] = matA[i][j] + matB[i][j] + matC[i][j];
        }
    }
    return matSum;
}


void Observador::geraMatQL() {

    matGlB = Mat_MultEscalar(matG, 2, 2, b);
    matGlC = Mat_MultEscalar(matI, 2, 2, c);

    matQL = Mat_Sum(matGlA, matGlB, matGlC, 2, 2);

    //return matQL;
}

void Observador::geraMatL() {
    geraMatQL();

    double **matTemp = Mat_Aloc(2,2);
    matTemp = Mat_Mult(matQL, 2, 2, matWoInv, 2, 2);
    matL = Mat_Mult(matTemp, 2, 2, matColSL, 2, 1);
}

/****************/


Observador::Observador() {
    matColSL = Mat_Aloc(2,1);
    matGlA = Mat_Aloc(2,2);
    matGlB = Mat_Aloc(2,2);
    matGlC = Mat_Aloc(2,2);

    matG = Mat_Aloc(2,2);
    matI = Mat_Aloc(2,2);
    matH = Mat_Aloc(2,1);

    matWoInv = Mat_Aloc(2,2);

    matQL = Mat_Aloc(2,2);
    matL = Mat_Aloc(2,1);

    /*-------------------*/

    matColSL[0][0] = 0.0;
    matColSL[1][0] = 1.0;

    matG[0][0] = 0.993458;
    matG[0][1] = 0.0;
    matG[1][0] = 0.006520;
    matG[1][1] = 0.993458;

    /* Matriz G^2 */
    matGlA[0][0] = 0.986958798;
    matGlA[0][1] = 0.0;
    matGlA[1][0] = 0.012954692;
    matGlA[1][1] = 0.986958798;

    matI[0][0] = 1.0;
    matI[0][1] = 0.0;
    matI[1][0] = 0.0;
    matI[1][1] = 1.0;

    matWoInv[0][0] = -152.3708589;
    matWoInv[0][1] = 153.3742331;
    matWoInv[1][0] = 1.0;
    matWoInv[1][1] = 0.0;
}

Observador::~Observador() {
    matGlA = Mat_Free(2,2,matGlA);
    matGlB = Mat_Free(2,2,matGlB);
    matGlC = Mat_Free(2,2,matGlC);

    matG = Mat_Free(2,2,matG);
    matI = Mat_Free(2,2,matI);
    matH = Mat_Free(2,1,matH);
    matWoInv = Mat_Free(2,2,matWoInv);

    matQL = Mat_Free(2,2,matQL);
    matL = Mat_Free(2,2,matL);
}


void Observador::calculaObservador(double tensao, double y, int polo1[2], int polo2[2]) {
    b = polo1[0]*2;
    c = polo1[0]*polo2[0] + polo1[1]*polo2[1];

    matXObs = Mat_Sum( Mat_Mult(matG,2,2,matXObs,2,1), \
                       Mat_MultEscalar(matL, 2, 1, y-yObs), \
                       Mat_MultEscalar(matH, 2, 1, tensao), \
                        2, 1);
}