**Projeto de Monitoramento Ambiental com ESP32**
Este projeto utiliza um microcontrolador ESP32 para monitorar parâmetros ambientais, como temperatura, umidade e qualidade do ar. Os dados são coletados por sensores (DHT22 e MQ-135), exibidos em um display OLED e enviados para a plataforma Adafruit IO via protocolo MQTT para análise e monitoramento remoto.

Componentes Utilizados
ESP32

Microcontrolador com conectividade Wi-Fi e Bluetooth integrado.
Sensor DHT22

Mede temperatura e umidade relativa do ambiente.
Sensor MQ-135

Mede a qualidade do ar (detecção de gases como CO2, NH3, benzeno, entre outros).
Display OLED (SSD1306)

Tela de 128x64 pixels para exibição local das medições.
Conexão Wi-Fi

Rede Wi-Fi para envio dos dados ao Adafruit IO.
Adafruit IO

Plataforma online para visualização e monitoramento dos dados em tempo real via MQTT.
Configuração do Sistema
Conexões dos Sensores
DHT22:
Pino de dados conectado ao GPIO 4.
MQ-135:
Saída analógica (AOUT) conectada ao GPIO 15.
Saída digital (DOUT) conectada ao GPIO 23.
Display OLED:
Conectado via interface I2C (SDA e SCL).
Configuração do Wi-Fi
No código, insira os detalhes da sua rede Wi-Fi:

cpp
Copiar código
char ssid[] = "SEU_SSID";
char pass[] = "SUA_SENHA";
Configuração do Adafruit IO
Adicione as suas credenciais:

cpp
Copiar código
#define AIO_USERNAME    "SEU_USERNAME"
#define AIO_KEY         "SEU_KEY"
Funcionalidades
Leitura dos Sensores:

DHT22: Mede a temperatura e a umidade.
MQ-135: Mede a qualidade do ar com base nos gases detectados.
Exibição Local:

Dados de temperatura, umidade e qualidade do ar são exibidos no display OLED.
Envio de Dados:

Os valores são enviados para o Adafruit IO utilizando o protocolo MQTT.
Cálculo do Tempo de Resposta:

Mede o tempo médio de leitura de cada sensor (DHT22 e MQ-135), útil para análises de desempenho.
Como Usar
Requisitos
Placa ESP32 configurada no Arduino IDE.
Instale as bibliotecas necessárias:
WiFi.h
Adafruit MQTT Library
DHT Library
Adafruit GFX Library
Adafruit SSD1306
Passos
Conecte os Sensores e o Display:

Monte o circuito conforme a seção de conexões acima.
Configure o Código:

Adicione as credenciais de Wi-Fi e Adafruit IO.
Compile e Envie o Código para o ESP32:

Carregue o código usando a IDE Arduino.
Monitore os Dados:

Veja as leituras no monitor serial, no display OLED e na plataforma Adafruit IO.
Saída Esperada
Monitor Serial
plaintext
Copiar código
Conectando ao Wi-Fi...
Conectado!
Conectando ao Adafruit IO...
Conectado ao Adafruit IO!
----- Dados do Sensor -----
Temperatura: 28.90 C
Umidade: 69.20 %
Qualidade do ar: Boa
Tempo leitura DHT (us): 5645
Tempo leitura MQ-135 (us): 33
Display OLED
plaintext
Copiar código
Sensores - Dados:
Temp: 28.9 C
Umid: 69.2 %
Qualidade: Boa
Plataforma Adafruit IO
Os dados serão enviados para os feeds configurados e poderão ser monitorados em tempo real.

Gráficos e Análise
Os tempos médios de leitura foram calculados para avaliar a eficiência do sistema:
DHT22: ~5.6 ms.
MQ-135: ~33 µs.
Dados como temperatura e umidade podem ser representados em gráficos para mostrar tendências ao longo do tempo.
Referências
Protocolo MQTT: mqtt.org
Adafruit IO: io.adafruit.com
Sensor DHT22: Datasheet
Sensor MQ-135: Datasheet
Licença
Este projeto é de código aberto, disponível para uso e modificação.
