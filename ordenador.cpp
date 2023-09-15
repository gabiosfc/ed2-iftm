#include <stdio.h>
#include <string.h>

void imprimirNomes(char nomes[][100], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", nomes[i]);
    }
}

void bubbleSort(char nomes[][100], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                char temp[100];
                strcpy(temp, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], temp);
            }
        }
    }
}

void selectionSort(char nomes[][100], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(nomes[j], nomes[min_index]) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            char temp[100];
            strcpy(temp, nomes[i]);
            strcpy(nomes[i], nomes[min_index]);
            strcpy(nomes[min_index], temp);
        }
    }
}

void insertionSort(char nomes[][100], int n) {
    for (int i = 1; i < n; i++) {
        char key[100];
        strcpy(key, nomes[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(nomes[j], key) > 0) {
            strcpy(nomes[j + 1], nomes[j]);
            j = j - 1;
        }
        strcpy(nomes[j + 1], key);
    }
}

void merge(char nomes[][100], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    char L[n1][100], R[n2][100];

    for (i = 0; i < n1; i++)
        strcpy(L[i], nomes[left + i]);
    for (j = 0; j < n2; j++)
        strcpy(R[j], nomes[middle + 1 + j]);

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(nomes[k], L[i]);
            i++;
        } else {
            strcpy(nomes[k], R[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        strcpy(nomes[k], L[i]);
        i++;
        k++;
    }

    while (j < n2) {
        strcpy(nomes[k], R[j]);
        j++;
        k++;
    }
}

void mergeSort(char nomes[][100], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(nomes, left, middle);
        mergeSort(nomes, middle + 1, right);
        merge(nomes, left, middle, right);
    }
}

int main() {
    char nomes[1000][100];
    int n = 0;

    FILE *arquivo = fopen("nomes2.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(nomes[n], sizeof(nomes[n]), arquivo) != NULL) {
        int len = strlen(nomes[n]);
        if (len > 0 && nomes[n][len - 1] == '\n') {
            nomes[n][len - 1] = '\0';
        }
        n++;
    }

    fclose(arquivo);

    int opcao;
    do {
        printf("Selecione um algoritmo de ordenacao:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                bubbleSort(nomes, n);
                printf("Nomes ordenados pelo Bubble Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 2:
                selectionSort(nomes, n);
                printf("Nomes ordenados pelo Selection Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 3:
                insertionSort(nomes, n);
                printf("Nomes ordenados pelo Insertion Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 4:
                mergeSort(nomes, 0, n - 1);
                printf("Nomes ordenados pelo Merge Sort:\n");
                imprimirNomes(nomes, n);
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);

    return 0;
}
