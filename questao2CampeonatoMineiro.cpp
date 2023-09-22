#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[4];
    int vitorias;
    int derrotas;
    int empates;
    int golsMarcados;
    int golsSofridos;
    int pontos;
    int saldoDeGols;
} Time;

void imprimirTime(Time t) {
    printf("%-4s%-4d%-4d%-4d%-4d%-4d%-4d%-4d\n", t.nome, t.pontos, t.vitorias, t.empates, t.derrotas, t.saldoDeGols, t.golsMarcados, t.golsSofridos);
}

void trocar(Time *vetor, int j) {
    Time aux = vetor[j];
    vetor[j] = vetor[j + 1];
    vetor[j + 1] = aux;
}

void bubbleSort(Time *vetor, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (vetor[j].pontos < vetor[j + 1].pontos ||
                (vetor[j].pontos == vetor[j + 1].pontos &&
                 vetor[j].vitorias < vetor[j + 1].vitorias) ||
                (vetor[j].pontos == vetor[j + 1].pontos &&
                 vetor[j].vitorias == vetor[j + 1].vitorias &&
                 vetor[j].saldoDeGols < vetor[j + 1].saldoDeGols) ||
                (vetor[j].pontos == vetor[j + 1].pontos &&
                 vetor[j].vitorias == vetor[j + 1].vitorias &&
                 vetor[j].saldoDeGols == vetor[j + 1].saldoDeGols &&
                 vetor[j].golsMarcados < vetor[j + 1].golsMarcados)) {
                trocar(vetor, j);
            }
        }
    }
}

void selectionSort(Time *vetor, int n) {
    for (int i = 0; i < n - 1; i++) {
        int indiceDoMenor = i;
        for (int j = i + 1; j < n; j++) {
            if (vetor[j].pontos > vetor[indiceDoMenor].pontos ||
                (vetor[j].pontos == vetor[indiceDoMenor].pontos &&
                 vetor[j].vitorias > vetor[indiceDoMenor].vitorias) ||
                (vetor[j].pontos == vetor[indiceDoMenor].pontos &&
                 vetor[j].vitorias == vetor[indiceDoMenor].vitorias &&
                 vetor[j].saldoDeGols > vetor[indiceDoMenor].saldoDeGols) ||
                (vetor[j].pontos == vetor[indiceDoMenor].pontos &&
                 vetor[j].vitorias == vetor[indiceDoMenor].vitorias &&
                 vetor[j].saldoDeGols == vetor[indiceDoMenor].saldoDeGols &&
                 vetor[j].golsMarcados > vetor[indiceDoMenor].golsMarcados)) {
                indiceDoMenor = j;
            }
        }
        if (indiceDoMenor != i) {
            Time aux = vetor[i];
            vetor[i] = vetor[indiceDoMenor];
            vetor[indiceDoMenor] = aux;
        }
    }
}

void insertionSort(Time *vetor, int n) {
    for (int i = 1; i < n; i++) {
        Time aux = vetor[i];
        int j;
        for (j = i - 1; j >= 0 && (vetor[j].pontos < aux.pontos ||
                                  (vetor[j].pontos == aux.pontos && vetor[j].vitorias < aux.vitorias) ||
                                  (vetor[j].pontos == aux.pontos && vetor[j].vitorias == aux.vitorias && vetor[j].saldoDeGols < aux.saldoDeGols) ||
                                  (vetor[j].pontos == aux.pontos && vetor[j].vitorias == aux.vitorias && vetor[j].saldoDeGols == aux.saldoDeGols && vetor[j].golsMarcados < aux.golsMarcados));
             j--) {
            vetor[j + 1] = vetor[j];
        }
        vetor[j + 1] = aux;
    }
}

