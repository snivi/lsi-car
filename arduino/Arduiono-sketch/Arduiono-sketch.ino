
#include <Servo.h>
#include <PPMReader.h>

int incomingByte = 0;
Servo esc;  // Control the speed
Servo volant; //Controle the direction
// 1000 => Counter clockwise
const int MINI = 1000;
// 2000 => fully clockwise
const int MAXI = 2000;
unsigned long FlagAuto ;

int interruptPin = 2;
int channelAmount = 6;
PPMReader ppm(interruptPin, channelAmount);

int CourbeMoteur[32]=
{ 1490,1480,1470,1460,1450,1445,1440,1435,1420,1425,1410,1405,1400,1375,1350,1325,1300,1275,1250,1225,1200,1175,1150,1125,1000,0};

void setup() {
  Serial.begin(9600);
  Serial.write("\nInit\n");
  esc.attach(7);
  esc.writeMicroseconds(1500);
  volant.attach(6);
  volant.writeMicroseconds(1500);
}

unsigned long ReversMoteur(unsigned long valeur )
{
  Serial.println();
  Serial.print(String(valeur));
  Serial.println();
  if ( valeur == 0 ) return valeur;
  if ( valeur < MINI ) valeur = MINI;
  if ( valeur > MAXI ) valeur = MAXI;

  valeur = (valeur - MINI) / (int)20 +1;
  Serial.print(valeur);
  Serial.println();
  return ( CourbeMoteur[valeur] );
}

void loop() {
    volant.writeMicroseconds(ppm.latestValidChannelValue(1, 0));
    esc.writeMicroseconds(ReversMoteur(ppm.latestValidChannelValue(3, 0)));
    FlagAuto = ppm.latestValidChannelValue(6, 0); // Choix auto ou manuel   
}
