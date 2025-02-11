
# 📡 Projeto: Controle de Servomotor por PWM no RP2040

Este repositório contém o código-fonte e a documentação para a atividade prática de controle de um **servomotor por PWM** utilizando o microcontrolador **RP2040** no simulador **Wokwi**.

[🎥 Link do vídeo de demonstração](https://youtu.be/mNFBqZ3xy9g)

---

<div align="center">
  <img src="https://github.com/user-attachments/assets/4253a27f-e135-4409-a283-20f29f11e863" alt="Descrição da imagem">
</div>

---

## 🎯 Objetivos

### Compreensão
- Implementação do **controle de um servomotor** via **PWM (Pulse Width Modulation)** no RP2040.
- Configuração do **ciclo ativo do PWM** para diferentes posições do servomotor.
- Simulação e validação do funcionamento do código no **Wokwi**.
- Integração com o LED RGB para observação do comportamento do PWM.

### Prática
- **Configuração da GPIO 22** para gerar um sinal PWM de **50Hz (período de 20ms)**.
- **Definição de ciclos ativos** para posicionamento do servomotor em **0°, 90° e 180°**.
- **Movimentação periódica** da flange do servomotor entre **0° e 180°**.
- **Integração com LED RGB** para observação dos efeitos do PWM.

## 📝 Descrição do Projeto

O projeto utiliza os seguintes componentes **simulados no Wokwi** e conectados ao **Raspberry Pi Pico W (RP2040)**:

### 🛠️ Componentes Utilizados
- **Microcontrolador Raspberry Pi Pico W**
- **Servomotor (motor micro servo padrão)**
- **LED RGB conectado à GPIO 12**

### ⚙️ Funcionalidades Implementadas
1. **Geração de sinal PWM na GPIO 22** com frequência de **50Hz (20ms por ciclo)**.
2. **Definição de ciclos ativos para controle de posição do servomotor**:
   - **2.400µs (0,12%)** → Servomotor em **180°**.
   - **1.470µs (0,0735%)** → Servomotor em **90°**.
   - **500µs (0,025%)** → Servomotor em **0°**.
3. **Movimentação periódica suave entre 0° e 180°** com incrementos de **±5µs** a cada **10ms**.
4. **Integração com o LED RGB (GPIO 12)** para analisar efeitos do PWM.

## 🚀 Como Executar o Projeto

### 📌 Pré-requisitos
- **Placa Raspberry Pi Pico W (RP2040) no Wokwi**
- **Simulador Wokwi**
- **Ambiente de desenvolvimento compatível**:
  - **VSCode + Pico SDK**
  - **CMake e ferramentas de compilação**

### 📥 Clonando o Repositório
```bash
  git clone https://github.com/SEU-USUARIO/SEU-REPOSITORIO.git
```

### 🔧 Compilação e Execução
1. **Abra o projeto no VSCode**.
2. **Compile o código** usando o **Pico SDK**.
3. **Carregue o firmware** na simulação do **Wokwi**.
4. **Verifique a movimentação do servomotor e os efeitos no LED RGB**.

## 📹 Entrega e Demonstração

### Requisitos da Entrega
- **Código-fonte**: O código deve ser bem estruturado, comentado e funcional.
- **Vídeo de demonstração** com **duração máxima de 3 minutos**, contendo:
  - Explicação da implementação.
  - Demonstração da simulação no Wokwi.
  - Análise dos efeitos do PWM no LED RGB.
- **O link do vídeo deve ser incluído no README.md**.

[🎥 Link do vídeo](https://youtu.be/mNFBqZ3xy9g)

---
### 📌 Observações Finais
Caso tenha dúvidas ou sugestões, sinta-se à vontade para abrir uma issue ou contribuir com melhorias no repositório. 🚀
