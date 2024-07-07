#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <iostream>

using namespace std;

namespace structures {

template<typename T>
class Trie {
private:
    struct Node {
        char letra;
        Node* filhos[26]; // 26 letras do alfabeto
        size_t fim_de_palavra; // Se for maior que zero, indica que o nó é o final de uma palavra
        int i; // Posição do primeiro caracter da palavra
        int j;  // Tamanho da linha

        // Construtor do nó
        Node(char c) : letra(c), fim_de_palavra(0), i(0), j(0) {
            for (size_t i = 0; i < 26; i++) {
                filhos[i] = nullptr;
            }
        }
    };

    Node* root; // Raiz da trie
    size_t size_; // Tamanho da trie

    void delete_node(Node* node); // Método auxiliar para deletar um nó
    void print(Node* node, string prefix) const; // Método auxiliar para imprimir a trie
    void visualize(Node* node, string prefix, int level)const;

public: //se necessário, adicionar mais métodos futuramente
    Trie(); // Construtor da trie
    ~Trie(); // Destrutor da trie

    bool empty() const; // Método para verificar se a trie está vazia
    size_t size() const; // Método que retorna o tamanho da trie
    void insert(const string& palavra, int i, int j); // Método para inserir uma palavra na trie
    void print() const; // Método para imprimir as palavras na trie
    size_t checkPrefix(const string& prefix); // Método para verificar se um prefixo existe na trie
    void visualize() const; // Método para visualizar a trie 
    size_t countPrefix(Node* node); // Método para contar número de fim de nodos de fins de palavras a partir de um nodo
};

} // namespace structures


#endif // TRIE_H


namespace structures {

template<typename T>
Trie<T>::Trie() { // Construtor da trie
    root = new Node(' ');
    size_ = 0;
}

template<typename T>
Trie<T>::~Trie() { // Destrutor da trie
    delete_node(root);
}

template<typename T>
void Trie<T>::visualize(Node* node, string prefix, int level) const {
    if (node == nullptr) {
        return;
    }
    if (node->letra != ' ') {
        cout << string(level * 2, ' ') << node->letra;
        if (node->fim_de_palavra > 0) {
            cout << " (" << node->fim_de_palavra << ")";
        }
        cout << endl;
    }
    for (size_t i = 0; i < 26; ++i) {
        if (node->filhos[i] != nullptr) {
            visualize(node->filhos[i], prefix + node->filhos[i]->letra, level + 1);
        }
    }
}

template<typename T>
void Trie<T>::visualize() const {
    visualize(root, "", 0);
}

template<typename T>
void Trie<T>::delete_node(Node* node) {
    if (node != nullptr) {
        for (size_t i = 0; i < 26; i++) {
            delete_node(node->filhos[i]);
        }
        delete node;
    }
}

template<typename T>
bool Trie<T>::empty() const {
    return size() == 0;
}

template<typename T>
size_t Trie<T>::size() const {
    return size_;
}

template<typename T>
void Trie<T>::insert(const string& palavra, int i, int j) {

    Node* atual = root;
    //itera através dos caracteres da strind palavra

    //calcula o índice da letra
    for (size_t i = 0; i < palavra.size(); i++) {
        size_t index = palavra[i] - 'a';   
        
        //se o filho não existir, cria um novo nó
        if (atual->filhos[index] == nullptr) { 
            atual->filhos[index] = new Node(palavra[i]);
        }

        //atualiza o nó atual para o nó filho recem criado ou que já existia
        atual = atual->filhos[index];
    }

    // depois de processar todos os caracteres da palavra, marca o nó final como 1, indicando que a palavra termina ali
    atual->fim_de_palavra++;
    atual->i = i; 
    atual->j = j; 
    size_++;
}

template<typename T>
void Trie<T>::print(Node* node, string prefix) const {
    if (node == nullptr) return;

    // se chegou ao final de uma palavra, imprime o prefixo
    if (node->fim_de_palavra > 0) {
        cout << prefix << endl;
    }

    for (size_t i = 0; i < 26; i++) {

        // se o nó filho existir, chama a função recursivamente
        if (node->filhos[i] != nullptr) {
            print(node->filhos[i], prefix + node->filhos[i]->letra);
        }
    }
}

template<typename T>
void Trie<T>::print() const {
    print(root, "");
}

// função recursiva para calcular o número de fim de palavras a partir de um nodo
template<typename T>
size_t Trie<T>::countPrefix(Node* node) {
    size_t contador = 0;

    // Verifica se o próprio nó é o fim de uma palavra
    if (node->fim_de_palavra) {
        contador++;
    }

    // percorre todos os nós filhos desse nodo somando o countPrefix de cada
    for (size_t i = 0; i < 26; i++) {
        if (node->filhos[i] != nullptr) {
            contador += countPrefix(node->filhos[i]);
        }
    }
    return contador;
}

template<typename T>
size_t Trie<T>::checkPrefix(const string& prefix) {
    Node* atual = root;

    //loop verifica se é prefixo e aponta para a última letra do prefixo
    for (size_t i = 0; i < prefix.size(); i++) {

        //calcula o índice da letra atual do prefixo
        int index = prefix[i] - 'a';
      
        //se o filho existir (ou seja, a letra atual do prefixo estiver na arvore), atualiza o nó atual
        if (atual->filhos[index] != nullptr) {

            //pegamos a letra seguinte para verificar se é prefixo
            atual = atual->filhos[index];

        // caso não seja prefixo de nenhuma palavra, retorna 0
        } else {
            cout << prefix << " is not prefix" << endl;
            return 0;
        }
    }

    // chama a função countPrefix para o último nodo do prefixo
    cout << prefix << " is prefix of " << countPrefix(atual) << " words" << endl;

    // se o prefixo for uma palavra, imprime a posição da palavra
    if (atual->fim_de_palavra > 0) {
        cout << prefix << " is at (" << atual->i  << "," << atual->j << ")"<< endl;
    }
    return countPrefix(atual);

} //checkPrefix

} // namespace structures

