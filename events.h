/*  ------------------------------------------------------------------
 * |Archivo: events.h                                                 |
 * |Fecha: 18-08-08                                                   |
 * |Size: 4 Kb                                                        |
 * |Descripcion: Contiene el manejador de eventos para la agenda:     |
 * |              clicks, onovers, focus, etc.                        |
 * |                                                                  |
 * |             El manejador de eventos proporciona a la interfaz    |
 * |             la simulacion de multihilo.                          |
 *  ------------------------------------------------------------------
 */
 
#define TAB 9
#define ENTER 13
#define ESCAPE 27

int click(Boton *, int, int, int);
int clickf(Campo *, int, int, int);
int mouseover(int, int, struct button*, int);
int eventHandler( Campo **, Boton **, int, int );
int nextFocus( Campo **, int );

int nextFocus( Campo **f, int n)
{
    int current = 0, next;
    for( int i = 0; i < n; i++ )
         if( (*f)[i].focus ){
             current = i;
             break;
         }
     next = current + 1;    

    if( next >= n )
        next = 0;
        
    (*f)[next].setfocus();
    (*f)[current].lostfocus();

    return 0;
}



int click(Boton *b, int x, int y, int n)
{
        for( int i = 0; i < n; i++ )
            if( x > b[i].x && x < b[i].x+b[i].w && y > b[i].y && y < b[i].y+b[i].h  )
               return i;
    return -1;
}

int clickf(Campo *f, int x, int y, int n)
{

        for( int i = 0; i < n; i++ )
            if( x > f[i].fx && x < f[i].fx+f[i].fw && y > f[i].fy && y < f[i].fy+f[i].fh  )
               return i;
    return -1;
}

int mouseover(int x, int y, struct button *b, int t)
{
    for( int i=0; i < t; i++ )
        if( x > b[i].x && x < b[i].x+b[i].w && y > b[i].y && y < b[i].y+b[i].h )
        {
            if( !b[i].isover )b[i].over();
            break;
        }else
             if( b[i].isover )b[i].redraw();
    return 0;
}

int eventHandler( Campo **fields, Boton **buttons, int f, int b )
{
    int event = -1, i = 0, focus = 0;
    while( true )
    {
        if( ismouseclick(WM_LBUTTONDOWN    ) ){
                int x, y;
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if( b > 0 )
                if( (event = click( *buttons,x,y, b )) >= 0  )
                        return event;
            
                if( f > 0 )
                if( (focus = clickf( *fields,x,y, f )) >= 0  ){
                        for( int j = 0; j < f; j++ )
                             (*fields)[j].lostfocus();
                        (*fields)[focus].setfocus();
                }
        }

        if( f > 0 )
        if( kbhit() ){
             char c = getch();

             if( c == TAB )
                 nextFocus( fields, f );
             else if( c == ENTER )
                  return 0;
             else if( c == ESCAPE )
                  return -1;
             else
                 for( i=0; i < f; i++ )
                      (*fields)[i].read( c );
        }
        if( b > 0 )
        mouseover(mousex(), mousey(), *buttons, b);
        delay(50);
    }
}
