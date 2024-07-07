#include <iostream>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <locale.h>
#include <string>
#include "array_stack.cpp"
#include "area.cpp"

using namespace std;

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


    char character;
    string tag_ativa = "";
    string tag = "";

    while (filexml.get(character)){ // leitura do arquivo

        // geração de tags
        if (character == '<') { //verifica se é uma tag de aberura ou fechamento
            tag_ativa = ""; //limpa a tag ativa
            while (character != '>') { // enquanto não encontrar o >, concatena os caracteres na tag
                tag += character; //concatena os caracteres na tag
                filexml.get(character); //lê o próximo caractere
            }
            tag += character; //contacena o > na tag

            if (tag[1] == '/') { // </tag> - tag de fechamento
                if (pilha.empty()) { //verifica se a pilha está vazia
                    valid = false; //se estiver vazia, a tag não tem tag de abertura correspondente
                }
                else if (tag != pilha.top()) { //verifica se a tag de fechamento é correspondente a tag de abertura
                        valid = false;
                }
                else {
                    pilha.pop(); //remove a tag de abertura da pilha
                    tag_ativa = ""; //limpa a tag ativa
                }
            }
            else {// #########NAO ENTENDI ESSE TRECHO DO CÓDIGO
                tag_ativa = tag; //se nao for uma tag de fechamento, a tag ativa é a tag de abertura
                tag.insert(1, "/"); //transforma a tag de abertura em tag de fechamento
                pilha.push(tag);
            }
        tag = "";
        }
    }