/*
 Compiladores - Analizador Lexico para el lenguaje C#

 Este programa lee un archivo fuente (escrito en C#) y calcula las parejas
 ordenadas <token, lexema> por medio de un automata finito determinista.
 Los tokens son guardados en un archivo de texto. (tokens.txt)

 Este programa esta diseñado para compilarse en Turbo C de Borland.

 Licencia:
 Este programa es software libre, por lo tanto se puede distribuir o
 modificar bajo los terminos de la licencia GNU (General Public License)
 asi como lo ha publicado la fundacion de software libre.

*/

#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int MT[94][30];
void llenar_matriz();
void corrige_arreglo(char arre[100]);

main(){

FILE *apt, *apt2;
char arch[15];
char c;
char arre[100];
int ind=0;
int ban=0, ban2=0;
int edo=1;
int ptr;
int yesp;

char *palabras[] = {"abstract", "as", "bool", "break", "byte", "case",
"catch", "char", "checked", "class", "const", "continue", "decimal",
"default", "delegate", "do", "double", "else", "enum", "event", "explicit",
"extern", "false", "finally", "fixed", "float", "for", "foreach", "goto",
"if", "implicit", "in", "int", "interface", "internal", "lock", "is", "long",
"namespace", "new", "null", "object", "operator", "out", "override", "params",
"private", "protect", "public", "readonly", "ref", "return", "sbyte", "sealed",
"short", "sizeof", "stackalloc", "static", "string", "struct", "switch","this",
"throw", "true", "try","typeof", "uint", "ulong", "unchecked", "unsafe",
"ushort", "using", "virtual", "void", "while", "cout"};

strncpy(arre,"",100);

printf("Analizador lexico para C#\n");
printf("Escriba el nombre del archivo que quiere analizar: ");
scanf("%s",arch);
printf("Intentando abrir: %s\n\n",arch);
apt=fopen(arch,"r");
apt2=fopen("tokens.txt","w");

if(apt == 0){
   printf("No se encontro el archivo\n");
   getch();
   exit(0);
   }

llenar_matriz();

while(!feof(apt)){
 if(ban==0) c=getc(apt);
 ban=0;
    // Es numero o letra?
 if(isdigit(c))  edo=MT[edo][0];
 if(isalpha(c))  edo=MT[edo][1];

   // Comparacion del caracter de entrada!!
 switch(c){
  case '+':edo=MT[edo][2];break;
  case '-':edo=MT[edo][3];break;
  case '%':edo=MT[edo][4];break;
  case '*':edo=MT[edo][5];break;
  case '=':edo=MT[edo][6];break;
  case '.':edo=MT[edo][7];break;
  case '"':edo=MT[edo][8];break;
  case '"':edo=MT[edo][9];break;
  case '/':edo=MT[edo][10];break;
  case '>':edo=MT[edo][11];break;
  case '<':edo=MT[edo][12];break;
  case '_':edo=MT[edo][13];break;
  case ' ', '\n', '\t':edo=MT[edo]14];break;
  default: edo=MT[edo][15];break;
 } //fin switch

  // Estados terminales del automata!!
 switch (edo) {
  case 3:    // SumaAsigna
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"SumaAsigna,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 4:    // *Suma
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Suma,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 5:    // Incremento
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Incremento,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 7:    // RestaAsigna
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"RestaAsigna,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 8:    // *Resta
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Resta,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 9:    // Decremento
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Decremento,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 11:    // MultiplicaAsigna
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"MultiplicaAsigna, %s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 12:    // *Multiplica
	 edo=1;
	 fprintf(apt2,"Multiplica,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 13:    // FinComentario
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"FinComentario,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 15:    // *Divide
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Divide,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 16:    // *DivideAsigna
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"DivideAsigna,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 18:    // ComentarioLinea
	 edo=1;
	 corrige_arreglo(arre);
	 // fprintf(apt2,"ComentarioLinea,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 22:    // *Comentario
	 edo=1;
	 // fprintf(apt2,"Comentario,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 24:    // Identico
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Identico,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 25:    // *Asigna
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Asigna,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 27:    // Diferente
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Diferente,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 28:    // *Negacion
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Negacion,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 30:    // ModuloAsigna
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"ModuloAsigna,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 31:    // *Modulo
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Modulo,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 33:    // MenorIgual
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"MenorIgual, 	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 34:    // *MenorQue
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"MenorQue, 	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 36:    // *CorrimientoIzq
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"CorrimientoIzq,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 37:    // *CorrimientoIzqAsigna
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"CorrimientoIzqAsigna, %s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 39:    // MayorIgual
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"MayorIgual,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 40:    // *MayorQue
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"MayorQue,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 42:    // *CorrimientoDer
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"CorrimientoDer,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 43:    // CorrimientoDerAsigna
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"CorrimientoDerAsigna, %s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 45:    // PotenciaAsigna
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"PotenciaAsigna,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 46:    // *Potencia
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Potencia,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 49:    // *Or
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Or,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 50:    // *Pipe
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Pipe,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 53:    // *Ampersand
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Ampersand,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 54:    // *And
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"SumaAsigna,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 56:    // *CorcheteIzq
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"CorcheteIzq,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 58:    // *CorcheteDer
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"CorcheteDer,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 60:    // *ParentesisIzq
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"ParentesisIzq,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 62:    // *ParentesisDer
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"ParentesisDer,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 64:    // *LlaveIzq
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"LlaveIzq,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 66:    // *LlaveDer
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"LlaveDer,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 69:    // *Texto
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Texto,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 71:    // *PuntoYcoma
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"PuntoYcoma,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 73:    // *Coma
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Coma,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 75:    // Gato
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Gato,		#\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 77:    // *Espacios
	 edo=1;
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
	 ban2=1;
       break;

  case 79:    // GuionBajo
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"GuionBajo,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 81:    // ComillaSimple
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"ComillaSimple,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 83:    // *Punto
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Punto,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 85:    // *Identificador
	 edo=1;
	 yesp=0;
	 if (ban2==1) corrige_arreglo(arre);
	 for(int b=0; b<23; b++){
	    ptr = strcmp(arre,palabras[b]);
	     if(ptr == 0){
		fprintf(apt2,"PalReservada,	%s\n",arre);
		yesp = 1;
	      }
	 }
	 if(yesp == 0)
	   fprintf(apt2,"Identificador,	%s\n",arre);
	   strncpy(arre,"",100);
	   ban=1;
	   ind=0;
       break;

  case 86:    // *Objeto
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"Objeto,		%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 90:    // *NumeroReal
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"NumeroReal,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 91:    // *NumeroEntero
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"NumeroEntero,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 93:    // NuevaLinea
	 edo=1;
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;

  case 95:    // *DosPuntos
	 edo=1;
	 corrige_arreglo(arre);
	 fprintf(apt2,"DosPuntos,	%s\n",arre);
	 strncpy(arre,"",100);
	 ind=0;
	 ban=1;
       break;
 } //fin Switch

 if(arre[0]==' '){
    ind=0; ban=0;
   }
 else
   arre[ind]=c;
 ind++;
} //fin while

fclose(apt2);
fclose(apt);
printf("Se ha creado un archivo con los tokens!!\n Presione enter para continuar");
getch();
exit(0);
}

