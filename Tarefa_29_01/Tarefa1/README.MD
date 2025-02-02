# 🚦 Atividade 1: Temporizador Periódico

Este repositório contém o código-fonte e a documentação para a atividade prática 1 da Unidade 4 - Capítulo 5 (Temporizador periódico) do curso de sistemas embarcados, referente à aula Síncrona do dia 29/01/2025.

## 📝 Descrição

Esta atividade tem como objetivo projetar um semáforo utilizando a função `add_repeating_timer_ms()`, presente no *Pico SDK*, para alternar entre os sinais de trânsito com um intervalo de **3 segundos**. A implementação deve ser realizada em um **Raspberry Pi Pico W**, simulando os seguintes componentes:

- *03 LEDs* (vermelho, amarelo e verde)
- *03 Resistores de 330 Ω*

O comportamento do semáforo segue um *fluxo cíclico*:

1. *Vermelho* -> 3 segundos
2. *Amarelo* -> 3 segundos
3. *Verde* -> 3 segundos
4. *Repetir o ciclo*

## ✅ Requisitos da Atividade

1. O acionamento dos LEDs deve iniciar na cor *vermelha*.
2. O temporizador deve estar configurado para um atraso de *3.000 ms*.
3. A função `repeating_timer_callback()` será responsável pela mudança de estado dos LEDs.
4. O loop principal *(while(1))* deve imprimir uma mensagem no console a cada *1 segundo (1.000 ms)*.
5. O experimento deve ser realizado no **VS Code**, utilizando a extensão **Wokwi** para simulação dos LEDs nos *GPIOs 11, 12 e 13*.

## 🏗️ Estrutura do Projeto

### 🛠️ Hardware Utilizado

- *Microcontrolador:* Raspberry Pi Pico W
- *LEDs:* Vermelho (GPIO 11), Amarelo (GPIO 12), Verde (GPIO 13)
- *Resistores:* 330 Ω conectados em série com cada LED

### ⚙️ Funcionamento do Código

- Os *LEDs* são configurados como *saída*.
- O *estado inicial* é o LED vermelho aceso.
- A função `repeating_timer_callback()` é chamada automaticamente a cada *3 segundos* para alternar entre os estados do semáforo.
- O loop principal exibe a mensagem *"Semáforo operando..."* no console a cada *1 segundo*.

## 🚀 Como Executar o Projeto

### 1️⃣ Configurar o Ambiente

Antes de executar o código, é necessário configurar o ambiente de desenvolvimento:

- Instale o **Raspberry Pi Pico SDK** e configure o **Toolchain** (compilador e dependências).
- Instale o **VS Code** e a extensão **Wokwi** para simulação do código.

### 2️⃣ Compilar o Código

1. Clone este repositório:
   ```sh
   git clone https://github.com/seu-usuario/atividade1_temporizador.git
   cd atividade1_temporizador
   ```
2. Compile o código utilizando o CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

### 3️⃣  Simular no Wokwi

1. Abra o **VS Code** e a extensão **Wokwi**.
2. Execute a simulação.

## ⚠️ Observações

- Caso os LEDs não acendam, verifique as conexões e se os *GPIOs estão corretamente configurados*.
- Para testes e depuração, utilize o **Wokwi** para simular o comportamento do LED RGB.
