# **Tarefa 10/02 - Controle de Display e LEDs com Joystick**

*Projeto desenvolvido para a disciplina de Sistemas Embarcados utilizando a placa RP2040 (BitDogLab).*

## 📌 **Objetivo**
O objetivo desta tarefa é consolidar os conhecimentos sobre o uso do conversor Analógico-Digital (ADC) no RP2040 e explorar a integração com um display OLED SSD1306 via I2C. O projeto utiliza um joystick para controlar LEDs RGB via PWM e movimentar um quadrado na tela do display.

## 🛠️ **Componentes Utilizados**
- Placa **RP2040** (BitDogLab)
- **Display OLED SSD1306** (I2C)
- **Joystick analógico**
- **LED RGB** (três canais PWM)
- **Botões** de controle

## 🔧 **Descrição do Projeto**
O código implementado permite:
- ✅ **Movimentar um quadrado no display SSD1306** conforme a posição do joystick  
- ✅ **Controlar a intensidade dos LEDs RGB** via PWM, proporcionalmente aos eixos X e Y do joystick  
- ✅ **Alternar o estado do LED verde** ao pressionar o botão do joystick  
- ✅ **Alternar o estilo da borda do display** ao pressionar o botão do joystick  
- ✅ **Ativar ou desativar os LEDs RGB** ao pressionar o botão "A"  
- ✅ **Utilizar interrupções (IRQ) para os botões** garantindo melhor desempenho  
- ✅ **Implementar debouncing via software** para evitar leituras indesejadas  

## 📜 **Funcionamento**
### **1️⃣ Controle dos LEDs RGB**
- **LED Azul**: intensidade varia conforme o eixo Y do joystick  
- **LED Vermelho**: intensidade varia conforme o eixo X do joystick  
- Ambos os LEDs utilizam **PWM** para transições suaves  

### **2️⃣ Movimentação do Quadrado no Display**
- O joystick move um **quadrado de 8x8 pixels** no **display OLED SSD1306**
- A posição do quadrado é proporcional ao deslocamento do joystick  

### **3️⃣ Botões e Interrupções**
- **Botão do Joystick (GPIO 22)**  
  - 🔹 Alterna o estado do LED Verde  
  - 🔹 Alterna entre diferentes estilos de borda no display  

- **Botão "A" (GPIO 5)**  
  - 🔹 Ativa/desativa os LEDs RGB  

## ⚙️ **Configuração e Execução**
### **📌 Pré-requisitos**
- Placa **RP2040** configurada com o **SDK do Pico**  
- Conexão correta dos componentes conforme o esquema  
- Ambiente de desenvolvimento com **CMake e GCC ARM**  

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

- [Link do vídeo](https://youtu.be/_i7wDwEkz80)

---
### 📌 Observações Finais
Caso tenha dúvidas ou sugestões, sinta-se à vontade para abrir uma issue ou contribuir com melhorias no repositório. 🚀
