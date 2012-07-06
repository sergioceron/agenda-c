/*  ------------------------------------------------------------------
 * |Archivo: interfaz.h                                               |
 * |Fecha: 18-08-08                                                   |
 * |Size: 15 Kb                                                       |
 * |Descripcion: Proporciona la interfaz grafica a las funciones de   |
 * |              la agenda.                                          |
 * |                                                                  |
 * |             Tambien inicia un loader para cargar en memoria las  |
 * |             imagenes y los componentes basicos.                  |
 *  ------------------------------------------------------------------
 */
 
char *FILE_NAME = "agenda.dat";

struct pagination
{
       int code;
       int multi;
};
typedef struct pagination page;

void *imagen;

int table(int, int, int, int);
int title(char *);
int loading();

int nuevo();
int editar( int );
int encontrar();
page listar( int offset );


int table( int x, int y, int rows, int cols )
{
    int w = 360, h = 390;
    
    setfillstyle( 1 ,15 );
    bar( x, y, x+w+1, y+25 );

    int color = getcolor();
    setcolor(7);
    y = y+25;
    for( int i = 0; i < rows+1; i++ )
         line( x, y + i*30, x+w, y + i*30 );
         
    for( int j = 0; j < cols+1; j++ )
         line( x + j*120 , y, x + j*120 , y + h );
    
        
    setcolor(color);
    return 0;
}

int title(char *txt)
{
    int c = getcolor();
    int bkcolor = getbkcolor();
    setbkcolor( COLOR(16,25,25) );
    setcolor( COLOR(135,180,180) );
    settextstyle(8,0,3);
    gprintfxy( 50, 50, txt );
    settextstyle(11,0,1);
    setbkcolor( bkcolor );
    setcolor( c );
    return 0;
}

int loading()
{
    imagen = loadbmp( 1, 1, "fondo1.bmp", -1);
    
    int error=0;
    char *msg[]= {"Cargando graficos", "Cargando interfaz", "Generando estructura", 
                  "Cargando datos", "Entrando a modo protegido", "Inicializando mouse", "Calculando dimensiones", 
                  "Generando coordenadas", "Registrando sesion", "Proteccion del sistema", "Cargando capa externa"};
    for( int i = 0, stage=0; i  < 255; i++ )
    {
         setfillstyle(1, COLOR( 255-i, i, 0) );
         bar(100, 340, 100 + (2*i), 350 );
         if( !( i % 25 ) ){
             setcolor(8);
             gprintfxy( 120, 60 + (20 * ++stage), msg[stage] ); 
             int lineheight = 120 + textwidth( msg[stage-1] );
             
             for( int j = 1; j < ( 300 - lineheight ) / 2; j++ ){
                  gprintfxy( lineheight + 5 + (j*2), 60 + (20 * stage), "-" ); 
                  delay( 1 );
             }
         }
         if( !( i % 26 ) ){
             setcolor( error ? COLOR(255, 0, 0) :COLOR(0, 255, 0));
             gprintfxy( 310, 60 + (20*stage), "%s", error ? "[ Failed ]" : "[ Done ]" );
         }
         delay(10);
    }
    setcolor( COLOR(0, 255, 0) );
    gprintfxy( 310, 60 + (20*11), "[ Done ]" );
    gprintfxy( 100, 320, "Load complete!" );
    delay(1000);
    cleardevice();
    return 0;
}

