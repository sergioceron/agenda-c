/*  ------------------------------------------------------------------
 * |Archivo: texto.h                                                  |
 * |Fecha: 18-08-08                                                   |
 * |Size: 9 Kb                                                        |
 * |Descripcion: Libreria que simula las funciones basicas de stdio.h |
 * |              y conio.h en modo grafico.                          |
 * |                                                                  |
 *  ------------------------------------------------------------------
 */
 
#include <stdarg.h>
const int BUFSIZE = 140;                //tamaño del buffer de captura
const char CR=13;			//Codigo de tecla ENTER
const char BS=8;                        //Codigo de la tecla RETROCESO
const char ESC=27;	                //Codigo de la tecla ESC
  



//*** GPRINTFXY
//Una funcion  printf() para graficos imprimira el texto en la posicion xloc y yloc
//no se afecta la posicion actual
int gprintfxy(int xloc, int yloc, char *fmt, ... );


//*** GPRINTF
//Una funci¢n  printf() para elementos  gr ficos. Actualizar   la posici¢n actual.
//Asume justificaci¢n a la izquierda LEFT_TEXT y HORIZ_DIr

int gprintf( char *fmt, ... );


 //*** GGETCHE
 //Funcion getche() para elementos graficos
 int ggetche(void);


  //*** GPUTCH 
  //Funcion  putch() para elementos graficos
  int gputch(int c);


  //*** GGETS
  // Una rutina para entrada de textos en modo grafico. Regresa el texto tecleado
  // Escribe  en pantalla el texto mientras se esta tecleando.
  // Soporta el caracter de retroceso.
  char *ggets(char *buffer, int max);


//*** SCANF
// Una funcion  scanf() para elementos graficos. Actualiza la posicion actual
// Asume alineacion izquierda LEFT_TEXT y HORIZ_DIR
int gscanf(int size, char *fmt, ... );

 //*** GSCANFXY 
 //Una funcion scanf() para elemntos graficos. No afecta la posicion actual
 // y escribe lo que se va tecleando en la posicion (xloc,yloc).
 // Asume alineacion izquierda LEFT_TEXT y HORIZ_DIR
 int gscanfxy(int size, int xloc, int yloc, char *fmt, ... );

//*** GPRINTFXY
//Una funcion  printf() para graficos imprimira el texto en la posicion xloc y yloc
//no se afecta la posicion actual
int gprintfxy(int xloc, int yloc, char *fmt, ... )
{
  va_list argptr;                  //apuntador a la lista de argumentos
  char str[BUFSIZE];					//buffer donde se armara el texto
  int cnt;								//resultado de la conversion de sprintf()
  struct fillsettingstype oldfill; //parametros actaules de relleno
  char userfillpattern[8];         //patron de relleno de usuario

  va_start(argptr,fmt);     ///iniacializa las funciones va_
  cnt = vsprintf(str,fmt,argptr);  //escribe el texto en el buffer
  if(str[0]==NULL) return (0);

  //borra el espacio  donde se imprimira el texto
  getfillsettings(&oldfill);
  if(oldfill.pattern == USER_FILL)
	 getfillpattern(userfillpattern);
  setfillstyle(SOLID_FILL,getbkcolor());
  bar(xloc,yloc,xloc+textwidth(str),yloc+textheight("H")*5/4);
  if (oldfill.pattern==USER_FILL)
     setfillpattern(userfillpattern,oldfill.color);
  else
     setfillstyle(oldfill.pattern,oldfill.color);
  outtextxy(xloc,yloc,str);   //escribe  el texto en la pantalla
  va_end(argptr);   //termina las funciones va_
  return(cnt);   //regresa el contador de conversion
}



//*** GPRINTF
//Una funci¢n  printf() para elementos  gr ficos. Actualizar   la posici¢n actual.
//Asume justificaci¢n a la izquierda LEFT_TEXT y HORIZ_DIr

