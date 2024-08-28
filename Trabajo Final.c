#include <stdio.h>
#include <stdlib.h>

int menu(char *msg); 
void caso1_1(int *v,int t); 
void caso1_2(int *v,int t);
void reset(int *v,int t);
void caso2_1(int *s,int t,int *r);
FILE *flujo(char *nombre,char *modo);
void guardar(FILE *g,int *v,int t);
void mostrar_resultados(int *v1,int t,int *v2);
void clean(int *vs,int *vr,int *ps,int *pr);
void ventas(int t,int *vs,int *vr);
void ganador(int *vs,int *vr,int *ps,int *pr);
int comparar(int *v1,int *v2,int t);
void recaudo(int *vs,int *vr,int *ps,int *pr);
void archivos(void);
void ganancia(int a);

int main(void) 
{ 
    int opc1,opc2,opc3,c[6]={0},s[6]={0},r[6]={0},vs=0,vr=0,ps=0,pr=0; 
    printf("JUEGUE EL BALOTO, COMPRELO, GANELO...Y DISFRUTELO! \n\n Creado con mucho esfuerzo por: \n\t\tAneider Granobles\t000345143\n\t\tJuan  J.  Zuluaga\t000348673");
    do{ 
        opc1=menu("\n\n1-Compra.\n2-Sorteo.\n3-Salir.\n\n"); 
        switch(opc1) 
        { 
            case 1: 
            do{ 
                opc2=menu("\n\n1-Automatico.\n2-Manual.\n3-Regresar al menu principal.\n\n"); 
                switch(opc2) 
                { 
                    case 1:
                    reset(&c[0],6);  //ANTES DE CADA VENTA EL VECTOR QUE GUARDA LOS NUMEROS SE REINICIA
                    caso1_1(&c[0],6);
                    break; 
                     
                    case 2:
                    reset(&c[0],6);
                    caso1_2(&c[0],6);
                    break; 
                     
                } 
            }while(opc2!=3); 
            break; 
             
            case 2: 
            do{ 
                opc3=menu("\n\n1-Nuevo Sorteo\n2-Resultados Baloto\n3-Borrar ventas realizadas\n4-Regresar al menu principal\n\n"); 
                switch(opc3) 
                { 
                    case 1:
                    reset(&s[0],6);  //LOS VECTORES SORTEO Y REVANCHA SE REINICIAN PARA PODER
                    reset(&r[0],6);  //LLENARLOS CON LOS NUEVOS NUMEROS GANADORES
                    caso2_1(&s[0],6,&r[0]);
                    mostrar_resultados(&s[0],6,&r[0]);
                    break; 
                     
                    case 2:
                    ventas(6,&vs,&vr);
                    ganador(&vs,&vr,&ps,&pr);
                    recaudo(&vs,&vr,&ps,&pr);
                    break; 
                     
                    case 3:
                    clean(&vs,&vr,&ps,&pr);
                    break;  
                } 
            }while(opc3!=4); 
        } 
    if(opc1==3)
    {
		printf("\n\nMuchas gracias por haber compartido tus conocimientos con nosotros.\n\t\tTe queremos con el corazon.");
	}
    }while(opc1!=3); 
    return 0; 
} 

int menu(char *msg) 
{ 
    int w;  //juanjo,en serio te confundiste con el menu?!
    printf("%s",msg); 
    scanf("%d",&w); 
    return w; 
} 

