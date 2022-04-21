//Declaro mis librerias que utilizare en mi programa
#include<iostream>
#include<stdlib.h>
#include<sstream>
#include<mysql.h>

//Incluyo mis librerias creadas con funciones tipo void
#include "AgregarAlumno.h"
#include "AgregarGrado.h"
#include "AgregarNota.h"
#include "BuscarAlumno.h"
#include "BuscarGrado.h"
#include "BorrarAlumGra.h"
#include "ModAlumno.h"
#include "ModGrado.h"
#include "ListAlumnos.h"
#include "ModSeccion.h"
#include "AgregarSeccion.h"

using namespace std;

//Incluyo mis funciones de las librerias 
void AgregarAlumno();
void AgregarGrado();
void AgregarSeccion();
void AgregarNota();
void BuscarAlumno();
void BuscarGrado();
void BorrarAlumGra();
void ModAlumno();
void ModGrado();
void ModSeccion();
void ListAlumnos();

//Creo mi funcion principal
int main()
{
	//Declaro mis variables
	int exit, opc;
	
	//Le muestro al usuario un menu donde le indico que funcion quiere realizar
	system("cls");
	system("color 7");
	cout<<"\t\t\t              PROYECTO II           "<<endl<<endl;
	cout<<"\t\t\t\t 1. Agregar Alumno"<<endl;
	cout<<"\t\t\t\t 2. Agregar Grado"<<endl;
	cout<<"\t\t\t\t 3. Agregar Seccion"<<endl;
	cout<<"\t\t\t\t 4. Agregar Nota"<<endl;
	cout<<"\t\t\t\t 5. Buscar Alumno"<<endl;
	cout<<"\t\t\t\t 6. Buscar Grado"<<endl;
	cout<<"\t\t\t\t 7. Borrar Alumno o Grado"<<endl;
	cout<<"\t\t\t\t 8. Modificar Datos de un Alumno"<<endl;
	cout<<"\t\t\t\t 9. Modificar Datos de un Grado"<<endl;
	cout<<"\t\t\t\t10. Modificar Datos de una Seccion"<<endl;
	cout<<"\t\t\t\t11. Listar Alumnos de un Grado y Seccion"<<endl;
	cout<<"\t\t\t\t12. Salir"<<endl<<endl;
	cout<<"\t\t\t\tIngrese una opcion: ";
	cin>>opc;
	
	//Ciclo donde si el usuario no ingresa la opcion correcta, el programa volvera a pedirlo
	while(opc<=0||opc>12)
	{
		cout<<"\n\t\t\t\tOpcion Invalida"<<endl;
		cout<<"\t\t\t\tIngrese una opcion: ";
		cin>>opc;
	}
	
	//Inicio un switch donde agrego mis funciones incluidas al principio del programa
	switch(opc){
		
		case 1:
			AgregarAlumno();
			break;
			
		case 2:
			AgregarGrado();
			break;
			
		case 3:
			AgregarSeccion();
			break;
			
		case 4:
			AgregarNota();
			break;
			
		case 5:
			BuscarAlumno();
			break;
			
		case 6:
			BuscarGrado();
			break;
		
		case 7:
			BorrarAlumGra();
			break;
		
		case 8:
			ModAlumno();
			break;
		
		case 9:
			ModGrado();
			break;
		
		case 10:
			ModSeccion();
			break;
			
		case 11:
			ListAlumnos();
			break;
		
		//Opcion donde se valida si el usuario desea salir del programa
		case 12:
			system("cls");
			system("color c");
			cout<<endl;
			cout<<"\t\t\t\tEsta seguro que desea salir\n\n";
			cout<<"\t\t\t\tPresione '1' para SI\n";
			cout<<"\t\t\t\tPresione '2' para NO\n\n ";
			cout<<"\t\t\t\t";
			cin>>exit;
			cout<<endl;
			
			if(exit == 1)
			{
				return 0;
			}
			
			else if(exit == 2)
			{
				return main();
			}
			
			//Ciclo donde valida si el usuario ingresa la opcion correcta
			while(exit<=0 || exit>2){
				system("cls");
				system("color c");
				cout<<endl;
				cout<<"\n\t\t\t\tOpcion Invalida"<<endl<<endl;
				cout<<"\t\t\t\tEsta seguro que desea salir\n\n";
				cout<<"\t\t\t\tPresione '1' para SI\n";
				cout<<"\t\t\t\tPresione '2' para NO\n\n ";
				cout<<"\t\t\t\t";
				cin>>exit;
				cout<<endl;
				
				if(exit == 1)
				{
					return 0;
				}
				
				else if(exit == 2)
				{
					return main();
				}	
			}
			break;
	}

	return main();
	
	//Fin del programa
}



