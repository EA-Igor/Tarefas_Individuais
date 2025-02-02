# 📡 Projeto: Interrupções no Microcontrolador RP2040

Este repositório contém o código-fonte e a documentação para a atividade prática da Unidade 4 - Capítulo 4 (Interrupções) do curso de sistemas embarcados, referente a aula Síncrona do dia 27/01/2025.

[Link do video de apresentação](https://youtu.be/z9qfMr6r9OU)
---

<div align="center">
  <img src="https://github.com/user-attachments/assets/a01ead39-8c4c-4efe-804c-79700c946baa" alt="Descrição da imagem">
</div>

---
## 🎯 Objetivos

### Compreensão
- Funcionamento e aplicação de interrupções em microcontroladores.
- Implementação de debouncing via software para evitar bouncing em botões.

### Prática
- Manipulação de LEDs comuns e LEDs endereçáveis WS2812.
- Utilização de resistores de pull-up internos para botões de acionamento.
- Desenvolvimento de um projeto funcional que combine hardware e software.

## 📝 Descrição do Projeto

O projeto utiliza os seguintes componentes conectados à placa BitDogLab:

### Componentes Utilizados
- **Matriz 5x5 de LEDs WS2812** (endereçáveis) conectada à **GPIO 7**.
- **LED RGB** com os pinos conectados às **GPIOs 11, 12 e 13**.
- **Botão A** conectado à **GPIO 5**.
- **Botão B** conectado à **GPIO 6**.

## ⚙️ Funcionalidades Implementadas

### LEDs e Botões
1. O **LED vermelho** do LED RGB pisca continuamente **5 vezes por segundo**.
2. O **Botão A** incrementa o número exibido na matriz de LEDs quando pressionado.
3. O **Botão B** decrementa o número exibido na matriz de LEDs quando pressionado.
4. A **matriz de LEDs WS2812** exibe números de **0 a 9** com um formato fixo (estilo digital) ou criativo, desde que os números sejam reconhecíveis.

## 🛠️ Requisitos Técnicos

### Implementação
- Uso de **interrupções (IRQ)** para todas as funcionalidades dos botões.
- Implementação de **debouncing via software** para evitar leituras incorretas dos botões.
- Controle de diferentes tipos de LEDs (**LEDs comuns e WS2812**).
- Código bem estruturado e comentado para facilitar o entendimento.

## 🚀 Como Executar o Projeto

### 📌 Pré-requisitos
- Placa **BitDogLab**
- Microcontrolador **RP2040**
- Biblioteca para controle dos **LEDs WS2812**
- Ambiente de desenvolvimento compatível (ex.: **Thonny, VSCode + Pico SDK**)

### 📥 Clonando o Repositório
```bash
  git clone https://github.com/EA-Igor/Tarefas_Individuais.git
```

### 🔧 Compilação e Upload
1. Compile o código-fonte no ambiente de desenvolvimento adequado.
2. Envie o firmware para a placa **BitDogLab**.
3. Conecte os componentes conforme o diagrama (fornecido no repositório).
4. Execute o código e verifique o funcionamento dos botões e LEDs.

## 📹 Entrega e Demonstração

### Requisitos da Entrega
- **Código-fonte**: O código será avaliado quanto à organização e funcionamento.
- **Vídeo de demonstração**: Um vídeo de até **2 minutos**, contendo:
  - Demonstração do funcionamento do projeto.
  - Explicação das funcionalidades implementadas.
  - Execução na placa **BitDogLab**.
- [Link do video](https://youtu.be/z9qfMr6r9OU)
