// Archivos de cabecera  << ./src >>
#include "Run.h"
// Archivos de cabecera  << ./BD >>
#include "./fncBD/fncBD__Run.h"
// Archivos de cabecera << ./Banco >>
#include "./fncBanco/fncBanco__Run.h"

// Compilar
// gcc -c Banco.c -I"./src" -std=c99 && gcc -o Banco Banco.o
// Compatible con Windows y Linux-Mint

int main(){

/*
if(fncBD_VerificarCuenta("1998-VMA-103")){
	fncBD_EstablecerConexionBD(false);
	fncBD_ObtenerDatosBanco();
	BUFFERFREE;

	// Eliminamos la cuenta
	fncBD_ActualizarUsuariosBD();

	BUFFERFREE;

	// Agregar usuario
	fncBD_RegistrarUsuarioDB();
	BUFFERFREE;

}
*/
 
	CLEAN;
	char Opcion;

	do{
		CLEAN;
		fncBanco_MensajesMenu();
		Opcion = '\0';
		printf("Selecciona una opcion: ");
		Opcion = getchar();
		BUFFERFREE;
		
		if( Opcion != '\n'){
			switch (Opcion){
				case '0': break; break;
				case '1': fncBanco_CrearCuenta(); break;
				case '2': fncBanco_Depositar(); break;
				case '3': fncBanco_Retirar(); break;
				case '4': fncBanco_Transferir(); break;
				case '5': fncBanco_ConfigurarCuenta(); break;
				case '6': fncBanco_OpcionesDeCuenta(); break;
				default: OPTIONERROR;
			}
		}
		
	}while(Opcion != '0');

	printf("THE END ");
	BUFFERFREE;

return 0;	
}