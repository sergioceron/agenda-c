/*  ------------------------------------------------------------------
 * |Archivo: agenda.h                                                 |
 * |Fecha: 18-08-08                                                   |
 * |Size: 5 Kb                                                        |
 * |Descripcion: Contiene las funciones basicas de la agenda:         |
 * |             abrir, cerrar, guardar, actualizar, buscar, etc .    |
 * |                                                                  |
 * |             El motor de la agenda se encuentra aqui, las         |
 * |             funciones sin interfaz.                              |
 *  ------------------------------------------------------------------
 */
 
struct Usuarios{
       char nombre[30];
       char apaterno[15];
       char amaterno[15];
       char empresa[20];
       char telefono[12];
       char cp[5];
       char correo[22];
       char direccion[35];
       char edireccion[35];
       char celular[15];
};

typedef struct Usuarios Usuario;

FILE* abrir( char *, int );
int cerrar( FILE* );
int getTotal( char * );
int guardar( Usuario, char * );
int actualizar( Usuario, int, char * );
int borrar( int, char * );
int *buscar( char*, char* );
Usuario getUser( int, char* );

int guardar( Usuario u, char *name )
{
    FILE *f = abrir( name, 2 );
    if ( f != NULL )
    {
        fwrite(&u, sizeof(u), 1, f);
    }else{
          printf("\n Error: Imposible guardar los datos");
          return -2;
    }
    cerrar ( f );
    return 0;
}

int getTotal( char *name )
{
      int items = 0;
      Usuario u;
      FILE *f = abrir( name, 0 );

	  while ( fread(&u, sizeof(u), 1, f) != 0 )
            items ++;

      cerrar( f );
      return items;
}

int actualizar( Usuario u, int e, char *name )
{
    Usuario user;
    FILE *f = abrir( name, 3 );
    int item = 0;
    if ( f != NULL )
    {
         while ( fread(&user, sizeof(user), 1, f) ){
               if( item == e )
                break;
               item++;
         }
         fseek(f,-1*sizeof(user),SEEK_CUR);
         fwrite(&u, sizeof(u), 1, f);
    }else{
          printf("\n Error: Imposible guardar los datos");
          return -2;
    }
    cerrar ( f );
    return 0;
}

int *buscar( char *s, char *name )
{
      Usuario u;
      int found = 0, item = 0;
      int regs[100];
      FILE *f = abrir( name, 0 );
      FILE *temp = fopen( "find.$$$", "w+");
      char buff[214];
	  while ( fread(&u, sizeof(u), 1, f) != 0 ){
	        sprintf( buff, "%s %s %s %s %s %s %s %s %s", u.nombre, u.apaterno, u.amaterno, u.empresa,  u.telefono, 
                     u.edireccion, u.direccion, u.correo, u.celular, u.cp );
	        if( strstr( toLower(buff), toLower(s)) != NULL ){
                fwrite(&u, sizeof(u), 1, temp);
                regs[ found ] = item;
                found ++;
            }
            item ++;
      }
      cerrar( temp );
      cerrar( f );
      return found > 0 ? regs : NULL;
}

int borrar( int e, char *name )
{
      Usuario u;
      int item = 0, found = 0;
      FILE *f = abrir( name, 0 );
      FILE *temp = fopen( "temp.$$$", "w+");
      if( !temp ){
         printf("\n Error: Imposible crear archivo de intercambio");
         return 0;
      }else{
         while ((fread(&u, sizeof(u), 1, f))!=0){
            if( item != e )
              fwrite(&u, sizeof(u), 1, temp);
            else
              found = 1;
            item ++;
         }
         cerrar( temp );
      }

      if(found && !cerrar( f ) ){
         system( "del agenda.dat" );
         system( "ren temp.$$$ agenda.dat" );
     }else{
         system("del temp.$$$");
         return 0;
     }
     return 1;
}

Usuario getUser( int e, char *name )
{
      Usuario u;
      int item = 0, found = 0;
      FILE *f = abrir( name, 0 );
      while ((fread(&u, sizeof(u), 1, f))!=0){
            if( item == e )
                break;
            item ++;
      }
      cerrar( f );

      return u;
}

FILE *abrir( char *name, int metodo )
{
   FILE *f;
   switch(metodo){
		case 0:
			f = fopen(name,"rb");
			break;
		case 1:
		    f = fopen(name,"wb");
			break;
		case 2:
			f = fopen(name,"ab");
			break;
		case 3:
			f = fopen(name,"r+b");
			break;
	}

   if(f == NULL) 
   { 
      printf( "Error fatal: No se puede abrir el archivo \n" );
      printf( "Creando una agenda de proteccion... \n" );
      f = fopen(name,"w+");
      printf( "Agenda creada. inicializando.... \n" );
//      return NULL; 
   } 

   return f;
}

int cerrar( FILE *f )
{
   if( fclose( f ) )
   {
       printf( "Error fatal: No se puede cerrar el archivo" );
       return 1;
   }
   return 0;
}
