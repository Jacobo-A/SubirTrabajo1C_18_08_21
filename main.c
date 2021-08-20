/*
Nombre de la comunidad:
Nombre: FLores Jacobo Alejandro 
UEA:       Fundamentos de programación
Profesor: Dra. Rafaela Blanca Silva López
Fecha:    14-07-2020
  
Proyecto final
Información de la versión: Dev-C++ 5.1.1
Copyright licenciamiento creative commons CC-BY-NC-SA.
*/

#include <stdio.h>
#define max 50

//#include <string.h>

typedef struct {
	int clave;
	char tipo[10];
	float peso;
	float altura;
	char dueno[20];
	float precio;
}animal;

void imprimir_arreglo(animal *, int);
//0
void guardarcontador(int *);
int replicar_cantidad();

int menu();
//1
void lectura_d(animal *,int *);
animal leer();
void escritura_a(animal *);
//2
void actualizar_A(animal *, int);
//3
void alta_a(animal *, int *);
//4
void baja_a(animal *, int *);
void recorrer (animal *, int );
void reescritura_a(animal *animales, int);
//5
void consultar(animal *, int);
//6
void consultar_r_B();
//7 
void modificar_r(animal *, int);
//8
void leer_a(animal *, int);



int main (void){

	animal animales[max];
	int opc;
	int contador=0;
	do{ 
		system("cls");
		opc = menu();
		
		switch (opc){
			case 0: guardarcontador(&contador); break;
			case 1: lectura_d(animales, &contador); break;
			case 2: alta_a(animales, &contador); break;
			case 3: baja_a(animales, &contador); reescritura_a(animales, contador); break;
			case 4: consultar(animales, contador); break;
			case 5: modificar_r(animales, contador); reescritura_a(animales, contador); break;
			case 6: consultar_r_B(animales, contador); system("pause"); break;
			case 7:	actualizar_A(animales, contador); break;
			case 8: contador=replicar_cantidad(); leer_a(animales, contador);  break;
			case 10: imprimir_arreglo(animales, contador); break;			
		}
	}while (opc != 0);

	return 0;
}
//imprimir arreglo
void imprimir_arreglo(animal *checkpoint,int contador){
	
	for (int i=0; i<contador; i++){
		printf("%i", (checkpoint+i)->clave);
		printf(" %s", (checkpoint+i)->tipo );
		printf(" %.2f", (checkpoint+i)->peso);
		printf(" %.2f",(checkpoint+i)->altura ) ;
		printf(" %s", (checkpoint+i)->dueno);
		printf (" %.2f\n\n", (checkpoint+i)->precio);
	}
	printf ("contador : %i\n", contador);
	system("pause");
}
//menu
int menu (){
	int opc;
	printf ("\n\t***** Control de inventarios Tienda de animales *****\n\n");
	printf ("\t\t1) Lectura de datos.\n"); //lee los datos
	printf ("\t\t2) Alta de un animal. \n"); //inresar alta desues dar a conocer la lista.
	printf ("\t\t3) Baja de un animal. \n"); //imprimir datos para conocer cual hayq eu dar de baja
	printf ("\t\t4) Consulta por clave.\n");
	printf ("\t\t5) Modificar registro. \n");
	printf ("\t\t6) Consulta inventario. \n"); //imprimir inventario en la pantalla de c
	printf ("\t\t7) Actualizar datos del Registro.TxT\n\n"); //pasar datos aun archivo txt comprensible para el
	printf ("\t\t8) --> Actualizar base de datos. <-- \n\n");
	printf ("\t\t0) Salir\n\n");
	printf (" !Cerrar de manera incorrecta el programa puedede ocacionar su mal funcionamiento.\n");
	printf (" !Para cargar datos antes ingresados presione 8)\n\n");
	printf (" Elegir opcion: ");
	scanf ("%i", &opc);
	return opc;
}

