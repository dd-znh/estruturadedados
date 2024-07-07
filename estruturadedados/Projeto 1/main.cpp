<<<<<<< HEAD
#include <iostream>
#include <string>
#include "./func.h"
#include "./infos.cpp"
// Alunos: Eduardo Achar - 23102448 e Victória Rodrigues Veloso - 23100460 
=======
<<<<<<< HEAD
#include <stdlib.h>
#include <stdio.h>
#include "./func.h"
#include "./infos.cpp"
=======
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>
>>>>>>> 120852008adc3871fda1a3c7063dfa4963ae3c94
>>>>>>> origin/main

namespace structures {

template<typename T>
class ArrayQueue {
public:
    ArrayQueue();
    ArrayQueue(std::size_t max);
    ~ArrayQueue();

    void enqueue(const T& data);
    T dequeue();
    T& back();
    void clear();
    std::size_t size();
    std::size_t max_size();
    bool empty();
    bool full();

private:
    T* contents;
    std::size_t max_size_;
    int begin_;
    int end_;
    std::size_t size_;
    static const auto DEFAULT_SIZE = 10u;
};

template<typename T>
ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
    size_ = 0;
}

template<typename T>
ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    begin_ = 0;
    end_ = -1;
    size_ = 0;
}

template<typename T>
ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}

template<typename T>
void ArrayQueue<T>::enqueue(const T& data) {
    if (full())
        throw std::out_of_range("fila cheia");
    end_ = (end_ + 1) % max_size_;
    contents[end_] = data;
    size_++;
}

template<typename T>
T ArrayQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("fila vazia");
    T aux = contents[begin_];
    begin_ = (begin_ + 1) % max_size_;
    size_--;
    return aux;
}

template<typename T>
T& ArrayQueue<T>::back() {
    if (empty())
        throw std::out_of_range("fila vazia");
    return contents[end_];
}

template<typename T>
void ArrayQueue<T>::clear() {
    begin_ = 0;
    end_ = -1;
    size_ = 0;
}

template<typename T>
std::size_t ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool ArrayQueue<T>::empty() {
    return size_ == 0;
}

template<typename T>
bool ArrayQueue<T>::full() {
    return size_ == max_size_;
}

template<typename T>
class ArrayStack {
public:
    ArrayStack();
    ArrayStack(std::size_t max);
    ~ArrayStack();

    void push(const T& data);
    T pop();
    T& top();
    void clear();
    std::size_t size();
    std::size_t max_size();
    bool empty();
    bool full();

private:
    T* contents;
    std::size_t max_size_;
    int top_;
    static const auto DEFAULT_SIZE = 10u;
};

template<typename T>
ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[DEFAULT_SIZE];
    top_ = -1;
}

template<typename T>
ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
ArrayStack<T>::~ArrayStack() {
    delete[] contents;
}

template<typename T>
void ArrayStack<T>::push(const T& data) {
    if (full())
        throw std::out_of_range("pilha cheia");
    top_++;
    contents[top_] = data;
}

template<typename T>
T ArrayStack<T>::pop() {
    if (empty())
        throw std::out_of_range("pilha vazia");
    T aux = contents[top_];
    top_--;
    return aux;
}

template<typename T>
T& ArrayStack<T>::top() {
    if (empty())
        throw std::out_of_range("pilha vazia");
    return contents[top_];
}

template<typename T>
void ArrayStack<T>::clear() {
    top_ = -1;
}

template<typename T>
std::size_t ArrayStack<T>::size() {
    return top_ + 1;
}

template<typename T>
std::size_t ArrayStack<T>::max_size() {
    return max_size_;
}

template<typename T>
bool ArrayStack<T>::empty() {
    return (top_ == -1);
}

template<typename T>
bool ArrayStack<T>::full() {
    return size() == max_size_;
}

}  // namespace structures

using namespace std;

