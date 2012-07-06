/*  ------------------------------------------------------------------
 * |Archivo: images.h                                                 |
 * |Fecha: 18-08-08                                                   |
 * |Size: 3 Kb                                                        |
 * |Descripcion: Libreria que abre una imagen en formato BMP a 256    |
 * |              colores en rgb.                                     |
 * |                                                                  |
 * |             La funcion loadbmp carga una imagen en memoria y al  |
 * |             mismo tiempo la imprime en pantalla.                 |
 *  ------------------------------------------------------------------
 */
 
typedef unsigned char byte;
byte paleta[256*3];
typedef unsigned int word;

void fskip(FILE *, int );
int getcolor( int );
void *loadbmp(int, int, char *, int );

void fskip(FILE *fp,int n){
   for (int i=0;i<n;i++)fgetc(fp);
} 

int getcolor( int color )
{
    return COLOR(paleta[(color*3+0)],paleta[(color*3+1)],paleta[(color*3+2)]);
}

void *loadbmp(int x1,int y1,char *file,int desp){
	word width=0, height=0, colors;
    int offset;
	FILE *fp;int num_colors,index;
	if ((fp = fopen(file,"rb")) == NULL) {
	printf("Error al abrir el archivo %s.\n",file);return NULL;}
	if (fgetc(fp)!='B' || fgetc(fp)!='M'){
	   fclose(fp);
       printf("%s no es un archivo bitmap.\n",file);
       return NULL;
    }
    fskip(fp,16);fread(&width, sizeof(word), 1, fp);
	fskip(fp,0);fread(&height, sizeof(word), 1, fp);
    fskip(fp,20);
    fread(&colors,sizeof(word), 1, fp);
    fskip(fp,4);
    if (colors==0)colors=256;

    int n;

    for(index=0;index<colors;index++){
	        paleta[(int)(index*3+2)] = fgetc(fp) >> 0;
          	paleta[(int)(index*3+1)] = fgetc(fp) >> 0;
        	paleta[(int)(index*3+0)] = fgetc(fp) >> 0;
            n=fgetc(fp);
    }
    int c;
    for( int y=height-1;(y>=0)&&(!feof(fp));y--)
             for(int x=0;(x<=width+desp)&&(!feof(fp));x++, c=fgetc(fp))
                        putpixel(x1+x,y1+y,getcolor(c)); 
    
	fclose(fp);
	// cargamos la imagen en la memoria
    int imagentam = imagesize( 1, 1, 800, 600 );
    void *imagen = malloc( imagentam );
    getimage( 1, 1, 800, 600, imagen );
    
	return imagen;
}
