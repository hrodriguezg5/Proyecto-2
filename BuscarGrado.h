using namespace std;

//Estructura donde declaro que tipo de datos tendran mis variables
struct DataBaseAlumno5{
	string Clave, Clave1, Nombre, Apellido, Correo, Grado, Seccion, sql;
	string IdGrado, IdNotas, IdClave, IdSeccion, IdAsignacion, IdAlumno;
	string Bimestre1, Bimestre2, Bimestre3, Bimestre4;
	string text1, text2, text3, text4;
    int resultado, opcion,opc, band, band2, gint, sint, a, b;
};

//Inicio mi funcion tipo void
void BuscarGrado(){
	
	struct DataBaseAlumno5 db;
	
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
		cout<<"\t\t\t\tIngrese el Codigo del grado a buscar: ";
		cin>>db.IdGrado;
		
		//Haciendo la consulta de busqueda del grado
		system("cls");
		db.sql="SELECT * FROM grado WHERE IdGrado='"+db.IdGrado+"'" ;
		query=db.sql.c_str();
		db.resultado=mysql_query(conexion, query);
		
		//Imprimiendo los resultados de mi busqueda
		if(db.resultado==0){
			system("color a");
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
			
			//Coloco una condicional en tal caso de que mi busqueda no tenga ningun resultado
			if(countRows<1){
				system("color c");
				cout<<"\t\t\t\tNo existe el registro ingresado";
			}
		}
		
		//Muestro en pantalla si no se pudo generar mi consulta
		else{
			system("cls");
			system("color c");
			cout<<"\t\t\t\tNo se pudo generar la consulta";
			cout<<"\t\t\t\t"<<mysql_error(conexion);
		}
		
		//Le indico al usuario que presione la opcion que desee realizar 
		cout<<endl<<endl;
		cout<<"\t\t\t\tPresione '1' para volver a buscar un grado"<<endl;
		cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
		cout<<"\t\t\t\t"; cin>>db.opc;
		
		//Ciclo que se crea si el usuario ingreso una opcion incorrecta
		while(db.opc<1 || db.opc>2){
			system("cls");
			system("color c");
			cout<<"\t\t\t\tOpcion Invalida!\n";
			cout<<"\t\t\t\tVuelva a Ingresar una Opcion\n ";
			cout<<endl<<endl;
			cout<<"\t\t\t\tPresione '1' para volver a buscar un grado"<<endl;
			cout<<"\t\t\t\tPresione '2' para volver al menu"<<endl<<endl;
			cout<<"\t\t\t\t"; cin>>db.opc;
		}
		
	//Fin del bucle
	} while(db.opc==1);
}
