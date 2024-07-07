#include <iostream>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <locale.h>
#include <string>
#include "area.cpp"
#include "validation.cpp"

using namespace std;

bool xmlinfos(const string& file) {

    // validacao
    bool init = xmlvalidation(file);

    // se a validacao der certo segue para calculo de area com as infos
    if (init) { 
        structures::ArrayStack<std::string> pilha;

        // Verificando se o caminho do arquivo não está vazio
        if (file.empty()) {
            throw invalid_argument("Caminho para o arquivo de entrada não encontrado !");
        }

        // Abrindo o arquivo XML
        ifstream filexml(file);
        if (!filexml.is_open()) {
            cerr << "Erro ao abrir o arquivo XML no caminho: " << file << endl;
            throw runtime_error("Erro ao abrir o arquivo XML !");
        }

        // Variaveis presentes no texto a serem armazenadas para o calculo da area
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

        // algoritmo de validacao de tag modificado (nao precisa verificar fechamento)
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
            // testa qual a tag vigente para fazer a leitura das informacoes
            else if (tag_ativa == "<cenario>") {
                // novo caso, entao zerar variaveis
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

                // passando variaveis lidas para inteiro
                h = stoi(height);
                w = stoi(width);
                x = stoi(posx);
                y = stoi(posy);

                // criacao de matriz
                matrix = new int*[h];
                for (int i = 0; i < h; i++) {
                    matrix[i] = new int[w];
                }

                // Preenchendo a matriz com os valores do arquivo
                for (int i = 0; i < h; i++) {
                    string line;
                    // Lê uma linha do arquivo
                    getline(filexml, line);
                    for (int j = 0; j < w; j++) {
                        // Converte o caractere para inteiro e atribui à matriz
                        matrix[i][j] = line[j] - '0';
                    }
                }
                cout << name << " " << areacounter(h, w, matrix, x, y) << "\n";
            }
        }
        // Fechando o arquivo
        filexml.close();
        return true;
    } else {return false;}
}
