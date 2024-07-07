// Nome: Eduardo Achar Matrícula 23102448 Victória Rodrigues Veloso - 23100460 

#include <iostream>
#include <fstream>
#include <list>
#include "Trie.h"

using namespace std;
using namespace structures;

int main() {

    // Variaveis auxiliares atividade
    string filename;
    string word;

    // Variaveis auxiliares leitura arquivo
    string word_append; // Palavra a ser adicionada na Trie
    char c; // Caracter atual
    int i = 0; // Posição do primeiro caracter da palavra
    int j = 0; // Tamanho da linha
    string line; // Linha do arquivo
    size_t start; // Posição do colchete de abertura
    size_t end; // Posição do colchete de fechamento

    //Entrada
    cin >> filename;

    // Trie
    Trie<string> trie;

    // Abrindo arquivo
    ifstream filexml(filename);

    // Leitura do arquivo e inserção na trie
    while (getline(filexml, line)) {
        
        // Posição do primeiro caracter da próxima linha
        i = filexml.tellg();
        
        // Tamanho da linha atual
        j = line.length();
        
        // Começo da palavra sinalizado por '['
        start = line.find('[');
        
        // Final da palavra sinalizado por ']'
        end = line.find(']');
        
        // Garante a ordem dos colchetes
        if (start < end) {
            
            // A palavra a ser adicionada na Trie é
            // Uma substring que começa após o colchete de abertura
            // E acaba antes do colchete de fechamento
            word_append = line.substr(start + 1, end - start - 1);
            
            // i - j - 1 é a posição do primeiro caracter da linha
            // ja que i é a primeira posição da próxima linha e
            // j é o comprimento da linha atual
            trie.insert(word_append, i - j - 1, j);
        }
    }

    filexml.close();

    // Looping para verificar se o prefixo existe na trie (entradas do teste)
    while (1) {
        cin >> word;
        
        // Condição de parada
        if (word.compare("0") == 0) {
            break;
        }
        
        // Função da Trie
        trie.checkPrefix(word);
    }
    return 0;
}
