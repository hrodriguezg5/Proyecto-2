using namespace std;

//Estructura donde declaro que tipo de datos tendran mis variables
struct DataBaseAlumno2{
	string Clave, Clave1, Nombre, Apellido, Correo, Grado, Seccion, sql;
	string IdGrado, IdNotas, IdClave, IdSeccion, IdAsignacion, IdAlumno;
	string Bimestre1, Bimestre2, Bimestre3, Bimestre4;
	string text1, text2, text3, text4;
    int resultado, opcion,opc, band, band2, gint, sint, a, b;
};

//Inicio mi funcion tipo void
void AgregarGrado(){
	
	struct DataBaseAlumno2 db;
	
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
			cout<<"\t\t\t\tIngrese un codigo para el nuevo grado: ";
			cin>>db.IdGrado;
			cout<<"\t\t\t\tIngrese un nombre para el nuevo grado: ";
			cin>>db.Grado;
				
			//Generando un nuevo bucle donde valido si los datos ingresados anteriormente se encuentran ya registrados
			do{		
				db.sql = "SELECT * FROM grado WHERE IdGrado="+db.IdGrado+" OR Grado='"+db.Grado+"'";
				query = db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				data=mysql_store_result(conexion);
				countRows=mysql_num_rows(data);
				
				//Condicional que se cumple si los datos ya se encuentran registrados
				if(countRows>=1){
					system("cls");
					cout<<endl;
					cout<<"\t\t\t\tDatos ya existentes!\n";
					cout<<"\t\t\t\tEl codigo '"+db.IdGrado+"' o nombre '"+db.Grado+"' ya se encuentran ingresados\n\n\n";
					db.sql = "SELECT * FROM grado";
					query = db.sql.c_str();
					db.resultado=mysql_query(conexion, query);
							
					//Imprimiendo de nuevo mi tabla grado en tal caso los datos ingresados esten duplicados
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
					}
					
					//Pidiendole datos al usuario
					cout<<"\n\t\t\t\tIngrese un codigo diferente para el nuevo grado: ";
					cin>>db.IdGrado;
					cout<<"\t\t\t\tIngrese un nombre diferente para su nuevo grado: ";
					cin>>db.Grado;
					db.band=1;
				}
				
				//Si los datos no se encuentran registrados, se registran automaticamente en la base de datos
				else{
					db.sql="INSERT INTO grado (IdGrado, Grado) VALUES ('"+db.IdGrado+"', '"+db.Grado+"')";
					query=db.sql.c_str();
					db.resultado=mysql_query(conexion, query);
					system("cls");
					system("color a");
					cout<<"\t\t\t\tRegistro guardado exitosamente";
					db.band=0;
				}
			
			}while(db.band==1);
		}
		
		//Muestro en pantalla el error si la validacion de la condicional principal no se cumplio
		else{
			system("cls");
			system("color c");
			cout<<"\t\t\t\tNo se pudo generar la consulta";
			cout<<"\t\t\t\t"<<mysql_error(conexion);
		}
		
		//Le indico al usuario que presione la opcion que desee realizar 
		cout<<endl<<endl;
		cout<<"\t\t\t\tPresione '1' para volver a agregar un grado"<<endl;
		cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
		cout<<"\t\t\t\t"; cin>>db.opc;
		
		//Ciclo que se crea si el usuario ingreso una opcion incorrecta
		while(db.opc<1 || db.opc>2){
			system("cls");
			system("color c");
			cout<<"\t\t\t\tOpcion Invalida!\n";
			cout<<"\t\t\t\tVuelva a Ingresar una Opcion\n ";
			cout<<endl<<endl;
			cout<<"\t\t\t\tPresione '1' para volver a agregar un grado"<<endl;
			cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
			cout<<"\t\t\t\t"; cin>>db.opc;
		}
		
	//Fin del bucle
	} while(db.opc==1);	
}