int areacounter(int height, int width, int **matrix, int startX, int startY) {
    structures::ArrayQueue< std::pair<int, int> > q(100000);
    int cont = 0;

    if (!(startX >= 0 && startX < height && startY >= 0 && startY < width) || matrix[startX][startY] != 1){
        return 0;
    }

    q.enqueue(std::make_pair(startX, startY));

    while (!q.empty()) {
        std::pair<int, int> b = q.dequeue();
        int nx = b.first;
        int ny = b.second;

        if(matrix[nx][ny] == 1) {
            cont += 1;
            matrix[nx][ny] = 2;

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

bool xmlvalidation(const string& file) {
    structures::ArrayStack<std::string> pilha;
    ifstream filexml(file);
    std::string tag;
    char character;

    while (filexml.get(character)){
        if (character == '<') {
            while (character != '>') {
                tag += character;
                filexml.get(character);
            }
            tag += character;

            if (tag[1] == '/') { 
                if (pilha.empty() || tag != pilha.top()) {
                    return false;
                } else {
                    pilha.pop();
                }
            } else {
                tag.insert(1, "/");
                pilha.push(tag);
            }
        tag = "";
        }
    }
    return pilha.empty();
}

bool xmlinfos(const string& file) {
    bool init = xmlvalidation(file);

    if (init) { 
        structures::ArrayStack<std::string> pilha;

        if (file.empty()) {
            throw invalid_argument("Caminho para o arquivo de entrada não encontrado !");
        }

        ifstream filexml(file);
        if (!filexml.is_open()) {
            cerr << "Erro ao abrir o arquivo XML no caminho: " << file << endl;
            throw runtime_error("Erro ao abrir o arquivo XML !");
        }

        char character;
        std::string tag;
        std::string tag_ativa = "";
        std::string name = "";
        std::string height = "";
        std::string width = "";
        std::string posx = "";
        std::string posy = "";
        int **matrix = nullptr;    
        int h;
        int w;
        int x;
        int y;

        cout << "output=";
        while (filexml.get(character)){
            if (character == '<') {
                tag_ativa = "";
                while (character != '>') {
                    tag += character;
                    filexml.get(character);
                }
                tag += character;
                if (tag[1] == '/') { 
                    pilha.pop();
                    tag_ativa = "";
                } else {
                    tag_ativa = tag;
                    tag.insert(1, "/");
                    pilha.push(tag);
                }
            tag = "";
            }
            else if (tag_ativa == "<cenario>") {
                name = "";
                height = "";
                width = "";
                posx = "";
                posy = "";
            }
            else if (tag_ativa == "<nome>") {
                name += character;
            }
            else if (tag_ativa == "<altura>") {
                height += character;    
            }
            else if (tag_ativa == "<largura>") {
                width += character;
            }
            else if (tag_ativa == "<x>") {
                posx += character;
            }
            else if (tag_ativa == "<y>") {
                posy += character;
            }
            else if (tag_ativa == "<matriz>") {
                h = stoi(height);
                w = stoi(width);
                x = stoi(posx);
                y = stoi(posy);

                matrix = new int*[h];
                for (int i = 0; i < h; i++) {
                    matrix[i] = new int[w];
                }

                for (int i = 0; i < h; i++) {
                    string line;
                    getline(filexml, line);
                    for (int j = 0; j < w; j++) {
                        matrix[i][j] = line[j] - '0';
                    }
                }
                cout << name << " " << areacounter(h, w, matrix, x, y) << "\n";
            }
        }
        filexml.close();
        return true;
    } else {
        return false;
    }
}

int main() {

<<<<<<< HEAD
=======
<<<<<<< HEAD

    //estrutura para encontrar o caminho dos cenários de acordo com o sistema operacional
    std::string pathFile;

    // leitura de caminho dos arquivos dependendo do SO
    #ifdef _WIN32
        pathFile = "cenarios\\cenarios1.xml"; // Caminho pra Windowns
    #elif __APPLE__
        pathFile = "cenarios/cenarios1.xml"; // Caminho pra MACOS
    #elif __linux__
        pathFile = "cenarios/cenarios1.xml"; // Caminho para Linux
    #elif __FreeBSD__
        pathFile = "cenarios/cenarios1.xml"; // Caminho para FreeBSD
    #else
        // Caso o sistema operacional não seja identificado
        std::cerr << "Sistema operacional não identificado!" << std::endl;
        return 1;
    #endif
>>>>>>> origin/main

    // para cada arquivo na pasta
    for (int i = 1; i < 7; i++) {
        std::string nameFile = "cenarios" + std::to_string(i) + ".xml";
        // saida
        std::cout << "case=" << i << "\n" << "input=" << nameFile << "\n";
        try {
            if (!xmlinfos(nameFile)) {
                std::cout << "output=erro" << std::endl;
            }
        } catch (const std::exception &e) {
            std::cerr << "Erro: " << e.what() << std::endl;
            std::cout << "output=erro" << std::endl;
        }
<<<<<<< HEAD
        std::cout << "\n";
=======
        cout << "\n";
=======
    std::string nameFile;
    std::cin >> nameFile;
    if (!xmlinfos(nameFile)) {
        std::cout << "erro" << std::endl;
        return 0;
>>>>>>> 120852008adc3871fda1a3c7063dfa4963ae3c94
>>>>>>> origin/main
    }
    std::cout << "\n";

    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> 120852008adc3871fda1a3c7063dfa4963ae3c94