void caso1_1(int *v,int t) 
{ 
    int i,b,f=0,w,aux,rev;
    FILE *c;
    for(i=0;i<t;i++) 
    { 
        b=rand()%45+1;    //SE GENERAN ALEATORIOS 
        for(w=0;w<t;w++) 
        { 
            if(v[w]==b)   //SE CONFIRMA QUE NO SE REPITAN 
            { 
                f=1; 
                break; 
            } 
        } 
        if(f==1) 
        { 
            f=0; 
            i=i-1; 
            continue; 
        } 
        v[i]=b; 
    } 
    for(i=0;i<t;i++)   //ORDENACION DE MENOR A MAYOR 
    { 
        for(w=i+1;w<6;w++) 
        { 
            if(v[i]>v[w]) 
            { 
                aux=v[i]; 
                v[i]=v[w]; 
                v[w]=aux; 
            } 
        } 
    } 
    printf("Numeros generados aleatoriamente:\n"); 
    for(i=0;i<t;i++) 
    { 
        printf("[%d]",v[i]); 
    }
    
    c=flujo("ventas.txt","a");  //SE GUARDAN LOS NUMEROS EN "ventas.txt"
    guardar(c,&v[0],t);
    fclose(c);
    
    printf("\n\nDesea comprar la revancha, por 2.000 adicionales?:\n1. Si.\n2. No.\n\n");
	scanf("%d",&rev);
	if((rev!=1)&&(rev!=2))
	{
		do
		{printf("Por favor verifique su eleccion:\n");
		scanf("%d",&rev);
		}while((rev!=1)&&(rev!=2));
	}
	if(rev==1)
	{
             c=flujo("ventas2.txt","a"); //SI SE COMPRA LA REVANCHA,SE GUARDA EL NUMERO EN "ventas2.txt"
             guardar(c,&v[0],t);
             fclose(c);
    }
    printf("\nGracias por su compra!");
} 

void caso1_2( int *v, int t)
{ 
    int i,f=0,b,w,aux,rev,invalida=0;
    FILE *c;
    for(i=0;i<t;i++) 
    { 
        printf("\nIngrese el numero %d:",i+1); 
        scanf("%d",&b); 
		for(w=0;w<t;w++)
        { 
             if((b<1)||(b>45))  //SE CONFIRMA QUE EL NUMERO ESTE EN EL RANGO
            { 
                 
                f=2; 
                break; 
            } 
            
            
            if(b==v[w])  //SE CONFIRMA QUE NO SE REPITAN 
            { 
				f=1;
				break; 
            } 
           
        } 
        if(f==1) 
       { 
           printf("\nEl numero esta repetido\nCompra INVALIDA.\n\n");
           invalida=1;
           break;
           } 
            
    if(f==2) 
       { 
           printf("\nEl numero esta fuera del rango\nCompra INVALIDA.\n\n");
           invalida=1;
           break;
       }
      v[i]=b;   //CADA NUMERO INGRESADO SE GUARDA EN LA POSICION DEL VECTOR
      
    for(w=0;w<t;w++)
    {printf("[%d]",v[w]);}
    } 
    
    if(invalida!=1)
    {
         
        for(i=0;i<t;i++)   //ORDENACION DE MENOR A MAYOR 
        { 
        for(w=i+1;w<6;w++) 
        { 
            if(v[i]>v[w]) 
            { 
                aux=v[i]; 
                v[i]=v[w]; 
                v[w]=aux; 
            } 
        } 
    } 
    
    c=flujo("ventas.txt","a"); //SE GUARDA LA VENTA EN "ventas.txt"
    guardar(c,&v[0],t);
    fclose(c);
    
    printf("\nDesea comprar la revancha, por 2.000 adicionales?:\n1. Si.\n2. No.\n\n");
	scanf("%d",&rev);
	if((rev!=1)&&(rev!=2))
	{
		do
		{printf("Por favor verifique su eleccion:\n");
		scanf("%d",&rev);
		}while((rev!=1)&&(rev!=2));
	}
		if(rev==1)
	{
             c=flujo("ventas2.txt","a");  //SI SE COMPRA LA REVANCHA,SE GUARDA EL NUMERO EN "ventas2.txt"
             guardar(c,&v[0],t);
             fclose(c);
    }
    printf("\nGracias por su compra!\n");
    
    for(i=0;i<t;i++)          //SE MUESTRAN LOS NUMEROS COMPRADOS ORGANIZADOS
    {printf("[%d]",v[i]);}
    
    printf("\n");
    }
    else
    {invalida=0;} //SI LA COMPRA ES INVALIDA,LA BANDERA SE REINICIA PARA FUTURAS COMPRAS Y TERMINA LA COMPRA
} 
 
