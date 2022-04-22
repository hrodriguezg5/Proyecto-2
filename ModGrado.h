using namespace std;

//Estructura donde declaro que tipo de datos tendran mis variables
struct DataBaseAlumno8{
	string Clave, Clave1, Nombre, Apellido, Correo, Grado, Seccion, sql;
	string IdGrado, IdNotas, IdClave, IdSeccion, IdAsignacion, IdAlumno;
	string Bimestre1, Bimestre2, Bimestre3, Bimestre4;
	string text1, text2, text3, text4;
    int resultado, opcion,opc, band, band2, gint, sint, a, b;
};

//Inicio mi funcion tipo void
void ModGrado(){
	
	struct DataBaseAlumno8 db;
	
	//Declarando mis funciones para mapear mis filas y columnas en la base de datos
	system("cls");
	MYSQL* conexion;
	MYSQL_ROW row;
	MYSQL_RES* data;
	
	//Conectandome a la base de datos
	conexion=mysql_init(0);
	conexion=mysql_real_connect(conexion, "localhost", "Admin", "Admin", "proyecto-2", 3306, NULL, 0);
	const char* query;
	
	//Iniciando el bucle para pedirle al usuario que ingrese datos y luego registrarlos
	do{
	
		//Haciendo una consulta a la base de datos donde me muestra todos los registros de mi tabla grado
		system("cls");
		system("color 7");
		db.sql = "SELECT * FROM grado";
		query = db.sql.c_str();
		db.resultado=mysql_query(conexion, query);
				
		//Imprimiendo mi tabla grado
		if (db.resultado==0){
			data=mysql_store_result(conexion);
			int countColumns=mysql_num_fields(data);
			int countRows=mysql_num_rows(data);
			cout<<"\t\t\t\tCodigo\tGrado"<<endl;
			cout<<"\t\t\t\t------\t-----";
			cout<<endl<<endl;
			
			while(row=mysql_fetch_row(data)){
				cout<<"\t\t\t\t";
				for (int i=0; i<countColumns; i++){
					cout<<row[i]<<"\t";
				}
				
				cout<<endl;
			}
			
			//Pidiendo datos al usuario
			cout<<endl<<endl;
			cout<<"\t\t\t\tIngrese el codigo del grado a modificar: ";
			cin>>db.IdGrado;
			
			//Si el usuario ingresa un codigo incorrecto, se le vuelve a pedir que ingrese uno
			do{		
				db.sql = "SELECT * FROM grado WHERE IdGrado="+db.IdGrado+"";
				query = db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				data=mysql_store_result(conexion);
				countRows=mysql_num_rows(data);
				
				if(countRows==0){
					cout<<endl;
					cout<<"\t\t\t\tCodigo Invalido!\n";
					cout<<"\t\t\t\tEl codigo no existe en la tabla grado\n";
					cout<<"\t\t\t\tIngrese el codigo del grado a modificar: ";
					cin>>db.IdGrado;
					db.band=1;
				}
				
				else{
					db.band=0;
				}
			
			}while(db.band==1);
		}
		
		//Realizo un query donde introduzco el codgio del grado que el usuario ingreso
		system("cls");
		db.sql = "SELECT * FROM grado WHERE IdGrado="+db.IdGrado+"";
		query = db.sql.c_str();
		db.resultado=mysql_query(conexion, query);
		
		//Imprimiendo el registro del grado a modificar
		if (db.resultado==0){
			data=mysql_store_result(conexion);
			int countColumns=mysql_num_fields(data);
			int countRows=mysql_num_rows(data);
			cout<<"\t\t\t\tCodigo\tGrado"<<endl;
			cout<<"\t\t\t\t------\t-----";
			cout<<endl<<endl;
			
			if(countRows>0){
				
				while(row=mysql_fetch_row(data)){
					cout<<"\t\t\t\t";
					for (int i=0; i<countColumns; i++){
						cout<<row[i]<<"\t";
					}
					
					cout<<endl;
				}
				
				//Preguntandole al usuario si desea modificar el registro
				system("color c");
				cout<<endl;
				cout<<"\t\t\t\tEsta seguro de modificar este registro?\n\n";
				cout<<"\t\t\t\tPresione '1' para SI\n";
				cout<<"\t\t\t\tPresione '2' para NO\n\n ";
				cout<<"\t\t\t\t";
				cin>>db.band;
				cout<<endl;
				
				//Si el usuario ingresa una opcion incorrecta, se le vuelve a pedir que lo ingrese correctamente
				while(db.band<1 || db.band>2){
					system("cls");
					system("color c");
					cout<<"\t\t\t\tOpcion Invalida!\n";
					cout<<"\t\t\t\tVuelva a Ingresar una Opcion\n ";
					cout<<endl<<endl;
					cout<<"\t\t\t\tEsta seguro de modificar este registro?\n\n";
					cout<<"\t\t\t\tPresione '1' para SI\n";
					cout<<"\t\t\t\tPresione '2' para NO\n\n ";
					cout<<"\t\t\t\t";
					cin>>db.band;
					cout<<endl;
				}
				
				//Condicional que se cumple si el usuario escoge la primera opcion
				if(db.band==1){
					
					//Pidiendole un nombre del grado al usuario
					system("cls");
					system("color 7");
					cout<<"\t\t\t\tIngrese el nuevo Nombre del grado: ";
					cin>>db.Grado;
					
					//Realizo un query donde introduzco el nombre del grado que el usuario ingreso	
					system("cls");	
					db.sql = "SELECT * FROM grado WHERE Grado='"+db.Grado+"'";
					query=db.sql.c_str();
					db.resultado=mysql_query(conexion, query);
					
					//Realizo una condicional donde valido si la consulta se realizó correctamente
					if(db.resultado==0){
						data=mysql_store_result(conexion);
						int countColumns=mysql_num_fields(data);
						int countRows=mysql_num_rows(data);
						
						/*Muestro un mensaje donde le indico al usuario que ha ingresado un nombre igual a la de un 
					   	  registro de mi tabla grado*/
						if(countRows>0){
							system("color c");
							cout<<"\t\t\t\tError al modificar el nombre del grado\n\n";
							cout<<"\t\t\t\tEl nombre '"+db.Grado+"' ya se encuentra en la tabla grado\n\n";
							cout<<"\t\t\t\tRegistro no modificado\n\n";
						}
						
						/*Si los datos ingresados anteriormente no se encuentran repetidos en la tabla grado, 
						  actualizo automaticamente el nombre*/
						else{
							system("cls");
							db.sql="UPDATE grado SET Grado = '"+db.Grado+"'WHERE IdGrado='"+db.IdGrado+"'";
							query=db.sql.c_str();
							db.resultado=mysql_query(conexion, query);
							system("color a");
							cout<<"\t\t\t\tRegistro guardado exitosamente";
						}
					}
			
				}
					
				//Muestro un mensaje donde el usuario decidio no modificar el registro
				else{
					system("cls");
					system("color c");
					cout<<"\t\t\t\tRegistro no modificado";
				
				}
			}
		}
		
		//Muestro en pantalla el error si la validacion de la condicional principal no se cumplio
		else{
			system("color c");
			cout<<"\t\t\t\tNo se pudo generar la consulta\n\n";
			cout<<"\t\t\t\t"<<mysql_error(conexion); 
		}
		
		//Le indico al usuario que presione la opcion que desee realizar 
		cout<<endl<<endl;
		cout<<"\t\t\t\tPresione '1' para volver a modificar un grado"<<endl;
		cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
		cout<<"\t\t\t\t"; cin>>db.opc;
		
		//Ciclo que se crea si el usuario ingreso una opcion incorrecta
		while(db.opc<1 || db.opc>2){
			system("cls");
			system("color c");
			cout<<"\t\t\t\tOpcion Invalida!\n";
			cout<<"\t\t\t\tVuelva a Ingresar una Opcion\n ";
			cout<<endl<<endl;
			cout<<"\t\t\t\tPresione '1' para volver a modificar un grado"<<endl;
			cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
			cout<<"\t\t\t\t"; cin>>db.opc;
		}	
		
	//Fin del bucle
	}while(db.opc==1);	
} 

