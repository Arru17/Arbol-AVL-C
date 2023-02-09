#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesLab3Arboles.h"

int main(){
	char nombre[31];
	char apellidoP[31];
	char apellidoM[31];
	char nombreMascota[21];
	char especieMascota[21]; 
	char numeroTelefono[21];
	char fechaControl[11]; 
	char vacunas[3];
   	int edadMascota, numeroAtenciones;
	int	cantidadDeRegistros;
	FILE* fichero;
	
   	fichero = abrirArchivo();
	fscanf(fichero, "%d", &cantidadDeRegistros);
	if (fgetc(fichero) == '\r') {
		fgetc(fichero);
	}
	Arbol* arbol;
	arbol= crearArbol();
	
	int aux;
   	for(aux=0; aux < cantidadDeRegistros; aux++){
	
		fscanf(fichero, "%s %s %s %s %s %d %s %d %s %s",nombre, apellidoP, apellidoM, nombreMascota,especieMascota,&edadMascota,numeroTelefono,&numeroAtenciones,vacunas,fechaControl);
			
		Mascota* mascota= crearMascota(nombreMascota,especieMascota,edadMascota,numeroAtenciones,vacunas, fechaControl);
		NodoArbol* existente;
		existente= buscarRegistro(arbol->raiz, nombre, apellidoP, apellidoM);
		if(existente !=NULL){
			insertarEnListaMascota(existente->cliente->listaMascotas, mascota);
		}
		else{
			Cliente* client= crearCliente(nombre,apellidoP,apellidoM,numeroTelefono);
			insertarEnListaMascota(client->listaMascotas, mascota);
			NodoArbol* nodo;
			nodo= crearNodoArbol(client);
			insertarArbol(arbol, nodo);
		}
		if (fgetc(fichero) == '\r'){
			fgetc(fichero);
		}
   }
	int accion;
	char salto;
	do{
		do{ 
			printf("Para elegir la accion a realizar debe ingresar un numero:\n"
		        "1.- Agregar registro de Mascota.\n"
				"2.- Eliminar registro de Mascota.\n"
				"3.- Buscar por fecha de control.\n"
				"4.- Modificar datos de una Mascota.\n"
				"5.- Imprimir Arbol (In, Pre y Post).\n"
				"6.- Salir. \n"                                                  );
				
			
		}while(((scanf("%d%c",&accion, &salto) != 2 || salto != '\n') && limpiarStdin()) || (accion < 1 || accion > 6));
		if(accion ==1){
			printf("Ingrese a continuacion todos los datos del registro. \n");
			
			char nombreNuevo[31];
			printf("Ingrese Nombre del duenio. \n");
			scanf("%s", nombreNuevo);
			
			char apellidoPNuevo[31];
			printf("Ingrese Apellido paterno del duenio. \n");
			scanf("%s", apellidoPNuevo);
			
			char apellidoMNuevo[31];
			printf("Ingrese Apellido materno del duenio. \n");
			scanf("%s", apellidoMNuevo);
			
			char nombreMascotaNuevo[21];
			printf("Ingrese Nombre de la mascota. \n");
			scanf("%s", nombreMascotaNuevo);
			
			char especieMascotaNuevo[21]; 
			printf("Ingrese Especie de la mascota. \n");
			scanf("%s", especieMascotaNuevo);
			
			char numeroTelefonoNuevo[21];
			printf("Ingrese Numero de telefono del duenio. \n");
			scanf("%s", numeroTelefonoNuevo);
			
			char fechaControlNuevo[11]; 
			printf("Ingrese la Fecha del proximo control de la mascota (en formato DD/MM/AAAA). \n");
			scanf("%s", fechaControlNuevo);
			
			char vacunasNuevo[3];
			printf("Posee al dia sus vacunas? (Si/No). \n");
			scanf("%s", vacunasNuevo);
			
			int edadMascotaNuevo, numeroAtencionesNuevo;
			printf("Ingrese Edad de la mascota. \n");
			scanf("%d", &edadMascotaNuevo);
			
			printf("Ingrese Numero de atenciones de la mascota. \n");
			scanf("%d", &numeroAtencionesNuevo);
			
			Mascota* mascotaNueva= crearMascota(nombreMascotaNuevo,especieMascotaNuevo,edadMascotaNuevo,numeroAtencionesNuevo,vacunasNuevo, fechaControlNuevo);
			NodoArbol* existe;
			existe= buscarRegistro(arbol->raiz, nombreNuevo, apellidoPNuevo, apellidoMNuevo);
			if(existe !=NULL){
				insertarEnListaMascota(existe->cliente->listaMascotas, mascotaNueva);
			}
			else{
				Cliente* clienteNuevo= crearCliente(nombreNuevo,apellidoPNuevo,apellidoMNuevo,numeroTelefonoNuevo);
				insertarEnListaMascota(clienteNuevo->listaMascotas, mascotaNueva);
				NodoArbol* nodoNuevo;
				nodoNuevo= crearNodoArbol(clienteNuevo);
				insertarArbol(arbol, nodoNuevo);
			}
			printf("Se ha registrado correctamente a la mascota. \n\n");
			accion=0;
		}
		if(accion ==2){
			char nombreDato[31];
			printf("Ingrese nombre del duenio\n");
			scanf("%s", nombreDato);
			char apellidoPDato[31];
			printf("Ingrese apellido paterno del duenio\n");
			scanf("%s", apellidoPDato);
			char apellidoMDato[31];
			printf("Ingrese apellido materno del duenio\n");
			scanf("%s", apellidoMDato);
			NodoArbol* registro;
			registro= buscarRegistro(arbol->raiz, nombreDato, apellidoPDato, apellidoMDato);
			if(registro != NULL){
				if(registro->cliente->listaMascotas->largo >1){
					char nombreMDato[21];
					printf("Ingrese nombre de la mascota \n");
					scanf("%s", nombreMDato);
					Mascota* seleccionada;
					seleccionada= revisarListaMascotas(registro->cliente->listaMascotas, nombreMDato);
					if(seleccionada != NULL){
						eliminarMascota(registro->cliente->listaMascotas, seleccionada);
					}else{
						printf("La mascota que busca no pertenece al duenio indicado. \n");
					}
				}else if(registro->cliente->listaMascotas->largo ==1){
					char nombreMDato[21];
					printf("Ingrese nombre de la mascota \n");
					scanf("%s", nombreMDato);
					Mascota* seleccionada;
					seleccionada= revisarListaMascotas(registro->cliente->listaMascotas, nombreMDato);
					if(seleccionada != NULL){
						borrarDato(arbol, registro);
						free(registro->cliente->listaMascotas->primera);
						free(registro->cliente->listaMascotas);
						free(registro->cliente);
						free(registro);
					}else{
						printf("La mascota que busca no pertenece al duenio indicado. \n");
					}
				}
				else{
					printf("Ha ocurrido un error desconocido. \n");
				}
			}else{
				printf("No existen registros de ese duenio. \n");
			}
			accion=0;
		}
		if(accion ==3){
			char fechaBuscar[8];
			printf("Ingrese fecha en formato MM/AAAA \n");
			scanf("%s", fechaBuscar);
			
			FILE* archivo;
			archivo= prepararArchivo();
			buscarFecha(arbol->raiz, fechaBuscar, archivo);
			fclose(archivo);
			accion=0;
		}
		if(accion ==4){
			printf("Ingrese dato de la mascota que desea modificar \n"
				   "1- Nombre. \n"
				   "2- Edad.\n"
				   "3- Numero de atenciones.\n"
				   "4- Vacunas. \n"
				   "5- fecha proximo control. \n"
				   "6- telefono (Duenio). \n");
			int eleccion;
			scanf("%d", &eleccion);
			char nombreReg[31];
			printf("Ingrese nombre del duenio\n");
			scanf("%s", nombreReg);
			char apellidoPReg[31];
			printf("Ingrese apellido paterno del duenio\n");
			scanf("%s", apellidoPReg);
			char apellidoMReg[31];
			printf("Ingrese apellido materno del duenio\n");
			scanf("%s", apellidoMReg);
			NodoArbol* nodoRegis;
			nodoRegis= buscarRegistro(arbol->raiz, nombreReg, apellidoPReg, apellidoMReg);
			if(nodoRegis != NULL){
				if(eleccion == 1){
					char nombreMReg[21];
					printf("Ingrese el nombre de la mascota. \n");
					scanf("%s", nombreMReg);
					char nuevoDato[21];
					printf("Ingrese el nuevo nombre. \n");
					scanf("%s", nuevoDato);
					Mascota* mascAux;
					mascAux=revisarListaMascotas(nodoRegis->cliente->listaMascotas, nombreMReg);
					if(mascAux != NULL){
						strcpy(mascAux->nombreM, nuevoDato);
					}else{
						printf("La mascota indicada no pertenece al duenio indicado. \n");
					}
				}
				else if (eleccion ==2){
					char nombreMReg[21];
					printf("Ingrese el nombre de la mascota. \n");
					scanf("%s", nombreMReg);
					int nuevoDato;
					printf("Ingrese la nueva edad. \n");
					scanf("%d", &nuevoDato);
					Mascota* mascAux;
					mascAux=revisarListaMascotas(nodoRegis->cliente->listaMascotas, nombreMReg);
					if(mascAux != NULL){
						mascAux->edad= nuevoDato;
					}else{
						printf("La mascota indicada no pertenece al duenio indicado. \n");
					}
				}
				else if (eleccion ==3){
					char nombreMReg[21];
					printf("Ingrese el nombre de la mascota. \n");
					scanf("%s", nombreMReg);
					int nuevoDato;
					printf("Ingrese el nuevo numero de atenciones. \n");
					scanf("%d", &nuevoDato);
					Mascota* mascAux;
					mascAux=revisarListaMascotas(nodoRegis->cliente->listaMascotas, nombreMReg);
					if(mascAux != NULL){
						mascAux->numAtenciones= nuevoDato;
					}else{
						printf("La mascota indicada no pertenece al duenio indicado. \n");
					}
				}
				else if (eleccion ==4){
					char nombreMReg[21];
					printf("Ingrese el nombre de la mascota. \n");
					scanf("%s", nombreMReg);
					char nuevoDato[3];
					printf("Posee las vacunas al dia? (Si/No). \n");
					scanf("%s", nuevoDato);
					Mascota* mascAux;
					mascAux=revisarListaMascotas(nodoRegis->cliente->listaMascotas, nombreMReg);
					if(mascAux != NULL){
						strcpy(mascAux->vacunas, nuevoDato);
					}else{
						printf("La mascota indicada no pertenece al duenio indicado. \n");
					}
				}
				else if (eleccion ==5){
					char nombreMReg[21];
					printf("Ingrese el nombre de la mascota. \n");
					scanf("%s", nombreMReg);
					char nuevoDato[21];
					printf("Ingrese fecha del proximo control. \n");
					scanf("%s", nuevoDato);
					Mascota* mascAux;
					mascAux=revisarListaMascotas(nodoRegis->cliente->listaMascotas, nombreMReg);
					if(mascAux != NULL){
						strcpy(mascAux->fechaProxControl, nuevoDato);
					}else{
						printf("La mascota indicada no pertenece al duenio indicado. \n");
					}
				}
				else if (eleccion ==6){
					char nuevoDato[21];
					printf("Ingrese el nuevo numero de telefono. \n");
					scanf("%s", nuevoDato);
					strcpy(nodoRegis->cliente->fono, nuevoDato);
				}else{
					printf("Has ingresado una opcion no existente. \n");
				}
			}else{
				printf("No se ha encontrado el duenio indicado. \n");
			}
			accion=0;
		} 
		if(accion == 5){
			printf("\n IN ORDEN *************************\n\n");
			recorrerIn(arbol->raiz);
			printf("\n PRE ORDEN ************************\n\n");
			recorrerPre(arbol->raiz);
			printf("\n POST ORDEN ***********************\n\n");
			recorrerPost(arbol->raiz);
			accion=0;
		}
		if(accion == 6){
			
		}
	}while(accion!=1 && accion!=2 && accion!=3 && accion!=4 && accion!=5 && accion!=6);
	vaciarArbol(arbol->raiz);
	free(arbol);
   
   return 1;
}