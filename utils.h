/*  ------------------------------------------------------------------
 * |Archivo: c-gui.h                                                  |
 * |Fecha: 18-08-08                                                   |
 * |Size: 2 Kb                                                        |
 * |Descripcion: Contiene algunas funciones extra para la agenda,     |
 * |              tales como validar, convertir a minusculas, etc.    |
 * |                                                                  |
 *  ------------------------------------------------------------------
 */
 
int validar( Campo *, int);
char *toLower( char* );

char *toLower( char *s )
{
    int len = strlen( s ); 
    int i;
    char *buff = (char *)malloc( sizeof(char)*len+1 );
    for( i = 0; i < len; i++ )
         buff[i] = tolower(s[i]);
    buff[len] = '\0';
    return buff;
}


int validar( Campo *c, int s)
{
    int valid = 1;
    for( int i = 0; i < s; i++ )
    {
         if(!c[i].isValid()){
            valid = 0;
            break;
         }
    }
    return valid;
}
