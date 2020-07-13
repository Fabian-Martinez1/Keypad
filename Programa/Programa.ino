int SUBIR=2;
int BAJAR=3;
int tecla=0;
int CONFIRMAR=4;
bool activarABC=false;
char *tecladoABC[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "ñ", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
char opciones[20][19]= {{"" },{""}};
//__________________________________________________________________________________________________________________________________________________________________________________________
void setup()
{
    Serial.begin(9600);
    pinMode(SUBIR, INPUT);
    pinMode(BAJAR, INPUT);
    pinMode(ConfirmarLetra, INPUT);
    pinMode(ConfirmarOpcion, INPUT);
    pinMode(6, OUTPUT);
}
//__________________________________________________________________________________________________________________________________________________________________________________________
void loop()
{

    
    botonera();  

}
//__________________________________________________________________________________________________________________________________________________________________________________________
void botonera()
{
   
    if((digitalRead(SUBIR)==HIGH)&&(tecla<=27))
    {
        subir();
    
    }
   if((digitalRead(BAJAR)==HIGH)&&(tecla>=0))
   {
      bajar();
        
   }
   if(digitalRead(CONFIRMARLETRA)==HIGH)
   {
    confirmarLetra();
    }
  if (tecla>27){           //Cuando la tecla llega a la "z" se reinicia y cuando llega a "cero", continua con la "z"
    tecla=0;
    }
  if (tecla<0)
  {
    tecla=27;
    }
}
//__________________________________________________________________________________________________________________________________________________________________________________________
void subir()
{

        
        digitalWrite(5, HIGH);
        
        Serial.println(tecladoABC[tecla]);
        tecla++;
        delay(200);
        digitalWrite(5,LOW);
}
//__________________________________________________________________________________________________________________________________________________________________________________________
void bajar()
{
  
        digitalWrite(6, HIGH);
        
        Serial.println(tecladoABC[tecla]);
        tecla--;
        delay(200);
        digitalWrite(6,LOW);
  
  
  }
//__________________________________________________________________________________________________________________________________________________________________________________________
void confirmarLetra()
{
   opciones[][]={{},{}};
    
}