void merge(Time *vetor, int inicio, int meio, int fim) {
    int i = inicio, j = meio + 1, k = 0;
    Time *temp = (Time *)malloc((fim - inicio + 1) * sizeof(Time));

    while (i <= meio && j <= fim) {
        if (vetor[i].pontos > vetor[j].pontos ||
            (vetor[i].pontos == vetor[j].pontos &&
             vetor[i].vitorias > vetor[j].vitorias) ||
            (vetor[i].pontos == vetor[j].pontos &&
             vetor[i].vitorias == vetor[j].vitorias &&
             vetor[i].saldoDeGols > vetor[j].saldoDeGols) ||
            (vetor[i].pontos == vetor[j].pontos &&
             vetor[i].vitorias == vetor[j].vitorias &&
             vetor[i].saldoDeGols == vetor[j].saldoDeGols &&
             vetor[i].golsMarcados > vetor[j].golsMarcados)) {
            temp[k++] = vetor[i++];
        } else {
            temp[k++] = vetor[j++];
        }
    }

    while (i <= meio) {
        temp[k++] = vetor[i++];
    }

    while (j <= fim) {
        temp[k++] = vetor[j++];
    }

    for (i = inicio, k = 0; i <= fim; i++, k++) {
        vetor[i] = temp[k];
    }

    free(temp);
}

void mergeSort(Time *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

char *escolherTime(Time *times, int numTimes, FILE *arquivo) {
    char linha[10];
    char time[4];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        strncpy(time, linha, 3);
        time[3] = '\0';

        int encontrado = 0;
        for (int i = 0; i < numTimes; i++) {
            if (strcmp(times[i].nome, time) == 0) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            return strdup(time);
        }
    }
    return NULL;
}

int main() {
    int numTimes = 0;
    Time *times = NULL;
    FILE *arquivo = fopen("dados.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    char *nomeTime;
    while ((nomeTime = escolherTime(times, numTimes, arquivo)) != NULL) {
        int vit = 0, der = 0, golsM = 0, golsS = 0, emp = 0;
        FILE *arquivoAux = fopen("dados.txt", "r");
        char linha[20];

        while (fgets(linha, sizeof(linha), arquivoAux) != NULL) {
            if (strstr(linha, nomeTime) != NULL) {
                int gp, gs;
                sscanf(linha, "%*s %dX%d", &gp, &gs);

                if (gp == gs)
                    emp++;
                if (gp > gs)
                    vit++;
                if (gs > gp)
                    der++;

                golsM += gp;
                golsS += gs;
            }
        }

        Time *temp = (Time *)realloc(times, (numTimes + 1) * sizeof(Time));
        if (temp == NULL) {
            printf("Erro na alocação de memória\n");
            fclose(arquivoAux);
            break;
        }
        times = temp;

        strcpy(times[numTimes].nome, nomeTime);
        times[numTimes].vitorias = vit;
        times[numTimes].derrotas = der;
        times[numTimes].empates = emp;
        times[numTimes].golsMarcados = golsM;
        times[numTimes].golsSofridos = golsS;
        times[numTimes].pontos = (vit * 3) + emp;
        times[numTimes].saldoDeGols = golsM - golsS;

        numTimes++;
        fclose(arquivoAux);
    }

    fclose(arquivo);

    printf("Selecione uma opção:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Merge Sort\n");
    printf("5 - Sair\n");

    int opcao;
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            bubbleSort(times, numTimes);
            break;
        case 2:
            selectionSort(times, numTimes);
            break;
        case 3:
            insertionSort(times, numTimes);
            break;
        case 4:
            mergeSort(times, 0, numTimes - 1);
            break;
        case 5:
            printf("Saindo...\n");
            free(times);
            return 0;
        default:
            printf("Opção inválida!\n");
    }

    printf("%-4s%-4s%-4s%-4s%-4s%-4s%-4s%-4s\n", "TIME", "P", "V", "E", "D", "SG", "GP", "GC");
    for (int i = 0; i < numTimes; i++) {
        imprimirTime(times[i]);
    }

    free(times);

    return 0;
}