int nuevo()
{
        int code, color, bgcolor;
        Campo *f = NULL;
        Boton *b = NULL;
        Usuario user;
        
        // Interfaz
        title( "Nuevo cliente" );
        
        color = getcolor();
        bgcolor = getbkcolor();
        setbkcolor( COLOR(16,25,25) );
        
        setcolor( COLOR(213,227,217) );
        f = ( Campo *)malloc( sizeof( Campo ) * 10 );
        gprintfxy( 50, 100, "Nombre completo:" );
        f[0].put( 50, 120, 310, 20, 30 ); f[0].setfocus();
        gprintfxy( 50, 160, "Apellido paterno:" );
        f[1].put( 50, 180, 150, 20, 15 );
        gprintfxy( 210, 160, "Apellido materno:" );
        f[2].put( 210, 180, 150, 20, 15 );
        gprintfxy( 50, 220, "Empresa:" );
        f[3].put( 50, 240, 150, 20, 20 );
        gprintfxy( 210, 220, "Telefono Empresa:" );
        f[4].put( 210, 240, 150, 20, 12 );
        f[4].setFormat( 2 );
        f[4].setMinChar( 8 );
        gprintfxy( 50, 280, "CP:" );
        f[5].put( 50, 300, 60, 20, 5 );
        f[5].setFormat( 2 );
        f[5].setMinChar( 5 );
        gprintfxy( 120, 280, "Correo:" );
        f[6].put( 120, 300, 250, 20, 22 );
        f[6].setFormat( 4 );
        gprintfxy( 50, 340, "Direccion personal:" );
        f[7].put( 50, 360, 310, 20, 35 );
        gprintfxy( 50, 400, "Direccion Empresa:" );
        f[8].put( 50, 420, 310, 20, 35 );
        gprintfxy( 50, 460, "Celular:" );
        f[9].put( 50, 480, 310, 20, 15 );
        f[9].setFormat( 2 );
        f[9].setMinChar( 12 );
           
        b = ( Boton * )malloc( sizeof( Boton ) * 2 );
        b[0].put( 210, 530, 150, 30, "Almacenar" );
        b[1].put( 50, 530, 130, 30, "Regresar" );
        
        setcolor( color );
        setbkcolor( bgcolor );
        
        // Validacion
        int validate = 0;
        do{
           code = eventHandler( &f, &b, 10, 2 );
           if( code == 1 ) break;
           validate = validar(f, 10);
           if( !validate ){
               setbkcolor( COLOR( 16,25,25 ) );
               setcolor( 15 );
               gprintfxy( 400,400, "Algunos campos no cumplen el minimo de caracteres." );
               delay(500);
               setcolor( COLOR( 16,25,25 ) );
               gprintfxy( 400,400, "Algunos campos no cumplen el minimo de caracteres." );
               setcolor(15);
               setbkcolor( 0 );
           }
        }while( !validate );
        
        // Guardar
        if( code == 0 ){
            strcpy(user.nombre, f[0].text );
            strcpy(user.apaterno, f[1].text );
            strcpy(user.amaterno, f[2].text );
            strcpy(user.empresa, f[3].text );
            strcpy(user.telefono, f[4].text );
            strcpy(user.cp, f[5].text );
            strcpy(user.correo, f[6].text );
            strcpy(user.direccion, f[7].text );
            strcpy(user.edireccion, f[8].text );
            strcpy(user.celular, f[9].text );
            code = guardar( user, FILE_NAME );
        }
        
        free( f );
        free( b );

        return code;
}

int encontrar()
{
        int code, color, bgcolor;
        Campo *f = NULL;
        Boton *b = NULL;
        Usuario user;
        
        // Interfaz
        title( "Busqueda" );
        
        color = getcolor();
        bgcolor = getbkcolor();
        setbkcolor( COLOR(16,25,25) );
        setcolor( COLOR(213,227,217) );
        
        f = ( Campo *)malloc( sizeof( Campo ) * 1 );
        gprintfxy( 50, 100, "Termino de busqueda:" );
        f[0].put( 50, 120, 310, 20, 30 ); f[0].setfocus();

           
        b = ( Boton * )malloc( sizeof( Boton ) * 2 );
        b[0].put( 210, 150, 150, 30, "Busqueda" );
        b[1].put( 50, 150, 130, 30, "Regresar" );
        
        code = eventHandler( &f, &b, 1, 2 );
        if( code == 0 )
            buscar( f[0].text, FILE_NAME );
            
        setcolor( color );
        setbkcolor( bgcolor );
            
        free( f );
        free( b );

        return code;
}

