#🚦 Atividade 2: Temporizador de um Disparo (One Shot)

Este repositório contém o código-fonte e a documentação para a atividade prática 2 da Unidade 4 - Capítulo 5 (Temporizador de um Disparo) do curso de sistemas embarcados, referente à aula Síncrona do dia 29/01/2025.
---

<div align="center">
  <img src="https://github.com/user-attachments/assets/0feaa4e8-f0ab-4954-98ed-f6e4af34e9b1" alt="Descrição da imagem">
</div>

---
📝 Descrição

Esta atividade tem como objetivo projetar um sistema de temporização utilizando a função add_alarm_in_ms(), presente no Pico SDK, para acionar LEDs a partir do clique em um botão (pushbutton). A implementação deve ser realizada em um Raspberry Pi Pico W, simulando os seguintes componentes:

03 LEDs (azul, vermelho e verde)

03 Resistores de 330 Ω

01 Botão (Pushbutton)

O comportamento do sistema segue o seguinte fluxo:

Ao pressionar o botão, todos os LEDs são ligados simultaneamente.

Após 3 segundos, um LED é desligado.

Após mais 3 segundos, o segundo LED é desligado.

Após mais 3 segundos, o último LED é desligado.

O botão só pode ser pressionado novamente após o desligamento de todos os LEDs.

✅ Requisitos da Atividade

O acionamento dos LEDs deve ser realizado apenas quando o botão for pressionado.

O temporizador deve estar configurado para um atraso de 3.000 ms entre cada mudança de estado dos LEDs.

A mudança de estado dos LEDs deve ser implementada em funções de callback do temporizador, similar à função turn_off_callback() abordada em aula.

O botão não pode acionar os LEDs enquanto o ciclo de temporização estiver em andamento.

O experimento deve ser realizado no VS Code, utilizando a extensão Wokwi para simulação dos LEDs nos GPIOs 11, 12 e 13 e o botão no GPIO 5.

(Opcional) Implementar uma rotina de debounce via software para o botão.

🏗️ Estrutura do Projeto

🛠️ Hardware Utilizado

Microcontrolador: Raspberry Pi Pico W

LEDs: Azul (GPIO 11), Vermelho (GPIO 12), Verde (GPIO 13)

Resistores: 330 Ω conectados em série com cada LED

Botão: Pushbutton (GPIO 5)

⚙️ Funcionamento do Código

Os LEDs são configurados como saída e o botão como entrada.

Quando o botão é pressionado, todos os LEDs são ligados.

A função add_alarm_in_ms() é utilizada para criar atrasos de 3 segundos entre as mudanças de estado dos LEDs.

O botão é desabilitado durante o ciclo de temporização e só pode ser pressionado novamente após o último LED ser desligado.

🚀 Como Executar o Projeto

1️⃣ Configurar o Ambiente

Antes de executar o código, é necessário configurar o ambiente de desenvolvimento:

Instale o Raspberry Pi Pico SDK e configure o Toolchain (compilador e dependências).

Instale o VS Code e a extensão Wokwi para simulação do código.

2️⃣ Compilar o Código

Clone este repositório:
 ```sh
git clone https://github.com/seu-usuario/atividade2_temporizador.git
cd atividade2_temporizador
```
Compile o código utilizando o CMake:
```sh
mkdir build
cd build
cmake ..
make
```
3️⃣ Simular no Wokwi

Abra o VS Code e a extensão Wokwi.

Execute a simulação.

⚠️ Observações

Caso os LEDs não acendam, verifique as conexões e se os GPIOs estão corretamente configurados.

Para testes e depuração, utilize o Wokwi para simular o comportamento do LED RGB e do botão.

Utilize a ferramenta BitDogLab para experimentos adicionais.
