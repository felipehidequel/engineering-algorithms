#include <iostream>
#include <string>
#include "heap.cpp"

class Scheduler
{
private:
    Heap heap;

public:
    void addProcess(int pid, int prioridade, const std::string &nome)
    {
        heap.insert(prioridade, pid, nome);
    }

    void boostPriority(int pid, int novaPrioridade)
    {
        heap.increaseKey(pid, novaPrioridade);
    }

    void run()
    {
        if (heap.isEmpty())
        {
            std::cout << "Nenhum processo para executar.\n";
            return;
        }

        Node p = heap.extractMax();
        std::cout << "Executando processo PID=" << p.pid
                  << " (" << p.nome << ") com prioridade "
                  << p.prioridade << "\n";
    }

    bool hasProcesses() const { return !heap.isEmpty(); }
};



int main()
{
    Scheduler escalonador;

    escalonador.addProcess(101, 3, "Editor de Texto");
    escalonador.addProcess(102, 5, "Navegador Web");
    escalonador.addProcess(103, 1, "Atualização em segundo plano");
    escalonador.addProcess(104, 4, "Compilação de código");

    std::cout << "Escalonando processos...\n";
    escalonador.run();
    escalonador.run();

    std::cout << "Boost de prioridade no processo de atualização...\n";
    escalonador.boostPriority(103, 6);

    while (escalonador.hasProcesses())
    {
        escalonador.run();
    }

    return 0;
}