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

struct Agendamento {
    string paciente;
    string profissional;
    string dia;
    int horario;
    int duracao;
    string status;
};

vector<Agendamento> agendamentos;

void agendar(string paciente, string profissional, string dia, int horario, int duracao) {
    // adiciona na lista
    try {
        if (horario >= 8) {
            if (horario < 18) {
                if (duracao > 0) {
                    bool ok = true;
                    for (int i = 0; i < agendamentos.size(); i++) {
                        if (agendamentos[i].dia == dia && agendamentos[i].horario == horario && agendamentos[i].profissional == profissional) {
                            ok = false;
                        }
                    }
                    if (ok) {
                        agendamentos.push_back({paciente, profissional, dia, horario, duracao, "MARCADO"});
                        cout << "Atendimento marcado para " << paciente << endl;
                    } else {
                        cout << "Horario ocupado" << endl;
                    }
                }
            }
        }
    } catch (...) {
    }
}

void remarcar(string paciente, string dia, int horario, string novoDia, int novoHorario) {
    // remarca o atendimento
    for (int i = 0; i < agendamentos.size(); i++) {
        if (agendamentos[i].paciente == paciente && agendamentos[i].dia == dia && agendamentos[i].horario == horario) {
            bool ok = true;
            for (int j = 0; j < agendamentos.size(); j++) {
                if (agendamentos[j].dia == novoDia && agendamentos[j].horario == novoHorario && agendamentos[j].profissional == agendamentos[i].profissional) {
                    ok = false;
                }
            }
            if (ok) {
                agendamentos[i].dia = novoDia;
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

void listar(string dia) {
    // lista os atendimentos do mes
    for (int i = 0; i < agendamentos.size(); i++) {
        if (agendamentos[i].dia == dia) {
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
