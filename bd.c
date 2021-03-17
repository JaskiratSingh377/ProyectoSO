// programa en C para introducir los datos en la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	char username [25]; 
	char consulta [80];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion, entrando nuestras claves de acceso y
	//el nombre de la base de datos a la que queremos acceder 
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "bd",0, NULL, 0);
	if (conn==NULL) 
	{
		printf ("Error al inicializar la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	
	
	
	
	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	printf("Aquí tienes una lista con los jugadores que actualmente hay en el sistema\n");
	err=mysql_query (conn, "SELECT * FROM Jugador");
	if (err!=0) 
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta. El resultado de la
	//consulta se devuelve en una variable del tipo puntero a
	//MYSQL_RES tal y como hemos declarado anteriormente.
	//Se trata de una tabla virtual en memoria que es la copia
	//de la tabla real en disco.
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial en memoria
	// en la que cada fila contiene los datos de una persona.
	
	// Ahora obtenemos la primera fila que se almacena en una
	// variable de tipo MYSQL_ROW
	row = mysql_fetch_row (resultado);
	// En una fila hay tantas columnas como datos tiene una
	// persona. En nuestro caso hay tres columnas: dni(row[0]),
	// nombre(row[1]) y edad (row[2]).
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while (row !=NULL) 
	{
			// la columna 2 contiene una palabra que es la edad
			// la convertimos a entero 
			// las columnas 0 y 1 contienen DNI y nombre 
			printf ("Username: %s\n", row[1]);
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
	}
	
	//Introduciremos en la base de datos 4 personas, 
	//cuyos datos pedimos al usuario
		printf("\n");
	printf ("Escribe el USERNAME del jugador que quieras eliminar de la base de datos\n");
	err = scanf ("%s", username);
	if (err!=1)
	{
		printf ("Error al introducir los datos \n");
		exit (1);
	}
	// Ahora construimos el string con el comando SQL
	// para insertar la persona en la base. Ese string es:
	// INSERT INTO personas VALUES ('dni', 'nombre', edad); 
		strcpy (consulta, "DELETE FROM Jugador WHERE Jugador.USERNAME='");
		//concatenamos el username 
		strcat (consulta, username); 
		strcat (consulta, "';");


		printf("consulta = %s\n", consulta);
		// Ahora ya podemos realizar la insercion 
		err = mysql_query(conn, consulta);
		if (err!=0)
		{
			printf ("Error al introducir datos la base %u %s\n", 
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		
		
		
		// consulta SQL para obtener una tabla con todos los datos
		// de la base de datos
		printf("\n");
		printf("Despues de dar baja al jugador deseado la BBDD queda de la siguiente forma:\n");
		err=mysql_query (conn, "SELECT * FROM Jugador");
		if (err!=0) 
		{
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta. El resultado de la
		//consulta se devuelve en una variable del tipo puntero a
		//MYSQL_RES tal y como hemos declarado anteriormente.
		//Se trata de una tabla virtual en memoria que es la copia
		//de la tabla real en disco.
		resultado = mysql_store_result (conn);
		// El resultado es una estructura matricial en memoria
		// en la que cada fila contiene los datos de una persona.
		
		// Ahora obtenemos la primera fila que se almacena en una
		// variable de tipo MYSQL_ROW
		row = mysql_fetch_row (resultado);
		// En una fila hay tantas columnas como datos tiene una
		// persona. En nuestro caso hay tres columnas: dni(row[0]),
		// nombre(row[1]) y edad (row[2]).
		if (row == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else
			while (row !=NULL) 
		{
				// la columna 2 contiene una palabra que es la edad
				// la convertimos a entero 
				// las columnas 0 y 1 contienen DNI y nombre 
				printf ("Username: %s\n", row[1]);
				// obtenemos la siguiente fila
				row = mysql_fetch_row (resultado);
		}
		
		// cerrar la conexion con el servidor MYSQL 
		mysql_close (conn);
		exit(0);
}
	


		

