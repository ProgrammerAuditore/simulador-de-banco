void fncBanco_Transferir(){
	
	CLEAN;
	printf("%s", TitulosBanco[6]);
	
	char NoTarjetaCuenta1[MAXCARACTERES];
	char NoTarjetaCuenta2[MAXCARACTERES];
	char _Descripcion[MAXCARACTERES];
	char _Asunto[MAXCARACTERES];
	int iTransferir = 0;
	
	printf("1) Introduzca el No. de tarjeta (remitente): \n");
	fgets(NoTarjetaCuenta1, MAXCARACTERES, stdin);
	strtok(NoTarjetaCuenta1,"\n");
	CHECKEO(NoTarjetaCuenta1);
	BUFFERFREE;
	
	printf("2) Introduzca el No. de tarjeta (a transferir): \n");
	fgets(NoTarjetaCuenta2, MAXCARACTERES, stdin);
	strtok(NoTarjetaCuenta2,"\n");
	CHECKEO(NoTarjetaCuenta2);
	BUFFERFREE;
	
	if( !fncBD_VerificarCuenta(NoTarjetaCuenta2) ){
		printf("Lo siento, la cuenta a transferir es inexistente. \n");
	}else if( !fncBD_VerificarCuenta(NoTarjetaCuenta1) ){
		printf("Lo siento, la cuenta remitente es inexistente. \n");
	}else if( fnc_CompararString(NoTarjetaCuenta1, NoTarjetaCuenta2) ){
		printf("*** Error cuenta duplicadas. \n");
	}else if( banco.EstadoDeCuenta == 0){
			printf("Lo siento, operacion rechazado. \n");
			printf("Cuenta bloqueda.\n");
	}else{

		fncBD_EstablecerConexionBD(false);
		fncBD_ObtenerDatosBanco();
		
		printf("3) Ingrese el monto a transferir: \n");
		scanf("%i", &iTransferir);
		BUFFERFREE;
		
		if( banco.EstadoDeCuenta == 0){
			printf("Lo siento, operacion rechazado. \n");
			printf("Cuenta bloqueda.\n");
		}else if(	(iTransferir < 0) || (iTransferir%100 != 0))
			printf("*** Error en el monto de transferencia. \n");
		else if ( (iTransferir > banco.Saldo) )
			printf("*** Fondo insuficientes \n");
		else{
			
			// Cuenta 1
			banco.Saldo -= iTransferir;
			fncBD_ActualizarDBBanco();
		
			// Registrar actividad
			actividades.TipoDeActividad = 301;
			sprintf(_Asunto, "Transferencia enviado: %s", NoTarjetaCuenta2);
			sprintf(_Descripcion, "Monto: (-) $%i", iTransferir);
			fncBD_RegistrarActividad("Banco: E&V", _Asunto, _Descripcion);
			
			// Cuenta 2			
			fncBD_VerificarCuenta(NoTarjetaCuenta2);
			fncBD_EstablecerConexionBD(false);
			fncBD_ObtenerDatosBanco();
			
			banco.Saldo += iTransferir;
			fncBD_ActualizarDBBanco();
			
			// Registrar actividad
			actividades.TipoDeActividad = 301;
			sprintf(_Asunto, "Transferencia recibido: %s", NoTarjetaCuenta1);
			sprintf(_Descripcion, "Monto: (+) $%i", iTransferir);
			fncBD_RegistrarActividad("Banco: E&V", _Asunto, _Descripcion);
		
			
			printf("------------[ OPERACION REALIZADA ]\n");
			
		}
	}
	
	fncBD_DeshacerConexionDB();
	BUFFERFREE;
	
}
