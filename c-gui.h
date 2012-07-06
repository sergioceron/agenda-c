/*  ------------------------------------------------------------------
 * |Archivo: c-gui.h                                                  |
 * |Fecha: 18-08-08                                                   |
 * |Size: 6 Kb                                                        |
 * |Descripcion: Contiene los componentes graficos de la agenda:      |
 * |              button y textbox.                                   |
 * |                                                                  |
 * |             Los componentes estan almacenados en una estructura  |
 * |             y basados en POO.                                    |
 *  ------------------------------------------------------------------
 */
 
#define I 35
#define S 160
#define sx 50
#define sy 100
#define tcolor 15

enum format{ ALPHA=1, INTEGER=2, REAL=3, CORREO=4 };

struct button{
   int x;
   int y;
   int w;
   int h;
   int isover;
   char texto[20];

   int draw(char *, int , int );
   void draw( char * );
   int put( int , int , int , int , char * );
   void over();
   void redraw();
   
} Button;

struct field{

	int fx, fy, fw, fh, lpos, nl, active, chars;
	int minchar;
	int focus;
	int format;
	char *text;

	void put( int x, int y, int w, int h, int maxchar );
	
	void setFormat( int f );

    void setText( char *s );

    void setMinChar( int min );

	void setfocus();

	void clear();

	void lostfocus();

	int isValid();

	int read( char c );
};

typedef struct button Boton;
typedef struct field Campo;

int button::draw(char *text, int fc, int bk )
{
     struct fillsettingstype info;
     int bkcolor = getbkcolor(), color = getcolor();
     getfillsettings( &info );
     
     setfillstyle(1,bk);
     setcolor(fc);
     bar3d( x, y, x+w, y+h, 1, 1);
     setbkcolor(bk);
     gprintfxy( x+w/2-(strlen(text)/2)*7, y+h/2-6, text );
     
     setfillstyle(info.pattern, info.color);
     setbkcolor( 0 );
     setcolor(color);
     return 0;
}

void button::draw( char *text )
{
     draw( text, 15, 4 );
     strcpy( texto, text );
     isover = 0;
}

int button::put( int _x, int _y, int _w, int _h, char *text )
{
     x = _x;
     y = _y;
     w = _w;
     h = _h;
     draw( text );

     return 0;
}

void button::over()
{
     for( int i = 0, steps=20; i < steps; i++ ){
          draw( texto, 15, COLOR(255-12*i,5*i,i*13));
          delay(30);
     }
     isover = 1;
}
   
void button::redraw()
{
     draw( texto, 15, 4 );
     isover = 0;
}

// Input

void field::put( int x, int y, int w, int h, int maxchar ){
	lpos=0;
	chars = 0;
	format = 1;
	minchar = 1;
	int c = getcolor();
	text = ( char * ) malloc( sizeof(char) * maxchar );
	
	for( int i = 0; i < maxchar; i++ )
		text[i]='\0';

	setcolor( 0 );
	setfillstyle( 1, tcolor );
	bar( x, y, x+w, y+h );
	rectangle( x, y, x+w, y+h );
	fx = x;		fy = y;
	fw = w;		fh = h;
	nl = maxchar;
	active = 1;
	setcolor( c );
}

void field::setFormat( int f )
{
     format = f;
}

void field::setText( char *s )
{
     int len = strlen( s );
     for( int i = 0 ; i < len; i++ )
          read( *(s+i) );
}

void field::setMinChar( int min )
{
     minchar = min;
}

void field::setfocus(){
    int c = getcolor();
	setcolor( 3 );
	rectangle( fx, fy, fx+fw, fy+fh );
	focus=1;
	setcolor(c);
}

void field::clear(){
	int color = getpixel( fx+2, fy+2 );
	setfillstyle( 1, color );
	bar( fx+1, fy+1, fx+fw-1, fy+fh-1 );
	strcpy( text, "" );
	lpos = 0;
}

void field::lostfocus(){	
    int c = getcolor();
	setcolor( 0 );
	rectangle( fx, fy, fx+fw, fy+fh );
	focus=0;
	setcolor(c);
}

int field::isValid(){
    return (chars >= minchar) ? true : false;
}

int field::read( char c ){

	char buff[2];
	int _c = getbkcolor();
	int validkeys = 1;
	int validalpha = ( (c >= 48 && c <= 57) || ( c >= 65 && c <= 90 ) || ( c >= 97 && c <= 122 ) ) || c == 8 || c == 32 || c == '-';
	
	switch( format ){
            case ALPHA:
                 validkeys = ( (c >= 48 && c <= 57) || ( c >= 65 && c <= 90 ) || ( c >= 97 && c <= 122 ) ) || c == 8 || c == 32;
                 break;
            case CORREO:
                 validkeys = validalpha || c == '@' || c == '.' || c == '_';
                 break;
            case INTEGER:
                 validkeys = (c >= 48 && c <= 57) || c == 8;
                 break;
            case REAL:
                 validkeys = (c >= 48 && c <= 57) || c == '.' || c== 8;
                 break;
    }
	
	if( focus == 1 && validkeys ){
		
		setbkcolor(15);
		setcolor(1);
		if( c!=8 ){
			if( lpos<nl ){
				buff[0]=c;
				buff[1]='\0';
				
				outtextxy( fx-2+textwidth(text)+10, fy-7+fh/2, buff);
				chars = chars + ( c != ' ' ? 1 : 0 );
                text[lpos]=c;
				lpos++;
			}
		}else if( c==8 && lpos>0 ){
			lpos--;
			text[lpos]='\0';
			chars --;
			setfillstyle( 1, tcolor );									
			bar( fx-2+textwidth(text)+20, fy+2, fx-2+textwidth(text)+10, fy+fh );
		}
		setbkcolor(_c);
		return 1;
	}else{
		return 0;
	}

}
