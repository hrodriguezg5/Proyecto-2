using namespace std;

//Estructura donde declaro que tipo de datos tendran mis variables
struct DataBaseAlumno3{
	string Clave, Clave1, Nombre, Apellido, Correo, Grado, Seccion, sql;
	string IdGrado, IdNotas, IdClave, IdSeccion, IdAsignacion, IdAlumno;
	string Bimestre1, Bimestre2, Bimestre3, Bimestre4;
	string text1, text2, text3, text4;
    int resultado, opcion,opc, band, band2, gint, sint, a, b;
    
};

//Inicio mi funcion tipo void
void AgregarNota(){
	
	struct DataBaseAlumno3 db;
	
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
		
		/*Haciendo uno consulta a la base de datos que me muestre si los datos ingresados anteriormente se encuentran en los campos
	      Clave, IdGrado, IdSeccion, de mi tabla notas*/
		system("cls");	
		db.sql="SELECT * FROM notas  WHERE Clave="+db.Clave+" AND IdGrado="+db.IdGrado+" AND IdSeccion="+db.IdSeccion+"";
		query=db.sql.c_str();
		db.resultado=mysql_query(conexion, query);
		
		//Haga la validacion de si la consulta anterior me trajo datos o no, y posteriormente les asigno los valores a mis variables
		if(db.resultado==0){
			data=mysql_store_result(conexion);
			int countRows=mysql_num_rows(data);
			
			if(countRows>0){
				db.a=1;
			}
			
			else{
				db.a=0;
			}	
		}
		
		/*Haciendo uno consulta a la base de datos que me muestre si los datos ingresados anteriormente se encuentran en los campos
	      Clave, IdGrado, IdSeccion, y validando que mi campo promedio tenga datos de mi tabla notas*/
		db.sql="SELECT * FROM notas  WHERE Clave="+db.Clave+" AND IdGrado="+db.IdGrado+" AND IdSeccion="+db.IdSeccion+" AND Promedio>0";
		query=db.sql.c_str();
		db.resultado=mysql_query(conexion, query);
		
		//Haga la validacion de si la consulta anterior me trajo datos o no, y posteriormente les asigno los valores a mis variables
		if(db.resultado==0){
			data=mysql_store_result(conexion);
			int countRows=mysql_num_rows(data);
			
			if(countRows>0){
				db.b=1;
			}
			
			else{
				db.b=0;
			}		
		}
		
		/*Segun el resultado de mis 2 consultas actuales, realizo multiples condicionales
		  Esta condicional pide que el registro a ingresar la nota sea la primera vez*/
		if (db.a==1 &&db.b==0){
			cout<<"\t\t\t\tIngrese la nota del Bimestre 1: ";
			cin>>db.Bimestre1;
			cout<<"\t\t\t\tIngrese la nota del Bimestre 2: ";
			cin>>db.Bimestre2;
			cout<<"\t\t\t\tIngrese la nota del Bimestre 3: ";
			cin>>db.Bimestre3;
			cout<<"\t\t\t\tIngrese la nota del Bimestre 4: ";
			cin>>db.Bimestre4;
			cout<<endl;
			
			//Hago una actualizacion a los campos de bimestre y promedio que se encontraban en 0 en mi tabla notas
			db.text1="UPDATE notas SET Bimestre1="+db.Bimestre1+" , Bimestre2="+db.Bimestre2+" , Bimestre3="+db.Bimestre3+", Bimestre4="+db.Bimestre4+", ";
			db.text2="Promedio=(("+db.Bimestre1+"+"+db.Bimestre2+"+"+db.Bimestre3+"+"+db.Bimestre4+")/4) ";
			db.text3="WHERE Clave="+db.Clave+" AND IdGrado="+db.IdGrado+" AND IdSeccion="+db.IdSeccion+"";
			db.sql=db.text1+db.text2+db.text3;
			query=db.sql.c_str();
			db.resultado=mysql_query(conexion, query);
			
			system("cls");
			system("color a");
			cout<<"\t\t\t\tRegistro guardado exitosamente";
		}
		
		/*Esta condicional le informa al usuario que el registro ingresado ya contenia datos
		y si desea modificar el registro*/
		else if(db.b==1){
			system("color c");
			cout<<"\t\t\t\tLos datos ingresados ya se encuentran registrados\n";
			cout<<"\t\t\t\tDesea modificarlos?\n\n";
			cout<<"\t\t\t\tPresione '1' para SI\n";
			cout<<"\t\t\t\tPresione '2' para NO\n\n ";
			cout<<"\t\t\t\t";
			cin>>db.band;
			cout<<endl;
			
			//Si la opcion es invalida, se le vuelve a pedir que ingrese una opcion
			while(db.band<1 || db.band>2){
				system("cls");
				system("color c");
				cout<<"\t\t\t\tOpcion Invalida!\n";
				cout<<"\t\t\t\tVuelva a Ingresar una Opcion\n ";
				cout<<endl<<endl;
				cout<<"\t\t\t\tLos datos ingresados ya se encuentran registrados\n";
				cout<<"\t\t\t\tDesea modificarlos?\n\n";
				cout<<"\t\t\t\tPresione '1' para SI\n";
				cout<<"\t\t\t\tPresione '2' para NO\n\n ";
				cout<<"\t\t\t\t";
				cin>>db.band;
				cout<<endl;
			}
			
			//Pidiendole datos al usuario de los campos que se actualizaran posteriormente
			if(db.band==1){
				system("cls");
				system("color 7");
				cout<<"\t\t\t\tIngrese la nota del Bimestre 1: ";
				cin>>db.Bimestre1;
				cout<<"\t\t\t\tIngrese la nota del Bimestre 2: ";
				cin>>db.Bimestre2;
				cout<<"\t\t\t\tIngrese la nota del Bimestre 3: ";
				cin>>db.Bimestre3;
				cout<<"\t\t\t\tIngrese la nota del Bimestre 4: ";
				cin>>db.Bimestre4;
				cout<<endl;
				
				//Hago una actualizacion a los campos de bimestre y promedio que se encontraban con datos en mi tabla columna
				db.text1="UPDATE notas SET Bimestre1="+db.Bimestre1+" , Bimestre2="+db.Bimestre2+" , Bimestre3="+db.Bimestre3+", Bimestre4="+db.Bimestre4+", ";
				db.text2="Promedio=(("+db.Bimestre1+"+"+db.Bimestre2+"+"+db.Bimestre3+"+"+db.Bimestre4+")/4) ";
				db.text3="WHERE Clave="+db.Clave+" AND IdGrado="+db.IdGrado+" AND IdSeccion="+db.IdSeccion+"";
				db.sql=db.text1+db.text2+db.text3;
				query=db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				cout<<endl<<db.resultado;
				
				system("cls");
				system("color a");
				cout<<"\t\t\t\tRegistro guardado exitosamente";
			}
			
			//Muestro un mensaje donde el usuario decidio no modificar el registro
			else{
					system("cls");
					system("color c");
					cout<<"\t\t\t\tRegistro no modificado";
				
			}
		}
		
		//Mensaje donde informa al usuario que el registro ingresado no se encontro
		else{
			system("cls");
			system("color c");
			cout<<"\t\t\t\tAlumno no encontrado";
		}
		
		//Le indico al usuario que presione la opcion que desee realizar 
		cout<<endl<<endl;
		cout<<"\t\t\t\tPresione '1' para volver a agregar una nota del alumno"<<endl;
		cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
		cout<<"\t\t\t\t"; cin>>db.opc;
		
		//Ciclo que se crea si el usuario ingreso una opcion incorrecta
		while(db.opc<1 || db.opc>2){
			system("cls");
			system("color c");
			cout<<"\t\t\t\tOpcion Invalida!\n";
			cout<<"\t\t\t\tVuelva a Ingresar la Opcion\n ";
			cout<<endl<<endl;
			cout<<"\t\t\t\tPresione '1' para volver a agregar una nota del alumno"<<endl;
			cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
			cout<<"\t\t\t\t"; cin>>db.opc;
		}
		
	//Fin del bucle
	} while(db.opc==1);	
}
