using namespace std;

//Estructura donde declaro que tipo de datos tendran mis variables
struct DataBaseAlumno1{
	string Clave, Clave1, Nombre, Apellido, Correo, Grado, Seccion, sql;
	string IdGrado, IdNotas, IdClave, IdSeccion, IdAsignacion, IdAlumno;
	string Bimestre1, Bimestre2, Bimestre3, Bimestre4;
	string text1, text2, text3, text4;
    int resultado, opcion,opc, band, band2, gint, sint, a, b;
};

//Inicio mi funcion tipo void
void AgregarAlumno(){
	
	struct DataBaseAlumno1 db;
	
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
		//Pidiendole datos al usuario
		system("cls");
		system("color 7");
		cout<<"\t\t\t\tIngrese la Clave del alumno: ";
		cin>>db.Clave;
		cout<<"\t\t\t\tIngrese Nombre del alumno: ";
		cin>>db.Nombre;
		cout<<"\t\t\t\tIngrese Apellido del alumno: ";
		cin>>db.Apellido;
		cout<<"\t\t\t\tIngrese Correo del alumno: ";
		cin>>db.Correo;
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
			
			//Pedirle el codigó grado al alumno
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
		
		/*Haciendo uno consulta a la base de datos que me muestre si los datos ingresados anteriormente se encuentran en los campos
	      Clave, IdGrado, IdSeccion, de mi tabla asignacion*/
		system("cls");	
		db.sql="SELECT * FROM asignacion WHERE Clave='"+db.Clave+"' AND  IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'" ;
		query=db.sql.c_str();
		db.resultado=mysql_query(conexion, query);
		
		//Realizo una condicional donde valido si la consulta se realizó correctamente
		if(db.resultado==0){
			data=mysql_store_result(conexion);
			int countColumns=mysql_num_fields(data);
			int countRows=mysql_num_rows(data);
			
			//Realizo una condicional donde valido si el query anterior me trajo datos para que estos no se guarden
			if(countRows>0){
				cout<<"\t\t\t\tError al ingresar alumno\n\n";
				cout<<"\t\t\t\tLa clave '"+db.Clave+"' del alumno '"+db.Nombre+"' ya se encuentra registrada\n\t\t\t\ten el grado  y seccion ingresados\n\n";
				system("color c");
				cout<<"\t\t\t\tRegistro no guardado\n\n";
			}
			
			/*Si el query anterior no me trajo datos, realizo 3 querys donde inserto la informacion ingresada por el usuario, cada query ingresa datos
			 a una tabla distinta para posteriormente poder utilizar estos datos en los demas requerimientos del programa*/
			else{
				db.text1="INSERT INTO alumno(Clave, Nombre, Apellido, Correo, IdGrado, IdSeccion) ";
				db.text2="VALUES ('"+db.Clave+"', '"+db.Nombre+"', '"+db.Apellido+"', '"+db.Correo+"', '"+db.IdGrado+"', '"+db.IdSeccion+"')";
				db.sql=db.text1+db.text2;
				query=db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				db.text1="INSERT INTO asignacion(IdAlumno, Clave, IdGrado, IdSeccion) SELECT IdAlumno, Clave, IdGrado, IdSeccion FROM alumno ";
				db.text2="WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
				db.sql=db.text1+db.text2;
				query=db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				db.text1="INSERT INTO notas(IdAlumno, Clave, IdGrado, IdSeccion) SELECT IdAlumno, Clave, IdGrado, IdSeccion FROM alumno ";
				db.text2="WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
				db.sql=db.text1+db.text2;
				query=db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				system("color a");
				cout<<"\t\t\t\tRegistro guardado exitosamente";
			}
		}
		
		//Muestro en pantalla el error si la validacion de la condicional principal no se cumplio
		else{
			system("color c");
			cout<<"\t\t\t\tRegistro no guardado";
			cout<<"\t\t\t\t"<<mysql_error(conexion); 
		}
		
		//Le indico al usuario que presione la opcion que desee realizar 
		cout<<endl<<endl;
		cout<<"\t\t\t\tPresione '1' para volver a agregar un alumno"<<endl;
		cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
		cout<<"\t\t\t\t"; cin>>db.opc;
		
		//Ciclo que se crea si el usuario ingreso una opcion incorrecta
		while(db.opc<1 || db.opc>2){
			system("cls");
			system("color c");
			cout<<"\t\t\t\tOpcion Invalida!\n";
			cout<<"\t\t\t\tVuelva a Ingresar una Opcion\n ";
			cout<<endl<<endl;
			cout<<"\t\t\t\tPresione '1' para volver a agregar un alumno"<<endl;
			cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
			cout<<"\t\t\t\t"; cin>>db.opc;
		}
		
	//Fin del bucle
	} while(db.opc==1);	
}
