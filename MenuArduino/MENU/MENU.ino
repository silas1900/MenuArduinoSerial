//=============================================================================================================================================================================================
/*Criando Menu utilizando monitor serial.
 * A partir do valor digitado no teclado 
 * do computador
 * 
 */
 //=============================================================================================================================================================================================
#include <DHT.h>
#include <DHT_U.h>

//======= Diretivas =============================================================================================================================================================================
#define led1 5
#define led2 6
#define DHTPIN A1
#define DHTTYPE DHT11
//==== Protótipo funções =================================================================================================================================================
//Função responsável pela aferição da temperatura e umidade
void temperaturaUmidade();

// função responsável por pisca led
void piscaLed(int qt);

// função responsável por ligar e desligar led
void ligarLed();

//Função responsável pela aferição da luminosidade
void luminosidade();

// Função responsável pelo menu
char menu();

// criando objeto para o DHT11
DHT dht(DHTPIN, DHTTYPE);
//==== Variáveis auxiliares ============================================================================================================================================
int aux = 0;
int ldr = A0;
char leitura;
//======================================================================================================================================================================
void setup(){
  
  pinMode(led1,OUTPUT);
  pinMode(led2, OUTPUT);
  dht.begin();
  Serial.begin(9600);

  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);

}

//========================================================================================================================================================================
void loop() {

    
    leitura = menu();
  
    if(leitura == '1'){ // se valor digitado for 1 chama a função 
      
      ligarLed();
     
    }else if(leitura == '2'){
      
      piscaLed(5); // pisca o led2 5 vezes
      digitalWrite(led2,LOW); // depois disliga o led2
     
    }else if(leitura == '3'){
      
      temperaturaUmidade();
    
    }else if(leitura == '4'){
      
      luminosidade();
     
    }
    
}// END Loop
//====== Função responsável pelo menu ==================================================================================================================================
char menu(){

  char options;  
  
  while(aux < 1){
    Serial.println("Escolha uma opção");

    Serial.println("1................LED1");
    
    Serial.println("2................Piscar LED2");
    
    Serial.println("3................Temperatura e umidade");
    
    Serial.println("4................Luminosidade");
    aux++;
  }// END while

 if(Serial.available() > 0){// enviar resposta apenas quando receber dados:

    options = Serial.read(); // Lê os dados recebidos na porta serial.
  
    aux = 0;
      
 }// end if

 return options;
}// END menu

//======== função responsável por ligar e desligar led ================================================================================================================
void ligarLed(){

  if(digitalRead(led1) == LOW){ // verifica se o led está desligado

      Serial.println(" Led1 ligado");
      digitalWrite(led1,HIGH); // liga led1
    
  }else{
    Serial.println("Led1 Desligado");
    digitalWrite(led1,LOW);
  }
  
} // END  ligarLed

//======== função responsável por pisca led ==========================================================================================================================
void piscaLed(int qt){
  Serial.println("Led2 piscando " + String(qt,DEC) + " vezes");

  for(int i = 0; i < qt; i++ ){
    digitalWrite(led2,HIGH);
    
    delay(1000);

    digitalWrite(led2,LOW);
    
    delay(1000);
  }//end for
      
}//END  picaLed

//======= Função responsável pela aferição da temperatura e umidade ====================================================================================================
void temperaturaUmidade(){

  float h = dht.readHumidity();         // Variável que recebe o valor da umidade relativa do ar do sensor
  float t = dht.readTemperature();     // Variável que recebe valor da temperatura

  /// testa se retorno é valido
  if(isnan(t) || isnan(t)){
      Serial.println("ERRO NA LEITURA DO SENSOR DHT11");
  }else{ // estiver tudo ok imprimi os valores 

    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
    
  }//  end else
  
}//END temperaturaUmidade

//======= Função responsável pela aferição da luminosidade ===============================================================================================================
void luminosidade(){

  int valorLdr = 0;

  // Receber a leitura do ldr
  valorLdr = analogRead(ldr);

  Serial.print("Luminosidade");
  Serial.println(valorLdr);

  delay(1000);
  
}// END luminosidade
//========================================================================= END ============================================================================================
