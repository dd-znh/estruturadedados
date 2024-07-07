#include <iostream>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <locale.h>
#include <string>
#include "array_stack.cpp"

using namespace std;

// funcao para validar as tags
bool xmlvalidation(const string& file) {
    bool valid = true;
    structures::ArrayStack<std::string> pilha;

    if (file.empty()) { // Verificando se o caminho do arquivo não está vazio
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
    structures::ArrayStack<std::string> pilha;
    ifstream filexml(file);
    std::string tag;
    std::string tag_ativa = "";
    std::string name = "";
    std::string height = 0;
    std::string width = 0;
    std::string posx = 0;
    std::string posy = 0;
    int matrix [0][0];

    /* 
    TODAS AS TAGS: cenarios, cenario, nome, dimensoes, altura, largura, robo, x, y, matriz
    TAGS IMPORTANTES NO MOMENTO:
    cenario - calcular area da matriz anterior e limpar dados
    nome - saída
    altura, largura, x, y, matriz - calculo de area
    */

    // algoritmo de validacao de tags
    while (filexml.get(character)){

        // geração de tags
        if (character == '<') {
            tag_ativa = "";
            while (character != '>') {
                // armazena caracter a caracter na tag
                tag += character;
                filexml.get(character);
            }
            // armazena '>'
            tag += character;

            if (tag[1] == '/') { 
                if (pilha.empty()) {
                    valid = false;
                }
                else if (tag != pilha.top()) {
                        valid = false;
                }
                else {
                    pilha.pop();
                    tag_ativa = "";
                }
            }
            // se for tag de entrada
            else {
                tag_ativa = tag;
                tag.insert(1, "/");
                pilha.push(tag);
            }
        tag = "";
        }

        // testa qual a tag vigente para assim saber o que fazer com os dados
        else if (tag_ativa == "cenarios") {
            int h = stoi(height);
            int w = stoi(width);
            int x = stoi(posx);
            int y = stoi(posy);
            cout << areacounter(h, w, &matrix[0][0], x, y);
        }

        else if (tag_ativa == "nome") {
            name += character;
        }

        else if (tag_ativa == "altura") {
            height += character;    
        }

        else if (tag_ativa == "largura") {
            width += character;
        }

        else if (tag_ativa == "x") {
            posx += character;
        }

        else if (tag_ativa == "y") {
            posy += character;
        }

        else if (tag_ativa == "matriz") {
            cout << "Não sei como fazer ainda";
        }
    }
    // se pilha vazia entao validacao deu certo e ja pode ir para retirada das infos de cada caso
    return pilha.empty();
}