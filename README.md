# Projeto Agenda Fácil
O AgendaFácil é uma agenda de atendimentos para clínicas de pequeno porte.
### Funcionalidades
Com o Agenda Fácil, você pode:
- Registrar agendamentos para atendimentos de forma fácil, automaticamente detectando conflitos de horário;
- Remarcar agendamentos existentes, também detectando automaticamente se o novo horário está ocupado;
- Listar de forma clara todos os atendimentos em um determinado dia!

# Compilação e execução
Para compilar este programa, é necessário um compilador de C++ (G++ ou Clang) instalado.

### Caso G++
Navegue até a pasta do programa, então compile pela linha de comando com:
```
g++ -std=c++17 -Wall agenda_facil.cpp -o agenda_facil.out
```
### Caso Clang
Navegue até a pasta do programa, então compile pela linha de comando com:
```
clang -std=c++17 -Wall agenda_facil.cpp -o agenda_facil.out
```
### Executar
Após a compilação, execute o programa na mesma pasta com o comando:
```
./agenda_facil.out
```

# Documentação
A documentação desse programa foi gerada no formato Doxygen e está disponível no diretório /docs/.

Caso queira gerá-la por conta própria, é necessário ter o Doxygen instalado. No Linux, ele pode ser instalado por:
```
sudo apt install doxygen
```
Com o Doxygen instalado, a documentação pode ser facilmente gerada ao executar o seguinte comando no diretório raiz do programa:
```
doxygen Doxyfile
```
A documentação será gerada dentro da pasta /docs/.