//0
void guardarcontador(int *contador){
	
	int dato;
	
	FILE *cantidad=fopen("contador.bin", "wb");
	if (cantidad == NULL){
		printf ("Error al intentar acceder al archivo.\n");
		system ("pause");
	}
	fwrite (contador,sizeof(dato),1, cantidad);
	fclose(cantidad);
	system("pause");
}
int replicar_cantidad(){
	int canti;
	FILE *cantidad=fopen("contador.bin", "rb");
	if (cantidad == NULL){
		printf ("Error al intentar acceder al archivo.\n");
		system ("pause");
	}
	fread (&canti, sizeof(canti), 1, cantidad);
	fclose(cantidad);
	return  canti;
}

// 1)
void lectura_d(animal *animales, int *contador){
	
	system("cls");
	int cantidad;

	printf ("Numero de altas: ");
	scanf ("%i", &cantidad);

	for (int i=0; i<cantidad; i++){
		*(animales+i) = leer();
		escritura_a(animales+i); //guardarlo
		(*contador) ++;
	}
	system ("pause");
}
animal leer(){
	animal alta;
	printf ("-----------------------\n");
	printf ("Clave: ");
	scanf ("%i", &alta.clave);
	fflush(stdin);
	printf ("Tipo: ");
	gets(alta.tipo);
	printf ("Peso (kg): ");
	scanf ("%f", &alta.peso);
	printf ("Altura (cm): ");
	scanf ("%f", &alta.altura);
	fflush (stdin);
	printf ("Dueño: ");
	gets(alta.dueno);
	printf ("Precio $: ");
	scanf ("%f", &alta.precio);	
	return alta;
}
void escritura_a(animal *animales){

	FILE* archivo;
	archivo=fopen ("Registro.bin", "ab");
	if (archivo == NULL){
		printf ("Error al intentar acceder al archivo.\n");
		system ("pause");
	}
	else{
		
		fwrite (animales, sizeof (animal), 1, archivo);
		printf("\t\a\n [Registrado]\n");
		printf ("-----------------------\n");
		fclose(archivo);
	}
}

