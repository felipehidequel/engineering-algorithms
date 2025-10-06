#include <iostream>

struct Node{
  int key;
  Node *prox;
};

class LinkedList{
  Node *head;
  
  public:
  LinkedList(){
    this->head = new Node;
    head->key = 0;
    head->prox = nullptr;
  }

  ~LinkedList(){
    Node *atual = head;
    Node *proximoNode = nullptr;
    
    while (atual != nullptr)
    {
        proximoNode = atual->prox;
        
        delete atual;
        
        atual = proximoNode;
    }
  }

  void append(int new_key){
      Node *novoNode = new Node;
      novoNode->key = new_key;
      novoNode->prox = nullptr;

      if(head->prox == nullptr){
          head->prox = novoNode;
          return;
      }
      
      Node *ultimo = head;
      while(ultimo->prox != nullptr){
          ultimo = ultimo->prox;
      }
      ultimo->prox = novoNode;
  }

  Node* searchList(int key){
    Node* atual = head;
    while (atual != nullptr && atual->key != key)
    {
      atual = atual->prox;
    }
    return atual;
  }
  
};

int main() {
    LinkedList minhaLista;
    minhaLista.append(10);
    minhaLista.append(20);
    minhaLista.append(30);

    return 0;
}