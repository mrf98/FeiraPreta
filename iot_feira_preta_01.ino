#include <RestClient.h>
#include <UIPEthernet.h>
const int qtdeLEDs = 5;
const int pinosLEDs[] = {7, 3, 4, 5, 6};
int intervalo_atualizacao = 1000;

// Enter a MAC address for your controller below.
byte mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xF1, 0x77};

EthernetClient client;
RestClient restClient("192.168.2.36", 3000, client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if (Ethernet.begin(mac)) {
    Serial.println(Ethernet.localIP());
  } else {
    Serial.println(F("Falha na inicialização Ethernet"));
  }
}

void loop() {
  char resposta[16] = {};
  int statusCode = restClient.get("/", resposta, 16);
  if (statusCode == 200) {
    Serial.println(F("Recebi resposta"));
    char voto = resposta[0];
    voto = voto - '0';
    Serial.println(resposta);
    atualizarLampadas(voto);
  } else {
    Serial.println(F("Falhou!"));
    Serial.println(statusCode);
  }

  resposta[0] = 0;

  delay(intervalo_atualizacao);
}

void atualizarLampadas(int voto) {
  int ledsAAcender = 0;
  switch (voto) {
    case 1:
      ledsAAcender = 1;
      break;
    case 2:
      ledsAAcender = 2;
      break;
    case 3:
      ledsAAcender = 3;
      break;
    case 4:
      ledsAAcender = 4;
      break;
    case 5:
      ledsAAcender = 5;
      break;
  }

  for (int i = 0; i < qtdeLEDs; i++) {
    digitalWrite(pinosLEDs[i], i < ledsAAcender ? HIGH : LOW);
  }
}