void reset(int *v,int t)
{
	int i;
	for(i=0;i<t;i++)
	{
		v[i]=0;
	}
}

void caso2_1(int *s,int t,int *r)
{
	int i,b,f=0,w,aux;
    FILE *g; 
    for(i=0;i<t;i++) 
    { 
        b=rand()%45+1;    //SE GENERAN ALEATORIOS 
        for(w=0;w<t;w++) 
        { 
            if(s[w]==b)   //SE CONFIRMA QUE NO SE REPITAN 
            { 
                f=1; 
                break; 
            } 
        } 
        if(f==1) 
        { 
            f=0; 
            i=i-1; 
            continue; 
        } 
        s[i]=b; 
    } 
    for(i=0;i<t;i++)   //ORDENACION DE MENOR A MAYOR 
    {                  //Y GUARDADO EN VECTOR SORTEO
        for(w=i+1;w<6;w++) 
        { 
            if(s[i]>s[w]) 
            { 
                aux=s[i]; 
                s[i]=s[w]; 
                s[w]=aux; 
            } 
        } 
    } 
    printf("\nSorteo realizado:\n"); 

   for(i=0;i<t;i++) 
    { 
        b=rand()%45+1;    //SE GENERAN ALEATORIOS 
        for(w=0;w<t;w++) 
        { 
            if(r[w]==b)   //SE CONFIRMA QUE NO SE REPITAN 
            { 
                f=1; 
                break; 
            } 
        } 
        if(f==1) 
        { 
            f=0; 
            i=i-1; 
            continue; 
        } 
        r[i]=b; 
    } 
    for(i=0;i<t;i++)   //ORDENACION DE MENOR A MAYOR 
    {                  //Y GUARDADO EN EL VECTOR REVANCHA
        for(w=i+1;w<6;w++) 
        { 
            if(r[i]>r[w]) 
            { 
                aux=r[i]; 
                r[i]=r[w]; 
                r[w]=aux; 
            } 
        } 
    } 
    
    g=flujo("sorteo.txt","w"); //SE GUARDAN RESULTADOS DEL SORTEO EN "sorteo.txt"
    guardar(g,&s[0],t);        //EN MODO "w" YA QUE SOLO PUEDE HABER 1 RESULTADO
    fclose(g);                 //POR SORTEO
    
    g=flujo("revancha.txt","w"); //IGUAL QUE EL RESULTADO ANTERIOR,PERO CON LA
    guardar(g,&r[0],t);          //REVANCHA
    fclose(g);
    
}

FILE *flujo(char *nombre,char *modo)
{
	FILE *fp;
	fp=fopen(nombre,modo);
	if (fp==NULL)
	{
		perror("Error con el archivo!");
		exit(1);
	}
	return fp;
}

void guardar(FILE *g,int *v,int t) //CON EL FLUJO DADO POR LA FUNCION DONDE SE 
{                                  //USE,GUARDAR VA A ESE ARCHIVO CON LOS DATOS
     int i;                        //DE UN VECTOR Y LOS GUARDA,UN VECTOR POR LINEA
     for(i=0;i<t;i++)
     {
          fprintf(g,"%d\t",v[i]);
     }    
     fprintf(g,"\n");       
}

void mostrar_resultados(int *s,int t,int *r)
{
     int i;                  //MUESTRA LOS NUMEROS DEL SORTEO
     
     printf("\nSORTEO:\n");
     for(i=0;i<t;i++) 
    { 
        printf("[%d]",s[i]); 
    } 
    
    printf("\n-------------------------");
    
    printf("\nREVANCHA:\n");
    for(i=0;i<t;i++) 
    { 
        printf("[%d]",r[i]); 
    } 
}

