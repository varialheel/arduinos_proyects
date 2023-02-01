#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//Ponemos la dirección MAC de la Ethernet Shield
IPAddress ip(192,168,1,177); //Asignamos  la IP al Arduino
EthernetServer server(80); //Creamos un servidor Web con el puerto 80 que es el puerto HTTP por defecto
 
void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
 
  // Inicializamos la comunicación Ethernet y el servidor
  Ethernet.begin(mac, ip);
  server.begin();
  
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
}
 
void loop()
{
  EthernetClient client = server.available(); //Creamos un cliente Web
  //Verificamos si se detecte un cliente a través de una petición HTTP
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true; //Una petición HTTP acaba con una línea en blanco
    String cadena=""; //Creamos una cadena de caracteres vacía
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();//Leemos la petición HTTP carácter por carácter
        Serial.write(c);//Visualizamos la petición HTTP por el Monitor Serial
        if(cadena.length()<50)
        {
                    cadena.concat(c);//concatenmos el String 'cadena' con la petición HTTP (c). De esta manera convertimos la petición HTTP a un String
           
                   //Ya que hemos convertido la petición HTTP a una cadena de caracteres, ahora podremos buscar partes del texto.
                   int posicion=cadena.indexOf("Data="); //Guardamos la posición de la Palabra "Data=" a la variable 'posicion'
                   int endPosition =  cadena.indexOf(";");
                   String data = cadena.substring((posicion+5),endPosition);
                   int longi = cadena.length();
                   cadena.replace("%20"," ");
                    if(posicion>=0)//Si en la posición hay "Data=1"
                    {
                      if () {
                      statements
                      }
                      lcd.setCursor(0, 0);
                      lcd.print();
                    }    
        }
        //Cuando reciba una línea en blanco, quiere decir que la petición HTTP ha acabado y el servidor Web está listo para enviar una respuesta
        if (c == 'n' && currentLineIsBlank) {
 
            // Enviamos al cliente una respuesta HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("<html>Conexión realizada con exito</html>");
            break;
        }
        if (c == 'n') {
          currentLineIsBlank = true;
        }
        else if (c != 'r') {
          currentLineIsBlank = false;
        }
      }
    }
    //Dar tiempo al navegador para recibir los datos
    delay(1);
    client.stop();// Cierra la conexión
  }
  
}