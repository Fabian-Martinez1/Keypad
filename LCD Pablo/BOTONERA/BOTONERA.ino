/*SSD1306_begin() : Initialize the OLED Display.
SSD1306_clear(…) : Clean the Display.
SSD1306_string(x position, y position,… ) : Add a text to buffer.
SSD1306_char3216(x position, y position,…) : Add a catheter to buffer.
SSD1306_display(name of buffer) : Show the buffer on Display.
char c[10]; sprintf (c,"%d", boton3);
SSD1306_string(2, 19, c, 12, 10, oled_buf);
*/
#include <SPI.h>
#include <Wire.h>
#include "ssd1306.h"
#include <EEPROM.h>

#define VCCSTATE SSD1306_SWITCHCAPVCC
#define WIDTH     128
#define HEIGHT     64
#define PAGES       8

#define OLED_RST    9 
#define OLED_DC     8
#define OLED_CS    10
#define SPI_MOSI   11    /* connect to the DIN pin of OLED */
#define SPI_SCK    13     /* connect to the CLK pin of OLED */

int seleccionar;
int boton1;
int boton2;
int boton3;
uint8_t oled_buf[WIDTH * HEIGHT / 8];


const uint8_t g3 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0F, 0x06, 0x30, 0x00, 0x00, 0x00, 0x01, 0xFE, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x06, 0x20, 0x00, 0x00, 0x00, 0x03, 0xFC, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x76, 0x0C, 0x60, 0x00, 0x00, 0x00, 0x00, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xE6, 0x0C, 0x60, 0x00, 0x00, 0xC0, 0x00, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xCE, 0x0C, 0xC0, 0x01, 0x01, 0x80, 0x00, 0xC1, 0x80, 0x00, 0x00, 0x00, 0x03, 0x00,
0x00, 0x1F, 0xFF, 0x18, 0xF0, 0xE3, 0xF3, 0xC0, 0x1C, 0xC1, 0xF0, 0x70, 0xBB, 0x87, 0x43, 0x00,
0x00, 0xFF, 0xFF, 0x18, 0xF9, 0xF3, 0xF7, 0xC0, 0x7E, 0xC1, 0xF1, 0xF9, 0xFF, 0x8F, 0xC7, 0x00,
0x01, 0xC3, 0x18, 0x31, 0x99, 0xF2, 0xC3, 0x00, 0xF1, 0x83, 0x31, 0x99, 0x99, 0x8C, 0xC7, 0x80,
0x03, 0x87, 0x18, 0x31, 0x9B, 0xF3, 0x83, 0x01, 0xC1, 0x83, 0x33, 0x19, 0x19, 0x98, 0x85, 0x80,
0x07, 0x06, 0x38, 0x23, 0x1B, 0x01, 0x86, 0x01, 0x83, 0x06, 0x23, 0x1B, 0x33, 0x19, 0x81, 0x80,
0x06, 0x0E, 0x3E, 0x7B, 0xF3, 0xF9, 0xF7, 0x83, 0x83, 0x06, 0x7B, 0xF3, 0x33, 0xDF, 0xEF, 0x80,
0x06, 0x0C, 0x1E, 0x7B, 0xE1, 0xF0, 0xF7, 0x83, 0x03, 0x04, 0x79, 0xE2, 0x23, 0xCE, 0xEF, 0x00,
0x06, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x07, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x03, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void setup() {

  pinMode(4,INPUT);
  pinMode(3,INPUT);
  pinMode(2,INPUT);
  SSD1306_begin();
  SSD1306_clear(oled_buf);
  SSD1306_bitmap(0, 0, g3, 128, 64, oled_buf);
  SSD1306_display(oled_buf);
delay(500);
  SSD1306_clear(oled_buf);
        //char c[10]; sprintf (c,"%f", a);
      //SSD1306_string(2, 19, c, 12, 10, oled_buf);
  SSD1306_string(14, 9, "Menu de opciones:", 12, 0, oled_buf);
  SSD1306_string(18, 48, "*Configuracion", 12, 10, oled_buf);
  SSD1306_string(18, 28, "*Elegir Opciones", 12, 10, oled_buf);
  SSD1306_display(oled_buf);
}

void loop() {
menu1();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void menu1(){
if (boton3==0)
  {
  if(digitalRead(4)==HIGH)
  {
      boton2=1;
      boton1=0;
      SSD1306_string(14, 9, "Menu de opciones:", 12, 0, oled_buf);
      SSD1306_string(18, 48, "*Configuracion", 12, 0, oled_buf);
      SSD1306_string(18, 28, "*Elegir Opciones", 12, 10, oled_buf);
      SSD1306_display(oled_buf);
  }
  else if(digitalRead(3)==HIGH)
  {
      boton1=1;
      boton2=0;
      SSD1306_string(14, 9, "Menu de opciones:", 12, 0, oled_buf);
      SSD1306_string(18, 48, "*Configuracion", 12, 10, oled_buf);
      SSD1306_string(18, 28, "*Elegir Opciones", 12, 0, oled_buf);
      SSD1306_display(oled_buf);
  }
  }
  menu_seleccionar_opciones();
  menu_opcion();
  menu_configuraciones();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void menu_seleccionar_opciones(){
if(digitalRead(2)==HIGH && boton1==1 && boton2==0)// si el boton de seleccionar se presiona y esta la opcion de "seleccionar opciones"
  {
    boton3=1; 
      SSD1306_clear(oled_buf);
      SSD1306_string(10, 19, "Opcion 1", 12, 10, oled_buf);
      SSD1306_string(10, 39, "Opcion 2", 12, 10, oled_buf);
      SSD1306_display(oled_buf);
   }      
          if(digitalRead(4)==HIGH && boton3==1 && boton1==1)
  {
      seleccionar=2;
      SSD1306_clear(oled_buf);
      SSD1306_string(10, 19, "Opcion 1", 12, 10, oled_buf);
      SSD1306_string(10, 39, "Opcion 2", 12, 0, oled_buf);
      SSD1306_display(oled_buf);
  }
          else if(digitalRead(3)==HIGH && boton3==1 && boton1==1)
  {
      seleccionar=1;
      SSD1306_clear(oled_buf);
      SSD1306_string(10, 19, "Opcion 1", 12, 0, oled_buf);
      SSD1306_string(10, 39, "Opcion 2", 12, 10, oled_buf);
      SSD1306_display(oled_buf);
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void menu_configuraciones(){
     
           if(digitalRead(2)==HIGH && boton2==1 && boton1==0)// si seleccionamos "configuracion"
  {
    boton3=1;
      SSD1306_clear(oled_buf);
      SSD1306_string(1, 1, "Escriba la opcion a modificar", 12, 10, oled_buf);
      //mostrar teclado
      SSD1306_display(oled_buf);  
  }
      SSD1306_display(oled_buf);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void menu_opcion(){
if(digitalRead(2)==HIGH && seleccionar==1 && boton1==1 && boton2==0)
{
      SSD1306_clear(oled_buf);
      SSD1306_string(2, 19, "Mostrar opcion de la EEPROM", 12, 10, oled_buf);  //mostrar EEPROM
      SSD1306_display(oled_buf); 
}
else if(digitalRead(2)==HIGH && seleccionar==2 && boton1==1 && boton2==0)
{
      SSD1306_clear(oled_buf);
      SSD1306_string(2, 19, "Mostrar opcion de la EEPROM", 12, 10, oled_buf);  //mostrar EEPROM
      SSD1306_display(oled_buf); 
}
}