int gprintf( char *fmt, ... )
{
  va_list  argptr;     	//apuntador a la lista de argumentos
  char str[BUFSIZE];  	//Buffer donde se armara el texto
  int cnt;              //Resultado de la conversion de sprintf()
  struct fillsettingstype oldfill; //Parametros actuales de relleno
  char userfillpattern[8]; //Patron de relleno del usuario
  int xloc, yloc;	//Posicion actual

  va_start(argptr,fmt);	//Inicializa la fucnion va_
  cnt=vsprintf(str,fmt,argptr); //Escribe le texto en el buffer
  //Borra el espacio  donde se imprimrira el texto
  xloc=getx(); yloc=gety();
  getfillsettings(&oldfill);
  if (oldfill.pattern == USER_FILL)
     getfillpattern(userfillpattern);
  setfillstyle(SOLID_FILL,getbkcolor());
  bar(xloc, yloc,xloc+textwidth(str),yloc+textheight("H")+5/4);
  if (oldfill.pattern == USER_FILL)
    setfillpattern(userfillpattern,oldfill.color);
  else
    setfillstyle(oldfill.pattern,oldfill.color);
  outtext(str);		//Escribe el texto en la pantalla
  va_end(argptr);	//Termina las funciones va_
  return(cnt);  	//Regresa  el contador de conversion
 }


 //*** GGETCHE
 //Funcion getche() para elementos graficos
 int ggetche(void)
 {
   char ch;

   ch=getch();		//Lee el caracter sin escribirlo en la pantalla
   gprintf("%c",ch);	//Escribe el caracter
   return(ch);
  }


  //*** GPUTCH 
  //Funcion  putch() para elementos graficos
  int gputch(int c)
  {
   char buffer[2];

   sprintf(buffer,"%c",c);
   gprintf(buffer);
   return(c);
   }


  //*** GGETS
  // Una rutina para entrada de textos en modo grafico. Regresa el texto tecleado
  // Escribe  en pantalla el texto mientras se esta tecleando.
  // Soporta el caracter de retroceso.
  char *ggets(char *buffer, int max)
  {
    int currloc, maxchars, oldcolor;
    struct viewporttype view;
    char ch, charbuff[3];

    buffer[0] = '\0';
    currloc = 0;
    getviewsettings(&view);
    maxchars = max;//(view.right -getx())/ textwidth("M") - 1;
  if (maxchars <= 0) return (NULL);
  gprintfxy(getx(),gety(), "_");

  while((ch=getch()) != CR )
  {   //tecla enter

    if (ch==BS) {   		//tecla retroceso
      if (currloc > 0 ) {
	 currloc --;
	 if (currloc <= maxchars) {
	   oldcolor= getcolor();
	   setcolor(getbkcolor());
	   sprintf(charbuff,"%c",buffer[currloc]);
	   gprintfxy(getx()-textwidth(charbuff),gety(),"%c_",buffer[currloc]);
	   setcolor(oldcolor);
	   moveto(getx()-textwidth(charbuff), gety());
	   }
	  }
	 }
	else {
	 if (currloc < maxchars) {
	   oldcolor = getcolor();
	   setcolor(getbkcolor());
	   gprintfxy(getx(),gety(), "_");
	   setcolor(oldcolor);
	   buffer[currloc] = ch;
	   gputch(ch);
	   currloc++;
	   }
	  // else
	     //putch(0x07);
	  }
	  if (currloc < maxchars)
	    gprintfxy(getx(),gety(),"_");
	 }
	 if (currloc <= maxchars ) {
	    oldcolor = getcolor();
	    setcolor(getbkcolor());
	    gprintfxy(getx(),gety(), "_");
	    setcolor(oldcolor);
	    }
	   buffer[currloc] = '\0';
	   return(buffer);
	 }


//*** SCANF
// Una funcion  scanf() para elementos graficos. Actualiza la posicion actual
// Asume alineacion izquierda LEFT_TEXT y HORIZ_DIR
int gscanf(int size, char *fmt, ... )
{
 va_list argptr;		//apuntador  a la lista de argumentos
 char str[BUFSIZE];		//Buffer para recibir la entrada de texto
 int cnt;			//Numero de campos convertidos

 va_start(argptr,fmt);		//Inicializa las funciones  va_
 ggets(str, size);			//Lee el texto tecleado
 cnt = vsscanf(str,fmt,argptr);	//Convierte el texto leido de acuerdo
				//con el formato
 va_end(argptr);		// Termina las fucniones va_
 return (cnt);			//Regresa el numero de conversiones
				//efectuadas correctamente
 }

 //*** GSCANFXY 
 //Una funcion scanf() para elemntos graficos. No afecta la posicion actual
 // y escribe lo que se va tecleando en la posicion (xloc,yloc).
 // Asume alineacion izquierda LEFT_TEXT y HORIZ_DIR
 int gscanfxy(int size, int xloc, int yloc, char *fmt, ... )
 {
   va_list argptr;	//Apuntador a la lista de argumentos
   char str[BUFSIZE];	//Buffer para recibir la entrada de texto
   int cnt;		// Numero de campos convertidos
   int oldx, oldy;	//Posici¢n actual original

   oldx=xloc;		//Guarda  la posicion actual para que despues
   oldy=yloc;		//pueda ser restaurada
   moveto(xloc,yloc);	//Se mueve a la posicon actual
   va_start(argptr,fmt); //inicializa las funciones va_
   ggets(str, size);		// Lee lo tecleado por el usuario
   cnt=vsscanf(str,fmt,argptr); //Convierte  el texto leido
   va_end(argptr);	//Termina las funciones var_
   moveto(oldx,oldy);	//Restaura la posicion actual
   return(cnt);	//Regresa el contador de conversiones
  }
