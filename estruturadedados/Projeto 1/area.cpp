#include <iostream>
#include <array>
#include "array_queue.cpp"
#include <tuple>

using namespace std;

int areacounter(int height, int width, int **matrix, int startX, int startY) {
    // fila q e contador de casas
    structures::ArrayQueue< std::pair<int, int> > q(100000);
    int cont = 0;

    // conferindo as condições de existência
    if (!(startX >= 0 && startX < height && startY >= 0 && startY < width) || matrix[startX][startY] != 1){
        return 0;
    }

    // posicao inicial entra na fila
    q.enqueue(std::make_pair(startX, startY));

    // variaveis declaradas pra ajudar na organizacao do codigo
    int nx;
    int ny;

    // algoritmo
    while (!q.empty())
    {
        // enquanto tiver pontos na fila, pegar o proximo ponto da fila 
        std::pair<int, int> b = q.dequeue();
        int nx = b.first;
        int ny = b.second;

        // se for 1 contaddor soma
        if(matrix[nx][ny] == 1) {
            cont += 1;

            // posicao recebe um valor != 1 para nao ser contado de novo (geraria um looping infinito na verdade)
            matrix[nx][ny] = 2;

            // adicionando os vizinhos a fila caso esses vizinhos existam
            if(nx + 1 < height && matrix[nx + 1][ny] == 1) {
                q.enqueue(std::make_pair(nx + 1, ny));
            }
            if(ny + 1 < width && matrix[nx][ny + 1] == 1) {
                q.enqueue(std::make_pair(nx, ny + 1));
            }
            if(nx > 0 && matrix[nx - 1][ny] == 1) {
                q.enqueue(std::make_pair(nx - 1, ny));
            }
            if(ny > 0 && matrix[nx][ny - 1] == 1) {
                q.enqueue(std::make_pair(nx, ny - 1));
            }
        }
    }
    return cont;
}
