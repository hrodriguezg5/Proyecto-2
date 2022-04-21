using namespace std;

//Estructura donde declaro que tipo de datos tendran mis variables
struct DataBaseAlumno4{
	string Clave, Clave1, Nombre, Apellido, Correo, Grado, Seccion, sql;
	string IdGrado, IdNotas, IdClave, IdSeccion, IdAsignacion, IdAlumno;
	string Bimestre1, Bimestre2, Bimestre3, Bimestre4;
	string text1, text2, text3, text4;
    int resultado, opcion,opc, band, band2, gint, sint, a, b;
};

//Inicio mi funcion tipo void
void BuscarAlumno(){
	
	struct DataBaseAlumno4 db;
	
	//Declarando mis funciones para mapear mis filas y columnas en la base de datos
	system("cls");
	MYSQL* conexion;
	MYSQL_ROW row;
	MYSQL_RES* data;
	
	//Conectandome a la base de datos	
	conexion=mysql_init(0);
	conexion=mysql_real_connect(conexion, "localhost", "Admin", "Admin", "proyecto-2", 3306, NULL, 0);
	const char* query;
	
	//Iniciando el bucle para pedirle que busque un grado
	do{
		//Pidiendole datos al usuario
		system("cls");
		system("color 7");
		cout<<"\t\t\t\tIngrese la Clave del alumno: ";
		cin>>db.Clave;
		cout<<endl;
		
		
		//Haciendo una consulta a la base de datos donde me muestra todos los registros de mi tabla grado
		system("cls");
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
			
			//Pedirle el codigó grado al usuario
			cout<<endl<<endl;
			cout<<"\t\t\t\tIngrese el Codigo del grado: ";
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
					cout<<"\t\t\t\tIngrese el Codigo del grado: ";
					cin>>db.IdGrado;
					db.band=1;
				}
				
				else{
					db.band=0;
				}
			
			}while(db.band==1);
		}
		
		//Haciendo uno consulta a la base de datos donde donde me muestra todos los registros de mi tabla seccion
		system("cls");
		db.sql="SELECT * FROM seccion";
		query=db.sql.c_str();
		db.resultado=mysql_query(conexion, query);
		
		//Imprimiendo mi tabla seccion
		if (db.resultado==0){
			data=mysql_store_result(conexion);
			int countColumns=mysql_num_fields(data);
			int countRows=mysql_num_rows(data);
			cout<<"\t\t\t\tCodigo\tSeccion"<<endl;
			cout<<"\t\t\t\t------\t-------";
			cout<<endl<<endl;
			
			while(row=mysql_fetch_row(data)){
				cout<<"\t\t\t\t";
				for (int i=0; i<countColumns; i++){
					cout<<row[i]<<"\t";
				}
				
				cout<<endl;
			}
			
			//Pedirle el codigó seccion al usuario
			cout<<endl<<endl;
			cout<<"\t\t\t\tIngrese el Codigo de la seccion: ";
			cin>>db.IdSeccion;
			
			//Si el usuario ingresa un codigo incorrecto, se le vuelve a pedir que ingrese uno	
			do{		
				db.sql="SELECT * FROM seccion WHERE IdSeccion="+db.IdSeccion+"";
				query=db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				data=mysql_store_result(conexion);
				int countRows=mysql_num_rows(data);
				
				if(countRows==0){
					cout<<endl;
					cout<<"\t\t\t\tCodigo Invalido!\n";
					cout<<"\t\t\t\tEl codigo no existe en la tabla seccion\n";
					cout<<"\t\t\t\tIngrese el Codigo de la seccion: ";
					cin>>db.IdSeccion;
					db.band=1;
				}
				
				else{
					db.band=0;
				}
			
			}while(db.band==1);
		}
		
		//Realizando una consulta a la base de datos donde recaudo toda la informacion del alumno que se pretende eliminar	
		system("cls");
		db.text1="SELECT CONCAT('Clave:     ', A.Clave), CONCAT('Nombre:    ',A.Nombre), CONCAT('Apellido:  ', A.Apellido), CONCAT('Correo:    ', A.Correo), ";
		db.text2="CONCAT('Grado:     ', G.Grado), CONCAT('Seccion:   ', S.Seccion), CONCAT('Promedio:  ', N.Promedio) FROM alumno AS A ";
		db.text3="JOIN asignacion AS ASI ON A.IdAlumno=ASI.IdAlumno JOIN grado G ON ASI.IdGrado=G.IdGrado JOIN seccion S ON ASI.IdSeccion=S.IdSeccion ";
		db.text4="JOIN notas N ON A.IdAlumno=N.IdAlumno WHERE ASI.Clave="+db.Clave+" AND ASI.IdGrado="+db.IdGrado+" AND ASI.IdSeccion="+db.IdSeccion+"";
		db.sql=db.text1+db.text2+db.text3+db.text4;
		query = db.sql.c_str();
		db.resultado=mysql_query(conexion, query);
		
		//Imprimiendo el registro del alumno que se busca
		if (db.resultado==0){
			data=mysql_store_result(conexion);
			int countColumns=mysql_num_fields(data);
			int countRows=mysql_num_rows(data);
			cout<<endl<<endl;
			
			if(countRows>0){
				cout<<"\t\t\t\tAlumno Encontrado!\n\n";
				system("color a");
				
				while(row=mysql_fetch_row(data)){
					for (int i=0; i<countColumns; i++){
						cout<<"\t\t\t\t"<<row[i]<<"\n";
					}
					
					cout<<endl;
				}
				
			}
			
			//Muestro este mensaje si el registro a buscar no se encuentra
			else{
				system("cls");
				system("color c");
				cout<<"\t\t\t\tRegistro no encontrado";
			}
		}
		
		//Muestro en pantalla el error si la validacion de la condicional principal no se cumplio
		else{
			system("cls");
			system("color c");
			cout<<"\t\t\t\tNo se pudo generar la consulta\n\n";
			cout<<"\t\t\t\t"<<mysql_error(conexion); 
		}
		
		//Le indico al usuario que presione la opcion que desee realizar 
		cout<<endl<<endl;
		cout<<"\t\t\t\tPresione '1' para volver a buscar un alumno"<<endl;
		cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
		cout<<"\t\t\t\t"; cin>>db.opc;
		
		//Ciclo que se crea si el usuario ingreso una opcion incorrecta
		while(db.opc<1 || db.opc>2){
			system("cls");
			system("color c");
			cout<<"\t\t\t\tOpcion Invalida!\n";
			cout<<"\t\t\t\tVuelva a Ingresar una Opcion\n ";
			cout<<endl<<endl;
			cout<<"\t\t\t\tPresione '1' para volver a buscar un alumno"<<endl;
			cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
			cout<<"\t\t\t\t"; cin>>db.opc;
		}
		
	//Fin del bucle
	} while(db.opc==1);
}
