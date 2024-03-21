// #define analogPin 0          
// #define chargePin 13         
// #define dischargePin 12      
// #define resistorValue 10000.0F   

// unsigned long startTime;
// unsigned long elapsedTime;
// float microFarads;                
// float nanoFarads;

// void setup(){
//   pinMode(chargePin, OUTPUT);     
//   digitalWrite(chargePin, LOW);  
//   Serial.begin(9600);             
// }

// void loop(){
//   digitalWrite(chargePin, HIGH);  
//   startTime = millis();
//   while(analogRead(analogPin) < 648){       
//   }

//   elapsedTime= millis() - startTime;
//   microFarads = ((float)elapsedTime / resistorValue) * 1000;   
//   Serial.print(elapsedTime);       
//   Serial.print(" mS    ");         

//   if (microFarads > 1){
//     Serial.print((long)microFarads);       
//     Serial.println(" microFarads");    
//       delay(1000);      
//   }

//   else{
//     nanoFarads = microFarads * 1000.0;      
//     Serial.print((long)nanoFarads);         
//     Serial.println(" nanoFarads");          
//     delay(1000); 
//   }

//   digitalWrite(chargePin, LOW);            
//   pinMode(dischargePin, OUTPUT);            
//   digitalWrite(dischargePin, LOW);          
//   while(analogRead(analogPin) > 0){         
//   }

//   pinMode(dischargePin, INPUT);            

// }


// small value





const int OUT_PIN = A4;
const int IN_PIN = A3;
const float IN_STRAY_CAP_TO_GND = 24.48;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;  
const int MAX_ADC_VALUE = 1023;

void setup(){
  pinMode(OUT_PIN, OUTPUT);
  pinMode(IN_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop(){
    pinMode(IN_PIN, INPUT);
    digitalWrite(OUT_PIN, HIGH);
    int val = analogRead(IN_PIN);
    digitalWrite(OUT_PIN, LOW);

    // if(val==0){
    //   Serial.print("0");
    // }

    if (val < 1000){
      pinMode(IN_PIN, OUTPUT);

      float capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);

      Serial.print(F("Capacitance Value = "));
      Serial.print(capacitance, 3);
      Serial.print(F(" pF ("));
      Serial.print(val);
      Serial.println(F(") "));
      delay(800);
    }

    else{
      pinMode(IN_PIN, OUTPUT);
      delay(1);
      pinMode(OUT_PIN, INPUT_PULLUP);
      unsigned long u1 = micros();
      unsigned long t;
      int digVal;

      do{
        digVal = digitalRead(OUT_PIN);
        unsigned long u2 = micros();
        t = u2 > u1 ? u2 - u1 : u1 - u2;
      } while ((digVal < 1) && (t < 400000L));

      pinMode(OUT_PIN, INPUT);  
      val = analogRead(OUT_PIN);
      digitalWrite(IN_PIN, HIGH);
      int dischargeTime = (int)(t / 1000L) * 5;
      delay(dischargeTime);   
      pinMode(OUT_PIN, OUTPUT);  
      digitalWrite(OUT_PIN, LOW);
      digitalWrite(IN_PIN, LOW);

      float capacitance = -(float)t / R_PULLUP / log(1.0 - (float)val / (float)MAX_ADC_VALUE);

      Serial.print(F("Capacitance Value = "));
      if (capacitance > 1000.0){
        Serial.print(capacitance / 1000.0, 2);
        Serial.print(F(" uF"));
          delay(800);
      }
      else{
        Serial.print(capacitance, 2);
        Serial.print(F(" nF"));
          delay(800);
      }

      Serial.print(F(" ("));
      Serial.print(digVal == 1 ? F("Normal") : F("HighVal"));
      Serial.print(F(", t= "));
      Serial.print(t);
      Serial.print(F(" us, ADC= "));
      Serial.print(val);
      Serial.println(F(")"));
    }
    while (millis() % 1000 != 0);    
}