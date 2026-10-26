#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int HORARIO_INICIO = 8;  //!< Hora do dia em que se iniciam atendimentos
const int HORARIO_FIM    = 18; //!< Hora do dia limite para atendimentos

struct Agendamento {
    string paciente;
    string profissional;
    string data;
    int horario;
    int duracao;
    string status;
};

vector<Agendamento> agendamentos;

/**
 * @brief Verifica se uma string está no formato AAAA-MM-DD de data
 * @param data String de texto representando uma data
 * @return true se a data estiver no formato certo, false caso contrário
 */
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

/**
 * @brief Verifica se o intervalo de tempo para um atendimento é válido
 * @param horario Hora de início do atendimento
 * @param duracao Duração, em minutos, do atendimento
 * @return true so o horário for válido, false caso contrário
 */
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

/**
 * @brief Verifica se um horário de atendimento está disponível, consideranto data, hora e profissional
 * @param profissional Profissional que realizará o atendimento
 * @param data Data, no formato AAAA-MM-DD, do atendimento
 * @param horario Horário do atendimento
 * @return true se o horário estiver livre, false se não estiver.
 */
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

/**
 * @brief Insere um agendamento na lista se seu horário estiver disponível
 * @param novoAgendamento Agendamento a ser adicionado
 * @param disponivel Booleano que determina a disponibilidade do horário
 */
void registrarAgendamento(Agendamento novoAgendamento, bool disponivel) {
    if (disponivel) {
        novoAgendamento.status = "MARCADO";
        agendamentos.push_back(novoAgendamento);
    }
}

/**
 * @brief Envia à saída padrão o resultado de uma tentativa de agendamento
 * @param paciente Nome do paciente do agendamento
 * @param disponivel Booleano que determina a disponibilidade do horário
 */
void imprimirResultadoAgendamento(string paciente, bool disponivel) {
    if (disponivel) cout << "Atendimento marcado para " << paciente;
    else cout << "Horario ocupado";
    cout << endl;
}

/**
 * @brief Busca na lista de agendamentos por um específico, determinado pelos parâmetros
 * @param paciente Paciente do agendamento a ser buscado
 * @param data Data, no formato AAAA-MM-DD, do agendamento a ser buscado
 * @param horario Horário do agendamento a ser buscado
 * @return Índice do agendamento encontrado, ou -1 se não for encontrado 
 */
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

/**
 * @brief Atualiza as informações de um agendamento existente de acordo com os parâmetros
 * @param alvo Agendamento a ser alterado
 * @param novoHorario Horário novo do agendamento alvo
 * @param novaData Data nova, no formato AAAA-MM-DD, do agendamento alvo
 */
void atualizarAgendamentoRemarcado(Agendamento &alvo, int novoHorario, string novaData) {
    alvo.horario = novoHorario;
    alvo.data = novaData;
}

/**
 * @brief Envia à saída padrão o resultado de uma tentativa de remarcar agendamento
 * @param disponivel Booleano que determina se o agendamento pôde ou não ser remarcado
 */
void imprimirResultadoRemarcado(bool disponivel) {
    if (disponivel) {
        cout << "Remarcado" << endl;
    }
    else {
        cout << "Horario ocupado" << endl;
    }
}

/**
 * @brief Registra um agendamento novo
 * @param paciente Nome do paciente a ser atendido
 * @param profissional Nome do profissional a realizar o atendimento
 * @param data Data, no formato AAAA-MM-DD, do atendimento
 * @param horario Hora do atendimento
 * @param duracao Duração, em minutos, do atendimento
 * @throw except Exceção jogada quando o formato da data ou o horário está inválido 
 */
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

/**
 * @brief Remarca um atendimento agendado
 * @param paciente Nome do paciente
 * @param data Data, no formato AAAA-MM-DD, do atendimento agendado
 * @param horario Hora do atendimento agendado
 * @param novaData Data, no formato AAAA-MM-DD, que substituirá a data agendada
 * @param novoHorario Horário que substituirá o horário agendado
 * @throw e Exceção jogada quando o atendimento passado na função não está na lista
 * @throw err Exceção jogada quando o formato da data está inválido
 */
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

/**
 * @brief Envia à saída padrão as informações sobre cada agendamento em um dia, um por linha
 * @param data Data, no formato AAAA-MM-DD, cujos atendimentos serão listados
 */
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