void corrige_arreglo(char arre[100]){
  for(int r=1; r<=100; r++)
  arre[r-1]=arre[r];
}

void llenar_matriz(){
 // Llenado Horizontal de la fila[0] columna [e] con 0's
  for(int e=0; e<=30; e++)
    MT[0][e]=0;
 // Llenado Vertical de la fila[m] columna[0] con 0's
  for(int m=0; m==93; m++)
    MT[m][0]=0;
 // Transiciones del automata!!
MT[0][0]=6;  
MT[0][1]=19;   
MT[0][2]=1;  
MT[0][3]=2;  
MT[0][4]=4;  
MT[0][5]=3;  
MT[0][6]=5; 
MT[0][7]=200;  
MT[0][8]=9;  
MT[0][9]=200;  
MT[0][10]=11;  
MT[0][11]=14; 
MT[0][12]=15;  
MT[0][13]=200;  
MT[0][14]=200;  
MT[0][15]=200;  

MT[1][0]=201;  
MT[1][1]=201;   
MT[1][2]=201;  
MT[1][3]=201;  
MT[1][4]=201;  
MT[1][5]=201;  
MT[1][6]=201; 
MT[1][7]=201;  
MT[1][8]=201;  
MT[1][9]=201;  
MT[1][10]=201;  
MT[1][11]=201; 
MT[1][12]=201;  
MT[1][13]=201;  
MT[1][14]=101;  
MT[1][15]=201;

MT[2][0]=202;  
MT[2][1]=202;   
MT[2][2]=201;  
MT[2][3]=202;  
MT[2][4]=202;  
MT[2][5]=202;  
MT[2][6]=202; 
MT[2][7]=202;  
MT[2][8]=202;  
MT[2][9]=202;  
MT[2][10]=202;  
MT[2][11]=202; 
MT[2][12]=202;  
MT[2][13]=202;  
MT[2][14]=102;  
MT[2][15]=202;  

MT[3][0]=203;  
MT[3][1]=203;   
MT[3][2]=203;  
MT[3][3]=203;  
MT[3][4]=203;  
MT[3][5]=203;  
MT[3][6]=203; 
MT[3][7]=203;  
MT[3][8]=203;  
MT[3][9]=203;  
MT[3][10]=203;  
MT[3][11]=203; 
MT[3][12]=203;  
MT[3][13]=203;  
MT[3][14]=103;  
MT[3][15]=203;  

MT[4][0]=204;  
MT[4][1]=204;   
MT[4][2]=204;  
MT[4][3]=204;  
MT[4][4]=204;  
MT[4][5]=204;  
MT[4][6]=204; 
MT[4][7]=204;  
MT[4][8]=204;  
MT[4][9]=204;  
MT[4][10]=204;  
MT[4][11]=204; 
MT[4][12]=204;  
MT[4][13]=204;  
MT[4][14]=104;  
MT[4][15]=204;  

MT[5][0]=205;  
MT[5][1]=205;   
MT[5][2]=205;  
MT[5][3]=205;  
MT[5][4]=205;  
MT[5][5]=205;  
MT[5][6]=18; 
MT[5][7]=205;  
MT[5][8]=205;  
MT[5][9]=205;  
MT[5][10]=205;  
MT[5][11]=205; 
MT[5][12]=205;  
MT[5][13]=205;  
MT[5][14]=105;  
MT[5][15]=205;

MT[6][0]=6;  
MT[6][1]=210;   
MT[6][2]=210;  
MT[6][3]=210;  
MT[6][4]=210;  
MT[6][5]=210;  
MT[6][6]=210; 
MT[6][7]=7; 
MT[6][8]=210;  
MT[6][9]=210;  
MT[6][10]=204;  
MT[6][11]=210; 
MT[6][12]=210;  
MT[6][13]=22;  
MT[6][14]=110;  
MT[6][15]=210; 

MT[7][0]=0;  
MT[7][1]=211;   
MT[7][2]=211;  
MT[7][3]=211;  
MT[7][4]=211;  
MT[7][5]=211;  
MT[7][6]=211; 
MT[7][7]=211; 
MT[7][8]=211;  
MT[7][9]=211;  
MT[7][10]=211;  
MT[7][11]=211; 
MT[7][12]=211;  
MT[7][13]=211;  
MT[7][14]=211;  
MT[7][15]=211;    

MT[8][0]=8;  
MT[8][1]=212;   
MT[8][2]=212;  
MT[8][3]=212;  
MT[8][4]=212;  
MT[8][5]=212;  
MT[8][6]=212; 
MT[8][7]=212; 
MT[8][8]=212;  
MT[8][9]=212;  
MT[8][10]=212;  
MT[8][11]=212; 
MT[8][12]=212;  
MT[8][13]=212;  
MT[8][14]=111;  
MT[8][15]=212; 

MT[9][0]=213;  
MT[9][1]=213;   
MT[9][2]=213;  
MT[9][3]=213;  
MT[9][4]=213;  
MT[9][5]=213;  
MT[9][6]=213; 
MT[9][7]=213; 
MT[9][8]=213;  
MT[9][9]=213;  
MT[9][10]=213;  
MT[9][11]=213; 
MT[9][12]=213;  
MT[9][13]=213;  
MT[9][14]=213;  
MT[9][15]=10; 

MT[10][0]=214;  
MT[10][1]=214;  
MT[10][2]=214;  
MT[10][3]=214;  
MT[10][4]=214;  
MT[10][5]=214;  
MT[10][6]=214; 
MT[10][7]=214; 
MT[10][8]=214;  
MT[10][9]=214;  
MT[10][10]=214;  
MT[10][11]=214; 
MT[10][12]=214;  
MT[10][13]=214;  
MT[10][14]=214;  
MT[10][15]=10; 

MT[11][0]=220;  
MT[11][1]=220;  
MT[11][2]=12;  
MT[11][3]=220;  
MT[11][4]=220;  
MT[11][5]=220;  
MT[11][6]=220; 
MT[11][7]=220; 
MT[11][8]=220;  
MT[11][9]=220;  
MT[11][10]=220;  
MT[11][11]=220; 
MT[11][12]=220;  
MT[11][13]=220;  
MT[11][14]=220;  
MT[11][15]=220;

MT[11][0]=220;  
MT[11][1]=220;  
MT[11][2]=12;  
MT[11][3]=220;  
MT[11][4]=220;  
MT[11][5]=220;  
MT[11][6]=220; 
MT[11][7]=220; 
MT[11][8]=220;  
MT[11][9]=220;  
MT[11][10]=220;  
MT[11][11]=220; 
MT[11][12]=220;  
MT[11][13]=220;  
MT[11][14]=220;  
MT[11][15]=220;

MT[12][0]=221;  
MT[12][1]=221;  
MT[12][2]=13;  
MT[12][3]=221;  
MT[12][4]=221;  
MT[12][5]=221;  
MT[12][6]=221; 
MT[12][7]=221; 
MT[12][8]=221;  
MT[12][9]=221;  
MT[12][10]=221;  
MT[12][11]=221; 
MT[12][12]=221;  
MT[12][13]=221;  
MT[12][14]=221;  
MT[12][15]=12;

MT[13][0]=222;  
MT[13][1]=222;  
MT[13][2]=222; 
MT[13][3]=222;  
MT[13][4]=222;  
MT[13][5]=222;  
MT[13][6]=222; 
MT[13][7]=222; 
MT[13][8]=222;  
MT[13][9]=222;  
MT[13][10]=120;  
MT[13][11]=222; 
MT[13][12]=222;  
MT[13][13]=222;  
MT[13][14]=222;  
MT[13][15]=222;

MT[14][0]=230;  
MT[14][1]=230;  
MT[14][2]=230; 
MT[14][3]=230;  
MT[14][4]=230;  
MT[14][5]=230;  
MT[14][6]=16; 
MT[14][7]=230; 
MT[14][8]=230;  
MT[14][9]=230;  
MT[14][10]=130;  
MT[14][11]=230; 
MT[14][12]=230;  
MT[14][13]=230;  
MT[14][14]=230;  
MT[14][15]=230;

MT[15][0]=231;  
MT[15][1]=231;  
MT[15][2]=231; 
MT[15][3]=231;  
MT[15][4]=231;  
MT[15][5]=231;  
MT[15][6]=17; 
MT[15][7]=231; 
MT[15][8]=231;  
MT[15][9]=231;  
MT[15][10]=131;  
MT[15][11]=231; 
MT[15][12]=231;  
MT[15][13]=231;  
MT[15][14]=231;  
MT[15][15]=231;

MT[16][0]=232;  
MT[16][1]=232;  
MT[16][2]=232; 
MT[16][3]=232;  
MT[16][4]=232;  
MT[16][5]=232;  
MT[16][6]=232;
MT[16][7]=232; 
MT[16][8]=232;  
MT[16][9]=232;  
MT[16][10]=132;  
MT[16][11]=232; 
MT[16][12]=232;  
MT[16][13]=232;  
MT[16][14]=131;  
MT[16][15]=232;

MT[17][0]=233;  
MT[17][1]=233;  
MT[17][2]=233; 
MT[17][3]=233;  
MT[17][4]=233;  
MT[17][5]=233;  
MT[17][6]=233;
MT[17][7]=233; 
MT[17][8]=233;  
MT[17][9]=233;  
MT[17][10]=133;  
MT[17][11]=233; 
MT[17][12]=233;  
MT[17][13]=233;  
MT[17][14]=132;  
MT[17][15]=233;

MT[18][0]=234;  
MT[18][1]=234;  
MT[18][2]=234; 
MT[18][3]=234;  
MT[18][4]=234;  
MT[18][5]=234;  
MT[18][6]=234;
MT[18][7]=234; 
MT[18][8]=234;  
MT[18][9]=234;  
MT[18][10]=134;  
MT[18][11]=234; 
MT[18][12]=234;  
MT[18][13]=234;  
MT[18][14]=135;  
MT[18][15]=234;

MT[19][0]=19;  
MT[19][1]=19;  
MT[19][2]=240; 
MT[19][3]=240;  
MT[19][4]=240;  
MT[19][5]=240;  
MT[19][6]=240;
MT[19][7]=240; 
MT[19][8]=240;  
MT[19][9]=240;  
MT[19][10]=240;  
MT[19][11]=240; 
MT[19][12]=240;  
MT[19][13]=20;  
MT[19][14]=140;  
MT[19][15]=240;

MT[20][0]=21;  
MT[20][1]=21;  
MT[20][2]=241; 
MT[20][3]=241;  
MT[20][4]=241;  
MT[20][5]=241;  
MT[20][6]=241;
MT[20][7]=241; 
MT[20][8]=241;  
MT[20][9]=241;  
MT[20][10]=241;  
MT[20][11]=241; 
MT[20][12]=241;  
MT[20][13]=241; 
MT[20][14]=241;  
MT[20][15]=241;

MT[21][0]=21;  
MT[21][1]=21;  
MT[21][2]=242; 
MT[21][3]=242;  
MT[21][4]=242;  
MT[21][5]=242;  
MT[21][6]=242;
MT[21][7]=242; 
MT[21][8]=242;  
MT[21][9]=242;  
MT[21][10]=242;  
MT[21][11]=242; 
MT[21][12]=242;  
MT[21][13]=242; 
MT[21][14]=140;  
MT[21][15]=242; 

MT[22][0]=23;  
MT[22][1]=23;  
MT[22][2]=243; 
MT[22][3]=243;  
MT[22][4]=243;  
MT[22][5]=243;  
MT[22][6]=243;
MT[22][7]=243; 
MT[22][8]=243;  
MT[22][9]=243;  
MT[22][10]=243;  
MT[22][11]=243; 
MT[22][12]=243;  
MT[22][13]=243; 
MT[22][14]=243;  
MT[22][15]=243;

MT[23][0]=23;  
MT[23][1]=23;  
MT[23][2]=244; 
MT[23][3]=244;  
MT[23][4]=244;  
MT[23][5]=244;  
MT[23][6]=244;
MT[23][7]=244; 
MT[23][8]=244;  
MT[23][9]=244;  
MT[23][10]=244;  
MT[23][11]=244; 
MT[23][12]=244;  
MT[23][13]=244; 
MT[23][14]=141;  
MT[23][15]=244; 
// Columnas con valores repetitivos
 for(int i=1; i<=30; i++){
  MT[21][i]=22;  MT[48][i]=50;  MT[52][i]=54;  MT[55][i]=56;  MT[57][i]=58;
  MT[59][i]=60;  MT[61][i]=62;  MT[63][i]=64;  MT[65][i]=66;  MT[68][i]=69;
  MT[70][i]=71;  MT[72][i]=73;  MT[74][i]=75;  MT[80][i]=81;  MT[82][i]=83;
  MT[94][i]=95;
 }
}//fin de la funcion llenar_matriz()