# 📡 Projeto: Controle de Matriz de LEDs e Display OLED no RP2040

Este repositório contém o código-fonte e a documentação para a atividade prática de manipulação de uma **matriz 5x5 de LEDs WS2812** e um **display OLED SSD1306** utilizando o microcontrolador **RP2040**.

[Link do vídeo de apresentação](https://youtu.be/sqKQNp08qgA)

---

<div align="center">
  <img src="https://github.com/user-attachments/assets/7bb3c709-6667-4671-9b88-847643ff4cc8" alt="Descrição da imagem">
</div>

---
## 🎯 Objetivos

### Compreensão
- Implementação do controle de uma **matriz de LEDs WS2812** utilizando **PIO (Programmable I/O)** no RP2040.
- Exibição de caracteres e mensagens em um **display OLED SSD1306** via **I2C**.
- Controle de LEDs individuais e debouncing de botões físicos.

### Prática
- Utilização de **interrupções GPIO** para botões físicos.
- Controle de LEDs **comuns e endereçáveis (WS2812B)**.
- Manipulação de um **display gráfico OLED** para exibição de informações dinâmicas.

## 📝 Descrição do Projeto

O projeto utiliza os seguintes componentes conectados ao **Raspberry Pi Pico (RP2040)**:

### Componentes Utilizados
- **Matriz 5x5 de LEDs WS2812** (endereçáveis) conectada à **GPIO 7**.
- **LED RGB** com os pinos conectados às **GPIOs 11, 12 e 13**.
- **Botão A** conectado à **GPIO 5**.
- **Botão B** conectado à **GPIO 6**.
- **Display OLED SSD1306** conectado via **I2C (SDA - GPIO 14, SCL - GPIO 15)**.

## ⚙️ Funcionalidades Implementadas

### LEDs e Botões
1. **Exibição de números na matriz 5x5**: A matriz de LEDs exibe números de **0 a 9** em um formato predefinido.
2. **Interação com botões**:
   - O **Botão A** alterna o estado do **LED verde** e exibe uma mensagem no display.
   - O **Botão B** alterna o estado do **LED azul** e exibe uma mensagem no display.
3. **Entrada de caracteres via terminal serial**:
   - O usuário pode digitar um número no monitor serial.
   - O número digitado é exibido na matriz de LEDs e no **display OLED**.
4. **Controle de LEDs RGB**: LEDs individuais piscam e alternam cores com base nas interações dos botões.
5. **Debouncing via software** para evitar leituras incorretas dos botões.

## 🛠️ Requisitos Técnicos

### Implementação
- **Uso de PIO**: Implementação de um programa PIO para controle dos **LEDs WS2812**.
- **Interrupções GPIO**: Configuração dos botões para responderem a eventos de pressionamento.
- **Comunicação I2C**: Utilização do barramento **I2C** para controlar o **display OLED SSD1306**.
- **Código modularizado e bem comentado** para facilitar a compreensão e modificações.

## 🚀 Como Executar o Projeto

### 📌 Pré-requisitos
- **Placa Raspberry Pi Pico (RP2040)**
- **Matriz de LEDs WS2812**
- **Display OLED SSD1306 (I2C)**
- **Ambiente de desenvolvimento compatível**:
  - **VSCode + Pico SDK**
  - **Ferramenta de monitoramento serial** (ex.: `minicom`, `PuTTY`, `screen`)

### 📥 Clonando o Repositório
```bash
  git clone https://github.com/EA-Igor/Tarefas_Individuais.git
```

### 🔧 Compilação e Upload
1. **Compile o código** usando o **Pico SDK**.
2. **Faça o upload do firmware** para o **RP2040**.
3. **Conecte os componentes** de acordo com o diagrama fornecido.
4. **Abra o monitor serial** e envie caracteres para testar a interação com a matriz de LEDs e o display OLED.

## 📹 Entrega e Demonstração

### Requisitos da Entrega
- **Código-fonte**: O código será avaliado quanto à organização, funcionamento e clareza.
- **Vídeo de demonstração**: Um vídeo de até **2 minutos**, contendo:
  - Demonstração do funcionamento do projeto.
  - Explicação das funcionalidades implementadas.
  - Execução na placa **RP2040**.

- [Link do vídeo](https://youtu.be/sqKQNp08qgA)

---
### 📌 Observações Finais
Caso tenha dúvidas ou sugestões, sinta-se à vontade para abrir uma issue ou contribuir com melhorias no repositório. 🚀

