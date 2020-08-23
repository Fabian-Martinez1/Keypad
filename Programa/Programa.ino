int SUBIR=2;
int BAJAR=3;
int ConfirmarOpcion=5;
int ConfirmarLetra=4;


int tecla=0;    //Para ver la posicion del arreglo tecladoABC
int confirmar=0;
char letra="";
int contador=0;
int contadorB=0;  //El contador que utilizo para medir el tiempo por palabra, en lugar de poner un "delay()"
char *tecladoABC[27] = 
{  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'ñ', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'  };

String opciones= "";
//__________________________________________________________________________________________________________________________________________________________________________________________
void setup()
{
    Serial.begin(9600);
    pinMode(SUBIR, INPUT_PULLUP);
    pinMode(BAJAR, INPUT_PULLUP);
    pinMode(ConfirmarLetra, INPUT_PULLUP);
    pinMode(ConfirmarOpcion, INPUT_PULLUP);
    
     
}
//__________________________________________________________________________________________________________________________________________________________________________________________
void loop()
{
    botonera();

}
//__________________________________________________________________________________________________________________________________________________________________________________________


void botonera()
{          
    subir();
    bajar();
    FConfirmarLetra();
    FConfirmarOpcion();
    FuncionABC();
}
//__________________________________________________________________________________________________________________________________________________________________________________________
void subir()
{
    if((digitalRead(SUBIR)==LOW))
    {
        contadorB++;
        if(contadorB==1)
        {
            letra=tecladoABC[tecla];
            Serial.print(letra);
            tecla++;
        }
        if(contadorB==10000)
        {
            contadorB=0;
        }
     }        //Este numero es 4000 ya que el contador al mantenerse apretado por un cierto periodo de tiempo se ejecuta varias veces y la ideas es que solo ejecute una letra a la vez, ya que el numero es mas chico, aparecerian mas de una letra en el display        
}
//__________________________________________________________________________________________________________________________________________________________________________________________
void bajar()
{   
      
        if((digitalRead(BAJAR)==LOW))
        {
            contadorB++;
            if(contadorB==1)
            {
                letra=tecladoABC[tecla];
                Serial.print(letra);
                tecla--;  
            }
            if(contadorB==10000)
            {
                contadorB=0;
            }
        }
  
  }
//__________________________________________________________________________________________________________________________________________________________________________________________
void FConfirmarLetra()
{
    if(digitalRead(ConfirmarLetra)==LOW)
    {
        
         contadorB++;
         if(contadorB==1)
         {
            opciones=opciones+letra;
            Serial.println("");
            Serial.println("Letra confirmada:");
            Serial.println(letra);
            contador++;
          }
          if(contadorB==10000)
          {
             contadorB=0;
          }
   }
}
//__________________________________________________________________________________________________________________________________________________________________________________________

void FConfirmarOpcion()
{
    if(digitalRead(ConfirmarOpcion)==LOW)
    {
        contadorB++;
        if(contadorB==1)
        {
            Serial.println("Su palabra es:");
            for(int i=0;i<contador;i++)
            {
                opciones[i];
                Serial.print(opciones[i]);
            }
            Serial.println();
        }
        if(contadorB==10000)
        {
            contadorB=0;
        }  
    }
}
//__________________________________________________________________________________________________________________________________________________________________________________________
void FuncionABC()
{
if (tecla==27)    //Cuando letra llega a el numero maximo del abcdario vuelve a empezar
    {
        tecla=0;
    }
    if(tecla<0)
    {
        tecla=26;
    }  
  
}
//__________________________________________________________________________________________________________________________________________________________________________________________