void clean(int *vs,int *vr,int *ps,int *pr) //CASO 2-3,REINICIA TODO
{
     FILE *c;
     c=flujo("sorteo.txt","w");
     fclose(c);
     c=flujo("ventas.txt","w");
     fclose(c);
     c=flujo("revancha.txt","w");
     fclose(c);
     c=flujo("ventas2.txt","w");
     fclose(c);
     *vs=0;
     *vr=0;
     *ps=0;
     *pr=0;
     printf("\nVentas borradas exitosamente.\n");
}

void ventas(int t,int *vs,int *vr) //ANALIZA SEGUN CUANTAS VENTAS SE HICIERON
{                                  //LA CANTIDAD DE GANANCIAS
     int e,ls=0,lr=0;
     FILE *f;
     archivos();
     f=flujo("ventas.txt","r");
     while((e=fgetc(f))!=EOF) //ESTE WHILE CUENTA CUANTAS LINEAS HAY,fgetc(f),LEE
     {                        //Y GUARDA EN e CARACTER A CARACTER,EOF HACE QUE VAYA
        if(e=='\n')           //HASTA EL FINAL DEL ARCHIVO ANALIZANDO.
        {ls++;}               //EL if HACE QUE CADA VEZ QUE SE LLEGUE A \n SUME UNO
     }                        //AL CONTADOR,ASI SE SABE CUANTAS LINEAS HAY.
     fclose(f);
     *vs=ls*5000;             //CADA LINEA ES UNA VENTA,ASI,SE MULTIPLICAN VENTAS
                              //POR PRECIO DE LA VENTA.
                              
     f=flujo("ventas2.txt","r");//AQUI ES LO MISMO QUE LO ANTERIOR,PERO SE HACE 
     while((e=fgetc(f))!=EOF)   //CON LAS VENTAS DE LA REVANCHA
     {
        if(e=='\n')
        {lr++;}
     }
     fclose(f);    
     *vr=lr*2000;     //ls=LINEAS SORTEO
                      //lr=LINEAS REVANCHA
                           
     printf("\nEl total de ventas de baloto fue:\n%d\n",*vs);
     printf("\nEl total de ventas de la revancha fue:\n%d\n",*vr);
}

