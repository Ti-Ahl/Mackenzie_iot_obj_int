#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configurações do display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Configuração do sensor DHT
#define DHTPIN 4       // Pino onde o DHT está conectado
#define DHTTYPE DHT22  // Tipo do sensor (DHT22)
DHT dht(DHTPIN, DHTTYPE);

// Configuração do sensor MQ-135
#define MQ135_AOUT_PIN 15  // Pino analógico do MQ-135
#define MQ135_DOUT_PIN 23  // Pino digital do MQ-135

// Configuração do Wi-Fi
char ssid[] = "Mansao Foster";
char pass[] = "Bummer12345";

// Configuração do Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "silalti"
#define AIO_KEY         "aio_OJZq167Fy0SSiBJKBIivsYHFfOR2"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Feeds do Adafruit IO
Adafruit_MQTT_Publish temperaturaFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperatura");
Adafruit_MQTT_Publish umidadeFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/umidade");
Adafruit_MQTT_Publish mq135QualityFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/mq135_quality");

// Variáveis para medições de tempo
unsigned long startTime, endTime;

void connectToWiFi() {
  Serial.print("Conectando ao Wi-Fi...");
  display.setCursor(0, 20);
  display.println("Conectando ao Wi-Fi...");
  display.display();
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.print(".");
    display.display();
  }

  Serial.println("Conectado!");
  display.println("Conectado ao Wi-Fi!");
  display.display();
}

void connectToMQTT() {
  Serial.print("Conectando ao Adafruit IO...");
  while (mqtt.connect() != 0) {
    Serial.println(mqtt.connectErrorString(mqtt.connect()));
    Serial.println("Tentando novamente em 5 segundos...");
    delay(5000);
  }
  Serial.println("Conectado ao Adafruit IO!");
}

String getAirQuality(int analogValue) {
  if (analogValue < 300) {
    return "Boa";
  } else if (analogValue < 700) {
    return "Moderada";
  } else {
    return "Ruim";
  }
}

void sendSensorData() {
  // Leitura do sensor DHT22
  unsigned long startTime = micros();  // Marca o tempo inicial para a leitura
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  unsigned long endTime = micros();    // Marca o tempo após a leitura
  unsigned long dhtTime = endTime - startTime;  // Calcula o tempo gasto em µs

  // Leitura do sensor MQ-135
  startTime = micros();  // Marca o tempo inicial para o sensor MQ-135
  int mq135AnalogValue = analogRead(MQ135_AOUT_PIN);
  String airQuality = getAirQuality(mq135AnalogValue);
  endTime = micros();    // Marca o tempo após a leitura
  unsigned long mq135Time = endTime - startTime;  // Calcula o tempo em µs

  // Publica os dados no Adafruit IO
  if (!temperaturaFeed.publish(temperatura))
    Serial.println("Erro ao publicar temperatura!");

  if (!umidadeFeed.publish(umidade))
    Serial.println("Erro ao publicar umidade!");

  if (!mq135QualityFeed.publish(airQuality.c_str()))
    Serial.println("Erro ao publicar qualidade do ar!");

  // Mostra os dados no monitor serial
  Serial.println("----- Dados do Sensor -----");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");
  Serial.print("Qualidade do ar: ");
  Serial.println(airQuality);
  Serial.print("Tempo leitura DHT (us): ");
  Serial.println(dhtTime);
  Serial.print("Tempo leitura MQ-135 (us): ");
  Serial.println(mq135Time);

  // Verifica condições de alerta
  bool alerta = false;
  String alertaMensagem;

  if (temperatura > 30) {
    alerta = true;
    alertaMensagem = "Temp fora do nivel: " + String(temperatura) + " C";
  } else if (temperatura < 20) {
    alerta = true;
    alertaMensagem = "Temp fora do nivel: " + String(temperatura) + " C";
  }

  if (umidade > 70) {
    alerta = true;
    alertaMensagem = "Umid fora do nivel: " + String(umidade) + " %";
  }

  // Mostra os dados ou alerta no display OLED
  startTime = micros();  // Marca o tempo inicial para o display
  display.clearDisplay();

  if (alerta) {
    display.setCursor(0, 0);
    display.println("ALERTA:");
    display.setCursor(0, 15);
    display.println(alertaMensagem);
  } else {
    display.setCursor(0, 0);
    display.println("Sensores - Dados:");
    display.setCursor(0, 15);
    display.print("Temp: ");
    display.print(temperatura);
    display.println(" C");

    display.setCursor(0, 30);
    display.print("Umid: ");
    display.print(umidade);
    display.println(" %");

    display.setCursor(0, 45);
    display.print("Qualidade: ");
    display.println(airQuality);
  }
  display.display();

  endTime = micros();  // Marca o tempo após atualizar o display
  unsigned long displayTime = endTime - startTime;  // Calcula o tempo do display em µs

  Serial.print("Tempo atualização OLED (us): ");
  Serial.println(displayTime);
}

void setup() {
  Serial.begin(115200);

  // Inicializa o DHT
  dht.begin();

  // Inicializa o display OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Endereço padrão: 0x3C
    Serial.println("Falha ao inicializar o display OLED");
    while (true); // Travar em caso de falha
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Inicializando...");
  display.display();

  // Configura os pinos do MQ-135
  pinMode(MQ135_AOUT_PIN, INPUT); // Pino analógico

  // Conecta ao Wi-Fi
  connectToWiFi();

  // Conecta ao Adafruit IO
  connectToMQTT();
}

void loop() {
  // Garante a conexão com o MQTT
  if (!mqtt.ping()) {
    mqtt.disconnect();
    connectToMQTT();
  }

  sendSensorData();         // Envia dados para o Adafruit IO e exibe no OLED
  delay(10000);             // Aguarda 10 segundos entre cada leitura
}
