<body>
  <h1>Projeto de Monitoramento Ambiental com ESP32</h1>
  <p>
    Este projeto utiliza um microcontrolador ESP32 para monitorar parâmetros ambientais, como temperatura, umidade e qualidade do ar. Os dados são coletados por sensores (<strong>DHT22</strong> e <strong>MQ-135</strong>), exibidos em um display OLED e enviados para a plataforma <strong>Adafruit IO</strong> via protocolo <strong>MQTT</strong> para análise e monitoramento remoto.
  </p>

  <h2>Componentes Utilizados</h2>
  <ul>
    <li><strong>ESP32</strong>: Microcontrolador com conectividade Wi-Fi e Bluetooth integrado.</li>
    <li><strong>Sensor DHT22</strong>: Mede temperatura e umidade relativa do ambiente.</li>
    <li><strong>Sensor MQ-135</strong>: Mede a qualidade do ar (detecção de gases como CO2, NH3, benzeno, entre outros).</li>
    <li><strong>Display OLED (SSD1306)</strong>: Tela de 128x64 pixels para exibição local das medições.</li>
    <li><strong>Conexão Wi-Fi</strong>: Rede Wi-Fi para envio dos dados ao Adafruit IO.</li>
    <li><strong>Adafruit IO</strong>: Plataforma online para visualização e monitoramento dos dados em tempo real via MQTT.</li>
  </ul>

  <h2>Configuração do Sistema</h2>

  <h3>Conexões dos Sensores</h3>
  <ul>
    <li><strong>DHT22</strong>: Pino de dados conectado ao GPIO <code>4</code>.</li>
    <li><strong>MQ-135</strong>:
      <ul>
        <li>Saída analógica (<code>AOUT</code>) conectada ao GPIO <code>15</code>.</li>
        <li>Saída digital (<code>DOUT</code>) conectada ao GPIO <code>23</code>.</li>
      </ul>
    </li>
    <li><strong>Display OLED</strong>: Conectado via interface I2C (SDA e SCL).</li>
  </ul>

  <h3>Configuração do Wi-Fi</h3>
  <p>No código, insira os detalhes da sua rede Wi-Fi:</p>
  <pre><code>
char ssid[] = "SEU_SSID";
char pass[] = "SUA_SENHA";
  </code></pre>

  <h3>Configuração do Adafruit IO</h3>
  <p>Adicione as suas credenciais:</p>
  <pre><code>
#define AIO_USERNAME    "SEU_USERNAME"
#define AIO_KEY         "SEU_KEY"
  </code></pre>

  <h2>Funcionalidades</h2>
  <ul>
    <li><strong>Leitura dos Sensores</strong>:
      <ul>
        <li><strong>DHT22</strong>: Mede a temperatura e a umidade.</li>
        <li><strong>MQ-135</strong>: Mede a qualidade do ar com base nos gases detectados.</li>
      </ul>
    </li>
    <li><strong>Exibição Local</strong>: Dados de temperatura, umidade e qualidade do ar são exibidos no display OLED.</li>
    <li><strong>Envio de Dados</strong>: Os valores são enviados para o <strong>Adafruit IO</strong> utilizando o protocolo <strong>MQTT</strong>.</li>
    <li><strong>Cálculo do Tempo de Resposta</strong>: Mede o tempo médio de leitura de cada sensor (<strong>DHT22</strong> e <strong>MQ-135</strong>), útil para análises de desempenho.</li>
  </ul>

  <h2>Como Usar</h2>
  <h3>Requisitos</h3>
  <ul>
    <li>Placa ESP32 configurada no Arduino IDE.</li>
    <li>Instale as bibliotecas necessárias:
      <ul>
        <li><strong>WiFi.h</strong></li>
        <li><strong>Adafruit MQTT Library</strong></li>
        <li><strong>DHT Library</strong></li>
        <li><strong>Adafruit GFX Library</strong></li>
        <li><strong>Adafruit SSD1306</strong></li>
      </ul>
    </li>
  </ul>

  <h3>Passos</h3>
  <ol>
    <li><strong>Conecte os Sensores e o Display</strong>: Monte o circuito conforme a seção de conexões acima.</li>
    <li><strong>Configure o Código</strong>: Adicione as credenciais de Wi-Fi e Adafruit IO.</li>
    <li><strong>Compile e Envie o Código para o ESP32</strong>: Carregue o código usando a IDE Arduino.</li>
    <li><strong>Monitore os Dados</strong>: Veja as leituras no monitor serial, no display OLED e na plataforma Adafruit IO.</li>
  </ol>

  <h2>Saída Esperada</h2>

  <h3>Monitor Serial</h3>
  <pre><code>
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
  </code></pre>

  <h3>Display OLED</h3>
  <pre><code>
Sensores - Dados:
Temp: 28.9 C
Umid: 69.2 %
Qualidade: Boa
  </code></pre>

  <h3>Plataforma Adafruit IO</h3>
  <p>Os dados serão enviados para os feeds configurados e poderão ser monitorados em tempo real.</p>

  <h2>Gráficos e Análise</h2>
  <p>Os tempos médios de leitura foram calculados para avaliar a eficiência do sistema:</p>
  <ul>
    <li><strong>DHT22</strong>: ~5.6 ms.</li>
    <li><strong>MQ-135</strong>: ~33 µs.</li>
  </ul>
  <p>Dados como temperatura e umidade podem ser representados em gráficos para mostrar tendências ao longo do tempo.</p>

  <h2>Referências</h2>
  <ul>
    <li>Protocolo MQTT: <a href="http://mqtt.org" target="_blank">mqtt.org</a></li>
    <li>Adafruit IO: <a href="https://io.adafruit.com/" target="_blank">io.adafruit.com</a></li>
    <li>Sensor DHT22: <a href="https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf" target="_blank">Datasheet</a></li>
    <li>Sensor MQ-135: <a href="https://www.sparkfun.com/datasheets/Sensors/Biometric/MQ-135.pdf" target="_blank">Datasheet</a></li>
  </ul>

  <h2>Licença</h2>
  <p>Este projeto é de código aberto, disponível para uso e modificação.</p>
</body>