void ganador(int *vs,int *vr,int *ps,int *pr)
{
     int i,x,a,v[6],s[6],w[6],b;
     float p;
     FILE *f,*f2;
     f2=flujo("sorteo.txt","r");
     reset(&w[0],6);
     for(i=0;i<6;i++)             //ESTE for METE EN UN VECTOR LOS NUMEROS DEL
     {                            //SORTEO,PARA COMPARARLOS CON LAS VENTAS
        fscanf(f2,"%d",&s[i]);
     }
     printf("\n\n\n\nGANADORES:\n");
     fclose(f2);

     f=flujo("ventas.txt","r");   //SE COMPARA VENTA A VENTA CON EL SORTEO Y SEGUN
     for(x=1;x<=*vs/5000;x++)     //ACIERTOS MUESTRA LO GANADO
     {
       for(i=0;i<6;i++)         //EL FLUJO EN EL ARCHIVO COMIENZA EN LA PRIMERA
       {                        //VENTA,ASI QUE LLENA UN VECTOR CON LOS 6 PRIMEROS
          fscanf(f,"%d",&v[i]); //NUMEROS Y LO COMPARA,LUEGO ASI CON TODAS LAS VENTAS
       }
       
       a=comparar(&v[0],&s[0],6);
       
       if(a!=-1)  //SEGUN LA CANTIDAD DE NUMEROS IGUALES,SE USA EL VECTOR CONTADOR
       {          //PARA SABER CUANTAS COMPRAS HAY CON 1 ACIERTO,2,3...
         w[a]++;
       }
     }
     
     rewind(f);  //LUEGO DE CONTAR CUANTAS COMPRAR TIENEN CUANTOS ACIERTOS,
                 //SE REINICIA EL FLUJO AL INICIO DEL ARCHIVO PARA COMENZAR
                 //A MOSTRAR GANADOR POR GANADOR
     
      for(x=1;x<=*vs/5000;x++)     //ACIERTOS MUESTRA LO GANADO
     {
       for(i=0;i<6;i++)         //EL FLUJO EN EL ARCHIVO COMIENZA EN LA PRIMERA
       {                        //VENTA,ASI QUE LLENA UN VECTOR CON LOS 6 PRIMEROS
          fscanf(f,"%d",&v[i]); //NUMEROS Y LO COMPARA,LUEGO ASI CON TODAS LAS VENTAS
       }
       printf("\n");
       
       a=comparar(&v[0],&s[0],6);
       
       if(a==-1)
       {continue;}
       if(a==0)
       {
          p=*vs*0.0;
          printf("Con 1 acierto,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nEs merecedora de $%f; equivalente al 0%% de las ventas,dividido entre los ganadores con los mismos aciertos.\n",p);
          *ps+=p;
       }
       if(a==1)
       {
          p=*vs*0.0;
          printf("Con 2 aciertos,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nEs merecedora de $%f; equivalente al 0%% de las ventas,dividido entre los ganadores con los mismos aciertos.\n",p);
          *ps+=p;
       }
       if(a==2)
       {
          p=(*vs*0.05)/(w[a]);
          printf("Con 3 aciertos,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nEs merecedora de $%f; equivalente al 5%% de las ventas,dividido entre los ganadores con los mismos aciertos.\n",p);
          *ps+=p;
       }
       if(a==3)
       {
          p=(*vs*0.1)/(w[a]);
          printf("Con 4 aciertos,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nEs merecedora de $%f; equivalente al 10%% de las ventas,dividido entre los ganadores con los mismos aciertos.\n",p);
          *ps+=p;
       }
       if(a==4)
       {
          p=(*vs*0.2)/(w[a]);
          printf("Con 5 aciertos,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nEs merecedora de $%f; equivalente al 20%% de las ventas,dividido entre los ganadores con los mismos aciertos.\n",p);
          *ps+=p;
       }
       if(a==5)
       {
          p=(*vs*0.4)/(w[a]);
          printf("Con 6 aciertos,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nEs merecedora de $%f; equivalente al 40%% de las ventas,dividido entre los ganadores con los mismos aciertos.\n",p);
          *ps+=p;
       }

     }
     fclose(f);
     
     printf("\n\n");
     for(i=0;i<6;i++)  //SE MUESTRA EL VECTOR QUE INDICA LA CANTIDAD DE
     {                 //GANADORES CON TANTOS ACIERTOS
        printf("\n*Con %d aciertos,hubo %d ganadores\n",i+1,w[i]);
     }

//----------------------------------------------------------------------------------------------------------------

     f=flujo("ventas2.txt","r");   //LO MISMO QUE LO ANTERIOR,AHORA CON LA
     f2=flujo("revancha.txt","r"); //REVANCHA
     for(i=0;i<6;i++)
     {
        fscanf(f2,"%d",&s[i]);
     }
     fclose(f2);
     
     reset(&w[0],6);   //SE REINICIA EL VECTOR CONTADOR DE ACIERTOS
     
     printf("\n\n\n\nGANADORES POR REVANCHA:\n");
     
     for(x=1;x<=*vr/2000;x++)     //ACIERTOS MUESTRA LO GANADO
     {
       for(i=0;i<6;i++)         //EL FLUJO EN EL ARCHIVO COMIENZA EN LA PRIMERA
       {                        //VENTA,ASI QUE LLENA UN VECTOR CON LOS 6 PRIMEROS
          fscanf(f,"%d",&v[i]); //NUMEROS Y LO COMPARA,LUEGO ASI CON TODAS LAS VENTAS
       }
       a=comparar(&v[0],&s[0],6);
       
       if(a!=-1) //VECTOR CONTADOR DE ACIERTOS REGRESA
       {
         w[a]++;
       }
       
     }
     
     rewind(f); //REINICIO DE FLUJO DE REVANCHA
     
     for(x=1;x<=*vr/2000;x++)
     {
       for(i=0;i<6;i++)
       {
          fscanf(f,"%d",&v[i]);
       }
       
       a=comparar(&v[0],&s[0],6);
       
       if(a==-1)
       {continue;} 
       if(a==0)
       {
          p=*vr*0.0;
          printf("\nCon 1 acierto,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nPor revancha,es merecedora de $%f; equivalente al 0%% de las ventas por revancha,dividido entre los ganadores con los mismos aciertos.\n",p);
          *pr+=p;
       }
       if(a==1)
       {
          p=*vr*0.0;
          printf("\nCon 2 aciertos,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nPor revancha,es merecedora de $%f; equivalente al 0%% de las ventas por revancha,dividido entre los ganadores con los mismos aciertos.\n",p);
          *pr+=p;
       }
       if(a==2)
       {
          p=(*vr*0.05)/(w[a]);
          printf("\nCon 3 aciertos,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nPor revancha,es merecedora de $%f; equivalente al 5%% de las ventas por revancha,dividido entre los ganadores con los mismos aciertos.\n",p);
          *pr+=p;
       }
       if(a==3)
       {
          p=(*vr*0.1)/(w[a]);
          printf("\nCon 4 aciertos,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nPor revancha,es merecedora de $%f; equivalente al 10%% de las ventas por revancha,dividido entre los ganadores con los mismos aciertos.\n",p);
          *pr+=p;
       }
       if(a==4)
       {
          p=(*vr*0.2)/(w[a]);
          printf("\nCon 5 aciertos,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nPor revancha,es merecedora de $%f; equivalente al 20%% de las ventas por revancha,dividido entre los ganadores con los mismos aciertos.\n",p);
          *pr+=p;
       }
       if(a==5)
       {
          p=(*vr*0.4)/(w[a]);
          printf("\nCon 6 aciertos,la boleta:\n");
          for(b=0;b<6;b++)
          {printf("[%d]",v[b]);}
          printf("\nPor revancha,es merecedora de $%f; equivalente al 40%% de las ventas por revancha,dividido entre los ganadores con los mismos aciertos.\n",p);
          *pr+=p;
       }
     }
     fclose(f);
     
     printf("\n\n");  //CONTEO DE GANADORES POR REVANCHA
     for(i=0;i<6;i++)
     {
        printf("\n*Con %d aciertos,hubo %d ganadores por revancha\n",i+1,w[i]);
     }
}