// 2)
void alta_a(animal *lista, int *contador){
	animal alta, animales;
	alta = leer();
	
	FILE* archivo=fopen ("registro.bin", "rb+");
	if (archivo == NULL){
		printf ("Error al intentar acceder al archivo.\n");
		system ("pause");
	}else {
		while ( fread(&animales, sizeof(animales), 1, archivo)){
			if(alta.clave == animales.clave){
				printf ("\ !!!!!Error de alta, clave igual.!!!!!\n");
				system("pause");
				return;
			}
		}
		// no coincide con ninguna clave entonces hay que agregarla.
		escritura_a(&alta);		
		*(lista + (*contador) ++) = alta; //agrega la nueva alta al arreglo de animales y aumentar el contador en 1
	
		consultar_r_B(lista, *contador);
		system("pause");
	}
}
// 3) 
void baja_a(animal *animales, int *contador){
	system ("cls");

	int clave;
	consultar_r_B(animales, *contador);

	
	printf ("Ingresa la clave de baja: ");
	scanf ("%i", &clave);
	for(int i=0; i<*contador; i++){
		if( clave == (animales+i)->clave){
			 //reduce en 1 al conteo en el arreglo
			recorrer ( (animales+i) , *contador);
			(*contador) -= 1;
			reescritura_a ( (animales+i), *contador);
			return;
		}
	}
}
void recorrer(animal *inicio, int contador){
	for (int i=0; i<contador; i++ ){
		*(inicio+i)= *(inicio+i+1);		
	}
	printf ("\tRegistro eliminado. \n");
	system("pause");
}
void reescritura_a(animal animales[max], int contador){
	animal dato;
	FILE* archivo=fopen ("Registro.bin", "wb");
	if (archivo == NULL){
		printf ("Error al intentar acceder al archivo.\n");
		system ("pause");
	}else {
		for (int i=0; i<contador; i++){
			fwrite (&animales[i], sizeof (dato), 1 ,archivo);		
		}
	}fclose(archivo);
		
}
// 4)
void consultar(animal *animales, int contador){
	int clave, i;
	printf ("Consultar por clave: ");
	scanf ("%i" ,&clave);
	
	for (i=0; i<=contador; i++){
		if ( clave == (animales + i)->clave ){
			consultar_r_B((animales + i ), 1);
			return;
		}
	}
	if (i>contador){
		printf ("\n\tClave no encontrada. \n\n");
	}
	system ("pause");
}
// 5)
void modificar_r(animal *animales, int contador){
	
	system("cls");
	consultar_r_B(animales, contador);
	int clave;
	printf ("Ingresar la clave a modificar: ");
	scanf ("%i", &clave);
	for (int i=0; i<=contador; i++){
		if (clave == (animales+i)->clave){
			printf("\n\t1)Modificar clave.\n");
			printf("\t2)Modificar tipo.\n");
			printf("\t3)Modificar peso.\n");
			printf("\t4)Modificar altura.\n");
			printf("\t5)Modificar dueño.\n");
			printf("\t6)Modificar precio.\n");
			printf("\t0)Menu principal.\n\n");
			printf ("Ingresa opcion: ");
			scanf ("%i", &clave);
			switch (clave){
				case 1: printf ("Clave: "); scanf ("%i", &(animales+i)->clave); break;
				case 2: printf ("Tipo: "); scanf ("%s", &(animales+i)->tipo); break;
				case 3: printf ("Peso: "); scanf ("%f", &(animales+i)->peso); break;	
				case 4: printf ("Altura: "); scanf ("%f", &(animales+i)->altura); break;
				case 5: printf ("Dueño: "); scanf ("%s", &(animales+i)->dueno); break;
				case 6: printf ("Precio: "); scanf ("%f", &(animales+i)->precio); break;
				case 0: break;			
			}
			printf ("\n\t\aOperacion realizada.");	
			system ("pause");	
			return;
		}	
	}
}
// 6)
void consultar_r_B(animal *animales,int contador){

		printf("-----------------------------------------------------------------------------\n");
		printf("%10s %9s %11s", "Clave", "Tipo", "Peso (kg)");
		printf("%15s %9s %13s\n\n", "Altura (cm)", "Dueño", "Precio ($)");
		for (int i=0; i<contador; i++){
			printf("%10i", (animales+i)->clave);
			printf("%10s", (animales+i)->tipo );
			printf("%10.2f", (animales+i)->peso);
			printf("%15.2f",(animales+i)->altura ) ;
			printf("%13s", (animales+i)->dueno);
			printf ("%12.2f\n", (animales+i)->precio);
		}
		printf("-----------------------------------------------------------------------------\n");
}
// 7)
void actualizar_A(animal *animales, int contador){
	FILE *archivo=fopen("Registro.txt", "w");
	for (int i=0; i<contador; i++){
		fprintf (archivo,"%i", (animales+i)->clave);
		fprintf (archivo," %10s", (animales+i)->tipo);
		fprintf (archivo," %13.2f", (animales+i)->peso);
		fprintf (archivo," %15.2f", (animales+i)->altura);
		fprintf (archivo," %10s", (animales+i)->dueno);
		fprintf (archivo," %13.2f\n", (animales+i)->precio);
	}
	fclose(archivo);
	printf ("\n\t\t\a***REGISTRO ACTUALIZADO.***\n");
	system("pause");
}
// 8)
void leer_a(animal animales[max], int contador){
	animal dato;

	FILE* archivo;
	archivo=fopen ("Registro.bin", "rb");
	if (archivo == NULL){
		printf ("\t\nError al intentar acceder al archivo.\n");
		system ("pause");
	}	
	else{		
		 for (int i=0; i<contador; i++)
		 {
		 	fread (&animales[i], sizeof (dato), 1, archivo) ;
		 }
		fclose(archivo);
		printf ("\n\t\t\a!!!!!!Base de datos actualizada.!!!!!! \n");
		system ("pause");	
	}
}
