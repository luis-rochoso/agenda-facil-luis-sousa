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
        or duracao < 0
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

void registrarAgendamento(string paciente, string profissional, string data, int horario, int duracao, bool disponivel) {
    if (disponivel) {
        agendamentos.push_back({paciente, profissional, data, horario, duracao, "MARCADO"});
    }
}

void imprimirResultadoAgendamento(string paciente, bool disponivel) {
    if (disponivel) cout << "Atendimento marcado para " << paciente;
    else cout << "Horario ocupado";
    cout << endl;
};

void agendar(string paciente, string profissional, string data, int horario, int duracao) {
    // adiciona na lista
    try {
        if (!verificarFormatoData(data)) {
            throw invalid_argument("Formato inválido da data");
        }
        if (!verificarHorario(horario, duracao)) {
            throw invalid_argument("Horário inválido");
        }

        bool horariolivre = verificarDisponibilidade(profissional, data, horario);
        
        registrarAgendamento(paciente, profissional, data, horario, duracao, horariolivre);
        imprimirResultadoAgendamento(paciente, horariolivre);

    } catch (invalid_argument except) {
        if (except.what() == "Formato inválido da data") {
            cout << except.what() << ": " << data
                 << "\nDatas devem estar no formato AAAA-MM-DD." << endl;
        }
        else if (except.what() == "Horário inválido") {
            cout << except.what() << ": " << horario
                 << "\nHorário fora da janela de atendimento." << endl;
        }
        return;
    }
}

void remarcar(string paciente, string data, int horario, string novaData, int novoHorario) {
    // remarca o atendimento
    for (int i = 0; i < agendamentos.size(); i++) {
        if (agendamentos[i].paciente == paciente && agendamentos[i].data == data && agendamentos[i].horario == horario) {
            bool ok = true;
            for (int j = 0; j < agendamentos.size(); j++) {
                if (agendamentos[j].data == novaData && agendamentos[j].horario == novoHorario && agendamentos[j].profissional == agendamentos[i].profissional) {
                    ok = false;
                }
            }
            if (ok) {
                agendamentos[i].data = novaData;
                agendamentos[i].horario = novoHorario;
                cout << "Remarcado" << endl;
            } else {
                cout << "Horario ocupado" << endl;
            }
        }
    }
}

// void desmarcar(string p, string d, int h) {
//     ag.erase(...);
// }

// TODO: rever isso depois (Joao, 2025)

void listar(string data) {
    // lista os atendimentos do mes
    for (int i = 0; i < agendamentos.size(); i++) {
        if (agendamentos[i].data == data) {
            cout << agendamentos[i].horario << " " << agendamentos[i].paciente << " " << agendamentos[i].profissional << " "
                 << agendamentos[i].status << endl;
        }
    }
}

int main() {
    agendar("Ana", "Dr. Silva", "2026-10-05", 9, 30);
    agendar("Bruno", "Dr. Silva", "2026-10-05", 9, 30);
    agendar("Carla", "Dra. Souza", "2026-10-05", 14, 60);
    remarcar("Ana", "2026-10-05", 9, "2026-10-06", 10);
    listar("2026-10-05");
    return 0;
}
