#include <stdio.h>
#include <stdbool.h>

#define V 5  // Grafın düğüm sayısı

// Verilen yol Hamilton Devresi mi diye kontrol eden fonksiyon
bool isHamiltonCycle(int path[]) {
    bool visited[V];
    int i;

    // Tüm düğümleri ziyaret edilmemiş olarak işaretle
    for (i = 0; i < V; i++) {
        visited[i] = false;
    }

    // Yolun başındaki düğümü tekrar ziyaret ediyor mu kontrol et
    if (path[0] != path[V-1]) {
        return false;
    }

    // Tüm düğümleri ziyaret edip edilmediğini kontrol et
    for (i = 0; i < V-1; i++) {
        if (!visited[path[i]]) {
            visited[path[i]] = true;
        } else {
            return false;
        }
    }

    // Son düğüm de ziyaret edildiyse Hamilton Devresi'dir
    return visited[path[V-1]];
}

// Tüm permütasyonları kullanarak Hamilton Devresi'ni bulan fonksiyon
void hamiltonianCycle(int graph[V][V]) {
    int i, j, k;
    int path[V];

    // İlk yol olarak tüm düğümleri sırayla ekle
    for (i = 0; i < V; i++) {
        path[0] = i;
        for (j = 0; j < V; j++) {
            if (graph[i][j] && i != j) {
                path[1] = j;
                for (k = 2; k < V; k++) {
                    path[k] = -1; // Yolun kalanını -1 olarak işaretle
                }
                if (isHamiltonCycle(path)) { // Yol Hamilton Devresi ise yazdır
                    printf("Hamilton Devresi: ");
                    for (k = 0; k < V; k++) {
                        printf("%d ", path[k]);
                    }
                    printf("%d\n", path[0]);
                    return;
                }
            }
        }
    }

    printf("Hamilton Devresi yok.\n");
}

int main() {
    int graph[V][V] = {{0, 1, 0, 1, 0},
                       {1, 0, 1, 1, 1},
                       {0, 1, 0, 0, 1},
                       {1, 1, 0, 0, 1},
                       {0, 1, 1, 1, 0}};

    hamiltonianCycle(graph);

    return 0;
}
