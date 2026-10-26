// ==========================================================
// Arquivo: agenda_base.cpp
// Autor: Equipe de estagiarios - 03/02/2024
// Alterado por: Joao - 15/05/2025
// Alterado por: Marina - 09/01/2026
// ==========================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int HORARIO_INICIO = 8;
const int HORARIO_FIM    = 18;

struct Agendamento {
    string paciente;
    string profissional;
    string data;
    int horario;
    int duracao;
    string status;
};

vector<Agendamento> agendamentos;

bool verificarFormatoData(string data) {
    if (data.size() != 10) {
        return false;
    }
    
    for (int i = 0; i < 10; ++i) {
        // Testar os hífens
        if (i == 4 or i == 7) {
            if (data[i] != '-') {
                return false;
            }
        }
        // Testar os números pela lógica da tabela ASCII
        else {
            if (data[i] < '0' or data[i] > '9') {
                return false;
            }
        }
    }

    return true;
}

bool verificarHorario(int horario, int duracao) {
    float duracaoEmHoras = duracao / 60;

    if (
        horario < HORARIO_INICIO
        or horario > HORARIO_FIM - 1 // A última consulta só pode começar até 1 hora antes de fechar
        or duracao < 15
        or duracao > 120
        or (duracao % 15 != 0)
        or horario + duracaoEmHoras > HORARIO_FIM + 1
    ) {
        return false;
    }

    return true;
}

bool verificarDisponibilidade(string profissional, string data, int horario) {
    for (int i = 0; i < agendamentos.size(); i++) {
        if (
            agendamentos[i].data == data
            and agendamentos[i].horario == horario
            and agendamentos[i].profissional == profissional
        ) {
            return false;
        }
    }
    return true;
}

void registrarAgendamento(Agendamento novoAgendamento, bool disponivel) {
    if (disponivel) {
        novoAgendamento.status = "MARCADO";
        agendamentos.push_back(novoAgendamento);
    }
}

void imprimirResultadoAgendamento(string paciente, bool disponivel) {
    if (disponivel) cout << "Atendimento marcado para " << paciente;
    else cout << "Horario ocupado";
    cout << endl;
}

// retorna o índice ao agendamento marcado encontrado
int procurarAgendamento(string paciente, string data, int horario) {
    
    for (int i = 0; i < agendamentos.size(); ++i) {
        if (
            agendamentos[i].paciente == paciente
            and agendamentos[i].data == data
            and agendamentos[i].horario == horario
        ) {
            return i;
        }
    }

    return -1;
}

void atualizarAgendamentoRemarcado(Agendamento &alvo, int novoHorario, string novaData) {
    alvo.horario = novoHorario;
    alvo.data = novaData;
}

void imprimirResultadoRemarcado(bool disponivel) {
    if (disponivel) {
        cout << "Remarcado" << endl;
    }
    else {
        cout << "Horario ocupado" << endl;
    }
}

void agendarAtendimento(string paciente, string profissional, string data, int horario, int duracao) {
    try {
        if (!verificarFormatoData(data)) {
            throw invalid_argument("Formato inválido da data");
        }
        if (!verificarHorario(horario, duracao)) {
            throw invalid_argument("Horário inválido");
        }

        bool horariolivre = verificarDisponibilidade(profissional, data, horario);
        Agendamento novoAgendamento = {paciente, profissional, data, horario, duracao, ""};
        
        registrarAgendamento(novoAgendamento, horariolivre);
        imprimirResultadoAgendamento(paciente, horariolivre);

    } catch (const invalid_argument& except) {
        if (except.what() == "Formato inválido da data") {
            cerr << except.what() << ": " << data
                 << "\nDatas devem estar no formato AAAA-MM-DD." << endl;
        }
        else if (except.what() == "Horário inválido") {
            cerr << except.what() << ": " << horario
                 << "\nHorário fora da janela de atendimento." << endl;
        }
        return;
    }
}

void remarcarAtendimento(string paciente, string data, int horario, string novaData, int novoHorario) {
    
    try {
        if (!verificarFormatoData(data) or !verificarFormatoData(novaData)) {
            throw std::invalid_argument("Formato inválido da data");
        } 
        
        int indiceAgendamento = procurarAgendamento(paciente, data, horario);
    
        if (indiceAgendamento < 0) {
            throw std::logic_error("Atendimento não está na lista.");
        }
        
        string profissional = agendamentos[indiceAgendamento].profissional;
        bool disponivel = verificarDisponibilidade(profissional, novaData, novoHorario);

        if (disponivel) {
            atualizarAgendamentoRemarcado(agendamentos[indiceAgendamento], novoHorario, novaData);
        }
        imprimirResultadoRemarcado(disponivel);
    }
    catch(const logic_error& e) {
        std::cerr << e.what() << endl;
    }
    catch(const invalid_argument& err) {
        cerr << err.what() << endl;
    }
}

void listarAtendimentosDoDia(string data) {
    for (int i = 0; i < agendamentos.size(); i++) {
        if (agendamentos[i].data == data) {
            cout << agendamentos[i].horario << " "
                 << agendamentos[i].paciente << " "
                 << agendamentos[i].profissional << " "
                 << agendamentos[i].status << endl;
        }
    }
}

int main() {
    agendarAtendimento("Ana", "Dr. Silva", "2026-10-05", 9, 30);
    agendarAtendimento("Bruno", "Dr. Silva", "2026-10-05", 9, 30);
    agendarAtendimento("Carla", "Dra. Souza", "2026-10-05", 14, 60);
    remarcarAtendimento("Ana", "2026-10-05", 9, "2026-10-06", 10);
    listarAtendimentosDoDia("2026-10-05");
    return 0;
}