int editar( int u )
{
        putimage( 0, 0, imagen, COPY_PUT );
        int code, color, bgcolor;
        Campo *f = NULL;
        Boton *b = NULL;
        Usuario user;
        
        user = getUser( u, FILE_NAME );
        // Interfaz
        title( "Editar cliente" );
        
        color = getcolor();
        bgcolor = getbkcolor();
        setbkcolor( COLOR(16,25,25) );
        
        setcolor( COLOR(213,227,217) );
        f = ( Campo *)malloc( sizeof( Campo ) * 10 );
        gprintfxy( 50, 100, "Nombre completo:" );
        f[0].put( 50, 120, 310, 20, 30 ); f[0].setfocus();
        gprintfxy( 50, 160, "Apellido paterno:" );
        f[1].put( 50, 180, 150, 20, 15 );
        gprintfxy( 210, 160, "Apellido materno:" );
        f[2].put( 210, 180, 150, 20, 15 );
        gprintfxy( 50, 220, "Empresa:" );
        f[3].put( 50, 240, 150, 20, 20 );
        gprintfxy( 210, 220, "Telefono Empresa:" );
        f[4].put( 210, 240, 150, 20, 12 );
        f[4].setFormat( 2 );
        f[4].setMinChar( 8 );
        gprintfxy( 50, 280, "CP:" );
        f[5].put( 50, 300, 60, 20, 5 );
        f[5].setFormat( 2 );
        f[5].setMinChar( 5 );
        gprintfxy( 120, 280, "Correo:" );
        f[6].put( 120, 300, 250, 20, 22 );
        f[6].setFormat( 4 );
        gprintfxy( 50, 340, "Direccion personal:" );
        f[7].put( 50, 360, 310, 20, 35 );
        gprintfxy( 50, 400, "Direccion Empresa:" );
        f[8].put( 50, 420, 310, 20, 35 );
        gprintfxy( 50, 460, "Celular:" );
        f[9].put( 50, 480, 310, 20, 15 );
        f[9].setFormat( 2 );
        f[9].setMinChar( 12 );
        
        // Setting text
        f[0].setText( user.nombre );
        nextFocus( &f, 10 );
        f[1].setText( user.apaterno );
        nextFocus( &f, 10 );
        f[2].setText( user.amaterno );
        nextFocus( &f, 10 );
        f[3].setText( user.empresa );
        nextFocus( &f, 10 );
        f[4].setText( user.telefono );
        nextFocus( &f, 10 );
        f[5].setText( user.cp );
        nextFocus( &f, 10 );
        f[6].setText( user.correo );
        nextFocus( &f, 10 );
        f[7].setText( user.direccion );
        nextFocus( &f, 10 );
        f[8].setText( user.edireccion );
        nextFocus( &f, 10 );
        f[9].setText( user.celular );
        nextFocus( &f, 10 );

        // Botones 
        b = ( Boton * )malloc( sizeof( Boton ) * 2 );
        b[0].put( 210, 530, 150, 30, "Almacenar" );
        b[1].put( 50, 530, 130, 30, "Regresar" );
        
        setcolor( color );
        setbkcolor( bgcolor );
        
        // Validacion
        int validate = 0;
        do{
           code = eventHandler( &f, &b, 10, 2 );
           if( code == 1 ) break;
           validate = validar(f, 10);
           if( !validate ){
               setbkcolor( COLOR( 16,25,25 ) );
               setcolor( 15 );
               gprintfxy( 400,400, "Algunos campos no cumplen el minimo de caracteres." );
               delay(500);
               setcolor( COLOR( 16,25,25 ) );
               gprintfxy( 400,400, "Algunos campos no cumplen el minimo de caracteres." );
               setcolor(15);
               setbkcolor( 0 );
           }
        }while( !validate );
        
        // Guardar
        if( code == 0 ){
            strcpy(user.nombre, f[0].text );
            strcpy(user.apaterno, f[1].text );
            strcpy(user.amaterno, f[2].text );
            strcpy(user.empresa, f[3].text );
            strcpy(user.telefono, f[4].text );
            strcpy(user.cp, f[5].text );
            strcpy(user.correo, f[6].text );
            strcpy(user.direccion, f[7].text );
            strcpy(user.edireccion, f[8].text );
            strcpy(user.celular, f[9].text );
            code = actualizar( user, u,  FILE_NAME );
        }
        free( f );
        free( b );

        return code;
}

