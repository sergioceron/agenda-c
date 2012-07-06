/*  ------------------------------------------------------------------
 * |Archivo: agenda-main.cpp                                          |
 * |Fecha: 18-08-08                                                   |
 * |Size: 3 Kb                                                        |
 * |Descripcion: Agenda basica en modo grafico que permite el alta,   |
 * |             baja, edicion y busqueda de clientes.                |
 * |                                                                  |
 * |             Basada en la libreria winbgim para la simulacion     |
 * |             de graphics.h en Dev-C.                              |
 *  ------------------------------------------------------------------
 */
 
// Librerias estaticas
#include <stdio.h> 
#include <string.h> 
#include <conio.h> 
#include <dos.h>
#include <time.h>
#include <winbgim.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Algunas definiciones
#define true 1
#define false 0

// Librerias extra
#include "texto.h"
#include "images.h"
#include "c-gui.h"
#include "utils.h"
#include "agenda.h"
#include "events.h"
#include "interfaz.h"


int menu();

int main()
{ 
   initwindow( 800,600 );
   
   settextstyle(2,0,4);
   
   loading();
   
   settextstyle( 11, 0, 10);
       
   int op, code, multi; 
   page p;
   
   do
   { 
     switch( op = menu() )
     {
        case 1:
           
           putimage( 0, 0, imagen, COPY_PUT );
           
           nuevo();
           
           cleardevice();
           break; 
        case 3: 
           putimage( 0, 0, imagen, COPY_PUT );
           
           p = listar(0);
           code = p.code;
           multi = p.multi;
           
           if( code >= 2 && code < 15 ){
               cleardevice();
               editar( code-2 + (13*multi) );
           }else if( code >= 15 ){
               cleardevice();
               borrar( code-15 + (13*multi), FILE_NAME );  
           }
           cleardevice();
           break; 
        case 2: 
           putimage( 0, 0, imagen, COPY_PUT );
           
           code = encontrar();
           if( code == 0 )
           {
               FILE_NAME = "find.$$$";
               
               putimage( 0, 0, imagen, COPY_PUT );
               
               p = listar(0);
               code = p.code;
               multi = p.multi;
               
               if( code >= 2 && code < 15 ){
                   cleardevice();
                   editar( code-2 + (13*multi) );
               }else if( code >= 15 ){
                   cleardevice();
                   borrar( code-15 + (13*multi), FILE_NAME );  
               }
               system( "del find.$$$" );
               FILE_NAME = "agenda.dat";
           }    
           cleardevice();
           break; 
        default : 
           exit(0);
           printf("Opcion no valida"); 
           break; 
     }

   }while(1);

   return 0;
  
} 


int menu() 
{
   putimage( 0, 0, imagen, COPY_PUT );
   int sxm = 150, sym=150, w = 120, h=40;
   int sph = 50, spv = 50, item = 0;
   Boton *b = ( Boton *)malloc( sizeof( Boton ) * 4 );;

   b[0].put( sxm, sym, w, h, "Ingresar" );
   b[1].put( sxm, sym+h+spv, w, h, "Buscar" );
   b[2].put( sxm, sym+2*(h+spv), w, h, "Listar" );
   b[3].put( sxm, sym+3*(h+spv), w, h,"Salir" );

   item = eventHandler( NULL, &b, 0, 4 )+1;
   cleardevice();
   
   return item; 
}

