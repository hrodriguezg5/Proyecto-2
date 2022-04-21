using namespace std;

//Estructura donde declaro que tipo de datos tendran mis variables
struct DataBaseAlumno6{
	string Clave, Clave1, Nombre, Apellido, Correo, Grado, Seccion, sql;
	string IdGrado, IdNotas, IdClave, IdSeccion, IdAsignacion, IdAlumno;
	string Bimestre1, Bimestre2, Bimestre3, Bimestre4;
	string text1, text2, text3, text4;
    int resultado, opcion,opc, band, band2, gint, sint, a, b;
};

//Inicio mi funcion tipo void
void BorrarAlumGra(){
	
	struct DataBaseAlumno6 db;
	
	//Declarando mis funciones para mapear mis filas y columnas en la base de datos
	system("cls");
	MYSQL* conexion;
	MYSQL_ROW row;
	MYSQL_RES* data;
	
	//Conectandome a la base de datos
	conexion=mysql_init(0);
	conexion=mysql_real_connect(conexion, "localhost", "Admin", "Admin", "proyecto-2", 3306, NULL, 0);
	const char* query;
	
	//Iniciando el bucle para pedirle que ingrese un registro o salga de él
	do{
		//Pidiendole al usuario que ingrese una opcion
		system("cls");
		system("color 7");
		cout<<"\t\t\t\tQue registro desea Borrar!\n\n";
		cout<<"\t\t\t\t1. Borrar un Alumno"<<endl;
		cout<<"\t\t\t\t2. Borrar un Alumno sin grado"<<endl;
		cout<<"\t\t\t\t3. Borrar un Grado"<<endl;
		cout<<"\t\t\t\t4. Ninguno"<<endl<<endl;
		cout<<"\t\t\t\tIngrese una opcion: ";
		cin>>db.band;
		
		//Si la opcion es invalida, se le vuelve a pedir que ingrese una opcion
		while(db.band<=0||db.band>4)
		{
			cout<<"\n\t\t\t\tOpcion Invalida"<<endl;
			cout<<"\t\t\t\tIngrese una opcion: ";
			cin>>db.band;
		}
			
		//Condicional que si cumple si el usuario desea borrar al alumno
		if(db.band==1){
		
			//Pidiendole datos al usuario
			system("cls");
			system("color 7");
			cout<<"\t\t\t\tIngrese la Clave del alumno a eliminar: ";
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
			
			//Realizando una consulta a la base de datos donde recaudo toda la informacion del alumno que se pretende eliminar	
			system("cls");
			db.text1="SELECT CONCAT('Clave:     ', A.Clave), CONCAT('Nombre:    ',A.Nombre), CONCAT('Apellido:  ', A.Apellido), CONCAT('Correo:    ', A.Correo), ";
			db.text2="CONCAT('Grado:     ', G.Grado), CONCAT('Seccion:   ', S.Seccion), CONCAT('Promedio:  ', N.Promedio) FROM alumno AS A ";
			db.text3="JOIN asignacion AS ASI ON A.IdAlumno=ASI.IdAlumno JOIN grado G ON ASI.IdGrado=G.IdGrado JOIN seccion S ON ASI.IdSeccion=S.IdSeccion ";
			db.text4="JOIN notas N ON A.IdAlumno=N.IdAlumno WHERE ASI.Clave="+db.Clave+" AND ASI.IdGrado="+db.IdGrado+" AND ASI.IdSeccion="+db.IdSeccion+"";
			db.sql=db.text1+db.text2+db.text3+db.text4;
			query = db.sql.c_str();
			db.resultado=mysql_query(conexion, query);
			
			//Imprimiendo el registro del alumno a eliminar
			if (db.resultado==0){
				data=mysql_store_result(conexion);
				int countColumns=mysql_num_fields(data);
				int countRows=mysql_num_rows(data);
				cout<<endl<<endl;
				
				if(countRows>0){
					while(row=mysql_fetch_row(data)){
						for (int i=0; i<countColumns; i++){
							cout<<"\t\t\t\t"<<row[i]<<"\n";
						}
						
						cout<<endl;
					}
					
					//Preguntandole al usuario si desea eliminar el registro
					system("color c");
					cout<<endl;
					cout<<"\t\t\t\tEsta seguro de eliminar este registro?\n\n";
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
						cout<<"\t\t\t\tEsta seguro de eliminar este registro?\n\n";
						cout<<"\t\t\t\tPresione '1' para SI\n";
						cout<<"\t\t\t\tPresione '2' para NO\n\n ";
						cout<<"\t\t\t\t";
						cin>>db.band;
						cout<<endl;
					}
					
					/*Si el usuario desea eliminar el registro, se ejecutara el query a tres tablas en la base de datos
					  siendo primero la tabla   */
					if(db.band==1){
						db.sql="DELETE FROM asignacion WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"'  AND IdSeccion='"+db.IdSeccion+"'";
						query=db.sql.c_str();
						db.resultado=mysql_query(conexion, query);
						db.sql="DELETE FROM notas WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";	
						query=db.sql.c_str();
						db.resultado=mysql_query(conexion, query);
						db.sql="DELETE FROM alumno WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";	
						query=db.sql.c_str();
						db.resultado=mysql_query(conexion, query);
						system("cls");
						system("color a");
						cout<<"\t\t\t\tRegistro eliminado exitosamente";
					}
					
					//Muestro este mensaje en pantalla por si el usuario decide no eliminarlo
					else{
						system("cls");
						system("color c");
						cout<<"\t\t\t\tRegistro no eliminado";
					}
				}
				
				//Muestro este mensaje si el registro a eliminar no se encuentra
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
		}
		
		//Condicional que si cumple si el usuario desea borrar al alumno que no tiene un grado asignado
		else if(db.band==2){
	
			//Haciendo una consulta a la base de datos donde me muestra todos los registros de mi tabla grado
			system("cls");
			system("color 7");
			db.text1 = "SELECT CONCAT('ID: ', A.IdAlumno, ' '), CONCAT('Clave: ', A.Clave),CONCAT('Nombre: ',  A.Nombre), CONCAT('Apellido: ', A.Apellido) FROM alumno A ";
			db.text2 = "JOIN grado G ON A.IdGrado<>G.IdGrado";
			db.sql=db.text1+db.text2;
			query = db.sql.c_str();
			db.resultado=mysql_query(conexion, query);
			
			//Imprimiendo el resultado de mi consulta
			if (db.resultado==0){
				cout<<endl<<endl;
				data=mysql_store_result(conexion);
				int countColumns=mysql_num_fields(data);
				int countRows=mysql_num_rows(data);
				
				if(countRows>0){
				
					while(row=mysql_fetch_row(data)){
						cout<<"\t\t\t\t";
						for (int i=0; i<countColumns; i++){
							cout<<row[i]<<"\t";
						}
						
						cout<<endl;
					}
					
					//Pedirle el ID alumno al usuario
					cout<<endl<<endl;
					cout<<"\t\t\t\tIngrese el ID del alumno que desea eliminar: ";
					cin>>db.IdAlumno;
					
					//Si el usuario ingresa un codigo incorrecto, se le vuelve a pedir que ingrese uno	
					do{		
						db.sql = "SELECT * FROM alumno WHERE IdAlumno="+db.IdAlumno+"";
						query = db.sql.c_str();
						db.resultado=mysql_query(conexion, query);
						data=mysql_store_result(conexion);
						countRows=mysql_num_rows(data);
							
						if(countRows==0){
							cout<<endl;
							system("color c");
							cout<<"\t\t\t\tID Invalido!\n";
							cout<<"\t\t\t\tIngrese el ID del alumno que desea eliminar: ";
							cin>>db.IdAlumno;
							db.band=1;
						}
						
						else{
							db.band=0;
						}
						
					}while(db.band==1);	
					
					//Haciendo una consulta a la tabla alumno 
					db.sql = "SELECT * FROM alumno WHERE IdAlumno="+db.IdAlumno+"";
					query = db.sql.c_str();
					db.resultado=mysql_query(conexion, query);
					data=mysql_store_result(conexion);
					countRows=mysql_num_rows(data);
					
					//Condicional donde le pregunto al usuario si esta seguro de eliminar el registro
					if(countRows>0){	
						system("cls");
						system("color c");
						cout<<endl;
						cout<<"\t\t\t\tEsta seguro de eliminar este registro?\n\n";
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
							cout<<"\t\t\t\tEsta seguro de eliminar este registro?\n\n";
							cout<<"\t\t\t\tPresione '1' para SI\n";
							cout<<"\t\t\t\tPresione '2' para NO\n\n ";
							cout<<"\t\t\t\t";
							cin>>db.band;
							cout<<endl;
						}
				
						/*Si el usuario desea eliminar el registro, se ejecutara el query a tres tablas en la base de datos
						  siendo primero la tabla asignacion, notas y alumno  */
						if(db.band==1){
							db.sql="DELETE FROM asignacion WHERE IdAlumno="+db.IdAlumno+"";	
							query=db.sql.c_str();
							db.resultado=mysql_query(conexion, query);
							db.sql="DELETE FROM notas WHERE IdAlumno="+db.IdAlumno+"";	
							query=db.sql.c_str();
							db.resultado=mysql_query(conexion, query);
							db.sql="DELETE FROM alumno WHERE IdAlumno="+db.IdAlumno+"";	
							query=db.sql.c_str();
							db.resultado=mysql_query(conexion, query);
							system("cls");
							system("color a");
							cout<<"\t\t\t\tRegistro eliminado exitosamente";
						}
						
						//Condicional que se cumple si el usuario no desea eliminar el registro
						else{
							system("cls");
							system("color c");
							cout<<"\t\t\t\tRegistro no eliminado";
						}
					}			
			
				}
				
				//Condicional que se cumple si la consulta no muestra datos			
				else{
					system("cls");
					system("color c");
					cout<<"\t\t\t\tNo existen registros";	
				}
			}
		}
		
		//Condicional que si cumple si el usuario desea borrar un grado
		else if(db.band==3){
			
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
				cout<<"\t\t\t\tIngrese el Codigo del grado a eliminar: ";
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
						cout<<"\t\t\t\tIngrese el Codigo del grado a eliminar: ";
						cin>>db.IdGrado;
						db.band=1;
					}
					
					else{
						db.band=0;
					}
				
				}while(db.band==1);
			}
			
			//Haciendo una consulta a la base de datos donde me muestra el grado a eliminar
			system("cls");
			db.sql="SELECT * FROM grado WHERE IdGrado="+db.IdGrado+"";
			query = db.sql.c_str();
			db.resultado=mysql_query(conexion, query);
			
			if (db.resultado==0){
				data=mysql_store_result(conexion);
				int countColumns=mysql_num_fields(data);
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
			 
			 //Mensaje de advertencia donde le pido al usuario que valide lo que se le muestra en pantalla
			cout<<endl<<endl<<endl;
			system("color c");
			cout<<"\t\t\t\tADVERTENCIA!!!!\n\n";
			cout<<"\t\t\t\tAL MOMENTO DE ELIMINAR ESTE GRADO LOS DEMAS REGISTROS\n";
			cout<<"\t\t\t\tSE VERAN AFECTADOS, TENIENDO ALUMNOS SIN UN GRADO ASIGNADO\n";
			cout<<"\t\t\t\tDESEA CONTINUAR?\n\n";
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
				cout<<"\t\t\t\tEsta seguro de eliminar este registro?\n\n";
				cout<<"\t\t\t\tPresione '1' para SI\n";
				cout<<"\t\t\t\tPresione '2' para NO\n\n ";
				cout<<"\t\t\t\t";
				cin>>db.band;
				cout<<endl;
			}
			
			/*Si el usuario desea eliminar el registro, se ejecutara el query a tres tablas en la base de datos
			  siendo primero la tabla   */
			if(db.band==1){
				db.sql="DELETE FROM asignacion WHERE IdGrado="+db.IdGrado+"";
				query=db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				db.sql="DELETE FROM grado WHERE IdGrado="+db.IdGrado+"";
				query=db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				db.sql="UPDATE notas SET IdGrado=0 WHERE IdGrado="+db.IdGrado+"";
				query=db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				db.sql="UPDATE alumno SET IdGrado=0 WHERE IdGrado="+db.IdGrado+"";
				query=db.sql.c_str();
				db.resultado=mysql_query(conexion, query);
				system("cls");
				system("color a");
				cout<<"\t\t\t\tRegistro eliminado exitosamente";
			}
			
			//Si el usuario no desea eliminar el registro, se mostrara este mensaje
			else{
				system("cls");
				system("color c");
				cout<<"\t\t\t\tRegistro no eliminado";
			}
			
		}
		
		//COndicional que se cumple si no se elige ninguna de las opciones anteriores
		else{
				system("cls");
				system("color c");
				cout<<"\t\t\t\tDatos no borrados";
		}
			
		//Le indico al usuario que ingrese una opcion
		cout<<endl<<endl;
		cout<<"\t\t\t\tPresione '1' para volver a borrar un alumno o grado"<<endl;
		cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
		cout<<"\t\t\t\t"; cin>>db.opc;
		
		//Si la opcion es invalida, se le vuelve a pedir que ingrese una opcion
		while(db.opc<1 || db.opc>2){
			system("cls");
			system("color c");
			cout<<"\t\t\t\tOpcion Invalida!\n";
			cout<<"\t\t\t\tVuelva a Ingresar la Opcion\n ";
			cout<<endl<<endl;
			cout<<"\t\t\t\tPresione '1' para volver a borrar un alumno o grado"<<endl;
			cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
			cout<<"\t\t\t\t"; cin>>db.opc;
		}
	
	//Fin del bucle
	} while(db.opc==1);

}