int comparar(int *v1,int *v2,int t)
{
     int i,x,r=-1;      //SE USA UN CONTADOR PARA DETERMINAR LA CANTIDAD
     for(i=0;i<t;i++)   //DE NUMEROS IGUALES ENTRE UN VECTOR (UNA COMPRA)
     {                  //Y EL VECTOR LLENADO CON LOS #s DEL SORTEO.
        for(x=0;x<t;x++)
        {
           if(v1[i]==v2[x])
           {
              r++;
           }
        }
     }
     return r;
}

void recaudo(int *vs,int *vr,int *ps,int *pr)
{
     int u;
     printf("\n\nECONOMIA:");
     printf("\n\nVentas baloto: $%d",*vs);
     printf("\nVentas revancha: $%d",*vr);
     printf("\nPagos baloto: $%d",*ps);
     printf("\nPagos revancha: $%d",*pr);
     u=(*vs+*vr)-(*ps+*pr);
     printf("\nUtilidades: $%d",u);
}

void archivos(void)       //FUNCION QUE ASEGURA LA EXISTENCIA DE LOS ARCHIVOS 
{                         //EN CASO DE QUE,POR EJEMPLO,SE TRATE DE VER GANADORES
	FILE *f;              //SIN HABER HECHO VENTAS NI SORTEOS.
	f=flujo("ventas.txt","a");
	fclose(f);
	f=flujo("ventas2.txt","a");
	fclose(f);
	f=flujo("sorteo.txt","a");
	fclose(f);
	f=flujo("revancha.txt","a");
	fclose(f);
}