page listar( int offset )
{
        int code, color, bgcolor;
        int item = 0;
        Boton *b = NULL;
        Usuario user;
        
        b = ( Boton * )malloc( sizeof( Boton ) * 28 );
        
        // Incializar los botones
        for( int j= 0; j < 28; j++ )
        {
             b[j].x = -1;
             b[j].y = -1;
             b[j].w = 0;
             b[j].h = 0;
             strcpy( b[j].texto, "" );
        }
        
        // Interfaz
        title( "Lista Clientes" );
        
        color = getcolor();
        bgcolor = getbkcolor();
        setbkcolor( COLOR(16,25,25) );
        
        setcolor( COLOR(213,227,217) );
        
        FILE *f;
        if( (f = abrir( FILE_NAME, 0 )) != NULL ){
             // Table
             table( 50, 98, 13, 3 );
             for( int k = 0; k < offset; k++ )
                  fread(&user, sizeof(user), 1, f);
             // Header
             int bgcolor = getbkcolor();
             int color = getcolor();
             setcolor( 8 );
             setbkcolor( 15 );
             settextstyle(11,0,8);
             gprintfxy( 55, 100, "ID" );
             gprintfxy( 85, 100, "Nombre" );
             gprintfxy( 205, 100, "A. Paterno" );
             gprintfxy( 325, 100, "A. Materno" );
             setbkcolor( bgcolor );
             setcolor( color );
             
             // Body list
             settextjustify( 1,2 );
             settextstyle(2,0,4);
             while ( fread(&user, sizeof(user), 1, f) != 0 && item < 13 )
             {
                 gprintfxy( 58, 130 + (item * 30), "%d", item );
                 settextjustify( 0,2 );
                 gprintfxy( 85, 130 + (item * 30), "%s", user.nombre );
                 settextjustify( 1,2 );
                 gprintfxy( 225, 130 + (item * 30), "%s", user.apaterno );
                 gprintfxy( 345, 130 + (item * 30), "%s", user.amaterno );
                 b[item+2].put( 415, 130 + (item * 30), 30, 20, "Ver" );
                 b[item+15].put( 455, 130 + (item * 30), 30, 20, "Del" );
                 item ++;
             }
             settextjustify( 0,2 );
        }
        
        if( getTotal( FILE_NAME ) > offset + 13  )
                b[0].put( 210, 530, 150, 30, "Siguiente" );
        b[1].put( 50, 530, 130, 30, "Regresar" );
        
        setcolor( color );
        setbkcolor( bgcolor );
        
        reactivate:
        code = eventHandler( NULL, &b, 0, 28 );
        settextstyle(11,0,1);
        
        free( b );
        
        cerrar(f);
        
        page p;
        p.multi = offset/13;
        
        if( code == 0 ){

            cleardevice();
            page p2 = listar( offset + 13 );
            code = p2.code;
            p.multi = p2.multi;
        }
        
        if( code == 1  ){
            if( offset == 0 ){
                code = 1;
                p.multi = 0;
            }else{
                 cleardevice();
                 page p2 = listar( offset - 13 );
                 code = p2.code;
                 p.multi = p2.multi;
            }
        }

        p.code = code;
        
        return p;
}
