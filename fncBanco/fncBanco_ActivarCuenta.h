void fncBanco_ActivarCuenta(){
        
    CLEAN;
	printf("%s", TitulosBanco[8]);
	String NoTarjeta;
	int PIN[2] = {0,0};

	printf("1) Introduzca el No. de tarjeta: \n");
	fgets(NoTarjeta, MAXCARACTERES, stdin);
	CHECKEO_INPUT(NoTarjeta);
	BUFFERFREE;
	
	if(fncBD_VerificarCuenta(NoTarjeta)){
		// Obtener el path de cada base de datos 
		fncBD_EstablecerConexionBD(false);
		// Obtener registros de la base de datos << banco >>
		fncBD_ObtenerDatosBanco();

		// Verificar el estado de cuenta
		if( banco.EstadoDeCuenta == ecCuentaActivada){
			printf("Lo siento, operacion rechazado. \n");
			printf("Cuenta ya esta activada. \n");
		}else if( banco.EstadoDeCuenta == ecCuentaCreadaONueva){
			printf("Lo siento, operacion rechazado. \n");
			printf("Cuenta nueva, la cuenta deberia estar (bloqueada / desactivada / recuperada ). \n");
		}else{

			printf("2) Introduzca PIN de la cuenta: \n");
			scanf("%i", &PIN[0]);
			BUFFERFREE;

			printf("3) Confirmar PIN de la cuenta: \n");
			scanf("%i", &PIN[1]);
			BUFFERFREE;

			if( CHECKEO_PIN(PIN[1]) ){
				MOSTRAR_MSGO_ERROR("Lo siento, PIN debe ser de 6 digitos.");
			}else if(PIN[1] != PIN[0]){
				MOSTRAR_MSGO_ERROR("Lo siento, PIN no coinciden.");
			}else if( PIN[1] != banco.PIN ){
				MOSTRAR_MSGO_ERROR("Lo siento, PIN incorrecto.");
			}else{
				
				int ecGuardado = banco.EstadoDeCuenta;
				// Generamos PIN nuevo solo si la cuenta esta:
				// bloqueada o desactivada
				if(banco.EstadoDeCuenta != ecCuentaRecuperado )
					banco.PIN = fnc_GenerarPIN();

				// Se activa la cuenta, solo si la cuenta aun
				// no esta activada, es decir, que el estado de cuenta esta:
				// Bloqueda o Desactivada o Recuperada
				banco.EstadoDeCuenta = ecCuentaActivada;
				
				// Actualizar la base de datos << banco >>
				// de la cuenta
                fncBD_ActualizarDBBanco();

				// Registrar operacion
				actividades.TipoDeActividad = taConfiguracionCuenta;
				fncBD_RegistrarActividades("Banco: E&V Bank",
				"Cuenta: Activada", "Operacion: Aprobada");
				
				printf("\nNOTA:\n");
				printf("La cuenta %s \n", banco.NoCuenta);
				printf("con no. de tarjeta %s: \n", banco.NoTarjeta);
				printf("Se activo exitosamente. \n");

				// Mostramos PIN nuevo solo si la cuenta esta:
				// bloqueada o desactivada
				if( ecGuardado != ecCuentaRecuperado )
					printf("PIN generado: %i \n", banco.PIN);

			}
		}

	}else{ MOSTRAR_MSGO_ERROR("Lo siento, la cuenta es inexistente."); }

	fncBD_DeshacerConexionDB();
	//BUFFERFREE;

}