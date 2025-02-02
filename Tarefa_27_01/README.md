# Projeto: Controle de LEDs e Interrupções com RP2040

## Descrição
Este projeto tem como objetivo explorar o uso de interrupções no microcontrolador RP2040 utilizando a placa BitDogLab. O sistema implementa controle de LEDs RGB e uma matriz de LEDs WS2812, além da leitura de botões com tratamento de bouncing.

## Funcionalidades
- O LED vermelho do LED RGB pisca continuamente 5 vezes por segundo.
- O botão A incrementa o número exibido na matriz de LEDs.
- O botão B decrementa o número exibido na matriz de LEDs.
- A matriz de LEDs WS2812 exibe números de 0 a 9 em um formato fixo ou criativo.

## Requisitos do Projeto
- **Uso de interrupções**: Todas as interações com os botões devem ser feitas por rotinas de interrupção (IRQ).
- **Debouncing via software**: Implementação obrigatória para evitar múltiplas detecções de pressionamento dos botões.
- **Controle de LEDs**: Utilização de LEDs comuns e endereçáveis WS2812.
- **Código bem estruturado**: Código organizado e comentado para facilitar o entendimento.

## Componentes Utilizados
- **Microcontrolador**: RP2040 na placa BitDogLab.
- **Matriz 5x5 de LEDs WS2812**: Conectada à GPIO 7.
- **LED RGB**: Pinos conectados às GPIOs 11, 12 e 13.
- **Botão A**: Conectado à GPIO 5.
- **Botão B**: Conectado à GPIO 6.

## Instruções de Uso
1. **Ligue a placa BitDogLab** e certifique-se de que todos os componentes estão corretamente conectados.
2. **Acompanhe o LED RGB**, que piscará continuamente na cor vermelha.
3. **Pressione o botão A** para incrementar a contagem exibida na matriz de LEDs.
4. **Pressione o botão B** para decrementar a contagem exibida na matriz de LEDs.
5. **Verifique a matriz de LEDs WS2812**, que deve exibir os números de 0 a 9 no formato definido.

## Entrega e Demonstração
Além do código-fonte, foi produzido um vídeo de demonstração mostrando:
- O funcionamento do projeto na placa BitDogLab.
- Explicação breve das funcionalidades implementadas.

## Autor
Desenvolvido para consolidar o conhecimento sobre interrupções, tratamento de bouncing e controle de LEDs no RP2040.

---
Sinta-se à vontade para contribuir e melhorar este projeto!
