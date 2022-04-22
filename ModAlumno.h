using namespace std;

//Estructura donde declaro que tipo de datos tendran mis variables
struct DataBaseAlumno7{
	string Clave, Clave1, Nombre, Apellido, Correo, Grado, Seccion, sql;
	string IdGrado, IdNotas, IdClave, IdSeccion, IdAsignacion, IdAlumno;
	string Bimestre1, Bimestre2, Bimestre3, Bimestre4;
	string text1, text2, text3, text4;
    int resultado, opcion,opc, band, band2, gint, sint, a, b;
};

//Inicio mi funcion tipo void
void ModAlumno(){
	struct DataBaseAlumno7 db;
	
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
		
		//Pidiendole la clave al usuario
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
		
		//Realizando una consulta a la base de datos donde recaudo toda la informacion del alumno al que se le modificaran los datos	
		system("cls");
		db.text1="SELECT CONCAT('Clave:     ', A.Clave), CONCAT('Nombre:    ',A.Nombre), CONCAT('Apellido:  ', A.Apellido), CONCAT('Correo:    ', A.Correo), ";
		db.text2="CONCAT('Grado:     ', G.Grado), CONCAT('Seccion:   ', S.Seccion), CONCAT('Promedio:  ', N.Promedio) FROM alumno AS A ";
		db.text3="JOIN asignacion AS ASI ON A.IdAlumno=ASI.IdAlumno JOIN grado G ON ASI.IdGrado=G.IdGrado JOIN seccion S ON ASI.IdSeccion=S.IdSeccion ";
		db.text4="JOIN notas N ON A.IdAlumno=N.IdAlumno WHERE ASI.Clave="+db.Clave+" AND ASI.IdGrado="+db.IdGrado+" AND ASI.IdSeccion="+db.IdSeccion+"";
		db.sql=db.text1+db.text2+db.text3+db.text4;
		query = db.sql.c_str();
		db.resultado=mysql_query(conexion, query);
			
		//Imprimiendo el registro del alumno a modificar
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
				
				//Mostrando un menu con el dato que se quiere modificar del alumno  
				if(db.band==1){
					system("cls");
					system("color 7");
					cout<<"\t\t\t\tQue dato desea Modificar!\n\n";
					cout<<"\t\t\t\t1. Clave\n";
					cout<<"\t\t\t\t2. Nombre\n";
					cout<<"\t\t\t\t3. Apellido\n";
					cout<<"\t\t\t\t4. Correo\n";
					cout<<"\t\t\t\t5. Grado\n";
					cout<<"\t\t\t\t6. Seccion\n";
					cout<<"\t\t\t\t7. Promedio\n";
					cout<<"\t\t\t\t8. Ninguno\n\n";
					cout<<"\t\t\t\tIngrese una opcion: ";
					cin>>db.opcion;
					
					//Si la opcion es invalida, se le vuelve a pedir que ingrese una opcion
					while(db.opcion<=0||db.opcion>8)
					{
						system("color c");
						cout<<"\n\t\t\t\tOpcion Invalida"<<endl;
						cout<<"\t\t\t\tIngrese una opcion:  ";
						cin>>db.opcion;
					}
					
					//Realizando un switch donde se muestra la opcion que el usuario alla seleccionado			
					switch(db.opcion){
						case 1:
							
							//Pidiendole la clave al usuario
							system("cls");
							cout<<"\t\t\t\tIngrese la nueva Clave del alumno: ";
							cin>>db.Clave1;
								
							//Realizo un query donde introduzco los datos que el usuario ingreso	
							system("cls");	
							db.sql="SELECT * FROM alumno WHERE Clave='"+db.Clave1+"' AND  IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'" ;
							query=db.sql.c_str();
							db.resultado=mysql_query(conexion, query);
							
							//Realizo una condicional donde valido si la consulta se realizó correctamente
							if(db.resultado==0){
								data=mysql_store_result(conexion);
								int countColumns=mysql_num_fields(data);
								int countRows=mysql_num_rows(data);
								
								//Muestro un mensaje donde le indico al usuario que ha ingresado la misma clave que quiere modificar
								if(db.Clave==db.Clave1){
									cout<<"\t\t\t\tError al modificar la clave\n";
									cout<<"\t\t\t\tEsta ingresando la misma clave de la consulta\n\n";
									system("color c");
									cout<<"\t\t\t\tRegistro no modificado\n\n";
								}
								
								/*Muestro un mensaje donde le indico al usuario que ha ingresado una clave igual a la de un 
							   	  alumno de un mismo grado y seccion */
								else if(countRows>0){
									cout<<"\t\t\t\tError al modificar la clave\n\n";
									cout<<"\t\t\t\tLa clave '"+db.Clave1+"' ya se encuentra asignada a un alumno\n\t\t\t\tdel mismo grado y seccion\n\n";
									system("color c");
									cout<<"\t\t\t\tRegistro no modificado\n\n";
								}
								
								/*Si los datos ingresados anteriormente no se encuentran repetidos en la base de datos, se realizara una actualizacion a la 
							   	  columna Clave de las tablas asignacion, notas y alumno*/
								else{
									db.sql="UPDATE asignacion SET Clave = '"+db.Clave1+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
									query=db.sql.c_str();
									db.resultado=mysql_query(conexion, query);
									db.sql="UPDATE notas SET Clave = '"+db.Clave1+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
									query=db.sql.c_str();
									db.resultado=mysql_query(conexion, query);
									db.sql="UPDATE alumno SET Clave = '"+db.Clave1+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
									query=db.sql.c_str();
									db.resultado=mysql_query(conexion, query);
									system("color a");
									cout<<"\t\t\t\tRegistro guardado exitosamente";
								}
							}
							break;
							
						case 2:
							
							//Pidiendole un nombre al usuario
							system("cls");
							cout<<"\t\t\t\tIngrese el nuevo Nombre del alumno: ";
							cin>>db.Nombre;
							
							//Realizo una actualizacion a la tabla alumno donde se le ingresa el nombre que el usuario decidio
							system("cls");
							db.sql="UPDATE alumno SET Nombre = '"+db.Nombre+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
							query=db.sql.c_str();
							db.resultado=mysql_query(conexion, query);
							system("color a");
							cout<<"\t\t\t\tRegistro guardado exitosamente";
							break;
							
						case 3:
							
							//Pidiendole un apellido al usuario
							system("cls");
							cout<<"\t\t\t\tIngrese el nuevo Apellido del alumno: ";
							cin>>db.Apellido;
							
							//Realizo una actualizacion a la tabla alumno donde se le ingresa el apellido que el usuario decidio
							system("cls");
							db.sql="UPDATE alumno SET Apellido = '"+db.Apellido+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
							query=db.sql.c_str();
							db.resultado=mysql_query(conexion, query);
							system("color a");
							cout<<"\t\t\t\tRegistro guardado exitosamente";
							break;
							
						case 4:
							
							//Pidiendole un correo al usuario
							system("cls");
							cout<<"\t\t\t\tIngrese el nuevo Correo del alumno: ";
							cin>>db.Correo;	
							
							//Realizo una actualizacion a la tabla alumno donde se le ingresa el correo que el usuario decidio
							system("cls");
							db.sql="UPDATE alumno SET Correo = '"+db.Correo+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
							query=db.sql.c_str();
							db.resultado=mysql_query(conexion, query);
							system("color a");
							cout<<"\t\t\t\tRegistro guardado exitosamente";
							break;
							
						case 5:	
								
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
								cout<<"\t\t\t\tIngrese el nuevo Codigo del grado: ";
								cin>>db.Grado;
								
								//Si el usuario ingresa un codigo incorrecto, se le vuelve a pedir que ingrese uno
								do{		
									db.sql = "SELECT * FROM grado WHERE IdGrado="+db.Grado+"";
									query = db.sql.c_str();
									db.resultado=mysql_query(conexion, query);
									data=mysql_store_result(conexion);
									countRows=mysql_num_rows(data);
									
									if(countRows==0){
										cout<<endl;
										cout<<"\t\t\t\tCodigo Invalido!\n";
										cout<<"\t\t\t\tEl codigo no existe en la tabla grado\n";
										cout<<"\t\t\t\tIngrese el nuevo Codigo del grado: ";
										cin>>db.Grado;
										db.band=1;
									}
									
									else{
										db.band=0;
									}
								
								}while(db.band==1);
								
								//Realizo un query donde introduzco los datos que el usuario ingreso	
								system("cls");	
								db.sql="SELECT * FROM alumno WHERE Clave='"+db.Clave+"' AND  IdGrado='"+db.Grado+"' AND IdSeccion='"+db.IdSeccion+"'" ;
								query=db.sql.c_str();
								db.resultado=mysql_query(conexion, query);
								
								//Realizo una condicional donde valido si la consulta se realizó correctamente
								if(db.resultado==0){
									data=mysql_store_result(conexion);
									int countColumns=mysql_num_fields(data);
									int countRows=mysql_num_rows(data);
									
									//Muestro un mensaje donde le indico al usuario que ha ingresado el mismo grado que quiere modificar
									if(db.IdGrado==db.Grado){
										cout<<"\t\t\t\tError al modificar el grado\n";
										cout<<"\t\t\t\tEsta ingresando el mismo grado de la consulta\n\n";
										system("color c");
										cout<<"\t\t\t\tRegistro no modificado\n\n";
									}
									
									
									/*Muestro un mensaje donde le indico al usuario que ha ingresado un grado igual a la de un 
							   		  alumno con la misma clave y seccion */
									else if(countRows>0){
										cout<<"\t\t\t\tError al modificar el grado\n\n";
										cout<<"\t\t\t\tEl codigo del grado '"+db.Grado+"' ya se encuentra asignada a un alumno\n\t\t\t\tcon la misma clave y seccion\n\n";
										system("color c");
										cout<<"\t\t\t\tRegistro no modificado\n\n";
									}
									
									/*Si los datos ingresados anteriormente no se encuentran repetidos en la base de datos, se realizara una actualizacion a la 
							   		  columna IdGrado de las tablas asignacion, notas y alumno*/
									else{
										db.sql="UPDATE asignacion SET IdGrado = '"+db.Grado+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
										query=db.sql.c_str();
										db.resultado=mysql_query(conexion, query);
										db.sql="UPDATE notas SET IdGrado = '"+db.Grado+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
										query=db.sql.c_str();
										db.resultado=mysql_query(conexion, query);
										db.sql="UPDATE alumno SET IdGrado = '"+db.Grado+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
										query=db.sql.c_str();
										db.resultado=mysql_query(conexion, query);
										system("color a");
										cout<<"\t\t\t\tRegistro guardado exitosamente";
									}
								}	
							}
							break;
							
						case 6:
							
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
								cout<<"\t\t\t\tIngrese el nuevo Codigo de la seccion: ";
								cin>>db.Seccion;
								
								//Si el usuario ingresa un codigo incorrecto, se le vuelve a pedir que ingrese uno
								do{		
									db.sql="SELECT * FROM seccion WHERE IdSeccion="+db.Seccion+"";
									query=db.sql.c_str();
									db.resultado=mysql_query(conexion, query);
									data=mysql_store_result(conexion);
									int countRows=mysql_num_rows(data);
									
									if(countRows==0){
										cout<<endl;
										cout<<"\t\t\t\tCodigo Invalido!\n";
										cout<<"\t\t\t\tEl codigo no existe en la tabla seccion\n";
										cout<<"\t\t\t\tIngrese el Codigo de la seccion: ";
										cin>>db.Seccion;
										db.band=1;
									}
									
									else{
										db.band=0;
									}
								
								}while(db.band==1);
								
								
								//Realizo un query donde introduzco los datos que el usuario ingreso
								system("cls");	
								db.sql="SELECT * FROM alumno WHERE Clave='"+db.Clave+"' AND  IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.Seccion+"'" ;
								query=db.sql.c_str();
								db.resultado=mysql_query(conexion, query);
								
								//Realizo una condicional donde valido si la consulta se realizó correctamente
								if(db.resultado==0){
									data=mysql_store_result(conexion);
									int countColumns=mysql_num_fields(data);
									int countRows=mysql_num_rows(data);
								
									//Muestro un mensaje donde le indico al usuario que ha ingresado la misma seccion que quiere modificar
									if(db.IdSeccion==db.Seccion){
										cout<<"\t\t\t\tError al modificar la seccion\n";
										cout<<"\t\t\t\tEsta ingresando la misma seccion de la consulta\n\n";
										system("color c");
										cout<<"\t\t\t\tRegistro no modificado\n\n";
									}
									
									/*Muestro un mensaje donde le indico al usuario que ha ingresado una seccion igual a la de un 
							   		  alumno con el mismo grado y seccion */
									else if(countRows>0){
										cout<<"\t\t\t\tError al modificar la seccion\n\n";
										cout<<"\t\t\t\tEl codigo de la seccion '"+db.Seccion+"' ya se encuentra asignada a un alumno\n\t\t\t\tcon la misma clave y grado\n\n";
										system("color c");
										cout<<"\t\t\t\tRegistro no modificado\n\n";
									}
									
									/*Si los datos ingresados anteriormente no se encuentran repetidos en la base de datos, se realizara una actualizacion a la 
							   		  columna IdSeccion de las tablas asignacion, notas y alumno*/
									else{
										db.sql="UPDATE asignacion SET IdSeccion = '"+db.Seccion+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
										query=db.sql.c_str();
										db.resultado=mysql_query(conexion, query);
										db.sql="UPDATE notas SET IdSeccion = '"+db.Seccion+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
										query=db.sql.c_str();
										db.resultado=mysql_query(conexion, query);
										db.sql="UPDATE alumno SET IdSeccion = '"+db.Seccion+"'WHERE Clave='"+db.Clave+"' AND IdGrado='"+db.IdGrado+"' AND IdSeccion='"+db.IdSeccion+"'";
										query=db.sql.c_str();
										db.resultado=mysql_query(conexion, query);
										system("color a");
										cout<<"\t\t\t\tRegistro guardado exitosamente";
									}
								}	
							}
							break;
							
						case 7:
							
							//Realizo un query donde introduzco los datos que el usuario ingreso en mi tabla notas
							system("cls");
							db.sql="SELECT * FROM notas  WHERE Clave="+db.Clave+" AND IdGrado="+db.IdGrado+" AND IdSeccion="+db.IdSeccion+"";
							query=db.sql.c_str();
							db.resultado=mysql_query(conexion, query);
							
							//Realizo una condicional donde valido si la consulta se realizó correctamente
							if(db.resultado==0){
								data=mysql_store_result(conexion);
								int countColumns=mysql_num_fields(data);
								int countRows=mysql_num_rows(data);
								
								//Si la consulta anterior me trajo datos, le pido datos al usario
								if(countRows>0){
									
									cout<<"\t\t\t\tIngrese la nota del Bimestre 1: ";
									cin>>db.Bimestre1;
									cout<<"\t\t\t\tIngrese la nota del Bimestre 2: ";
									cin>>db.Bimestre2;
									cout<<"\t\t\t\tIngrese la nota del Bimestre 3: ";
									cin>>db.Bimestre3;
									cout<<"\t\t\t\tIngrese la nota del Bimestre 4: ";
									cin>>db.Bimestre4;
									cout<<endl;
									
									//Hago una actualizacion a los campos de bimestre y promedio que se encontraban con datos en mi tabla notas
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
								
								//Condicional que muestra un mensaje si no se encontro datos en mi tabla notas
								else{
									system("color c");
									cout<<"\t\t\t\tNo se encontro ningun promedio a modificar\n\n";
									cout<<"\t\t\t\t"<<mysql_error(conexion); 
								}
							}
							
							//Muestro en pantalla el error si mi consulta de la opcion promedio no se cumplio
							else{
								system("color c");
								cout<<"\t\t\t\tNo se pudo generar la consulta\n\n";
								cout<<"\t\t\t\t"<<mysql_error(conexion); 
							}
							break;
						
						//Le doy la opcion al usuario de que no realiza ninguna modificacion
						case 8:
							system("cls");
							system("color c");
							cout<<"\t\t\t\tRegistro no modificado";
							break;		
					}
				}
					
				//Muestro un mensaje donde el usuario decidio no modificar el registro
				else{
					system("cls");
					system("color c");
					cout<<"\t\t\t\tRegistro no modificado";
				
				}
			}
			
			//Muestro este mensaje si el registro a buscar no se encuentro
			else{
				system("cls");
				system("color c");
				cout<<"\t\t\t\tRegistro no encontrado";
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
		cout<<"\t\t\t\tPresione '1' para volver a modificar un alumno"<<endl;
		cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
		cout<<"\t\t\t\t"; cin>>db.opc;
		
		//Ciclo que se crea si el usuario ingreso una opcion incorrecta
		while(db.opc<1 || db.opc>2){
			system("cls");
			system("color c");
			cout<<"\t\t\t\tOpcion Invalida!\n";
			cout<<"\t\t\t\tVuelva a Ingresar una Opcion\n ";
			cout<<endl<<endl;
			cout<<"\t\t\t\tPresione '1' para volver a modificar un alumno"<<endl;
			cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
			cout<<"\t\t\t\t"; cin>>db.opc;
		}	
		
	//Fin del bucle
	}while(db.opc==1);	
} 

