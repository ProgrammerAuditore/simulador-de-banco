void fncBD_EstablecerConexionBD(bool verConexion){
	
	int conexion=0;
	//printf("%s %s \n", bdusuarios.NoCuenta, bdusuarios.NoTarjeta);
	
	// Generar el PATH de la carpeta de la cuenta
	snprintf(bdusuarios.PATHUser, MAXCARACTERES * 2 ,"%s%s/%s%s",
	FolderBD[0],
	bdusuarios.NoCuenta,
	FilesBD[2],
	bdusuarios.NoTarjeta
	);

	// printf("::: %s :::\n", bdusuarios.PATHUser);

	FILE *PATHUser = fopen(bdusuarios.PATHUser, "r");
	if(PATHUser == NULL){
		perror("1) fncBD_EstablecerConexionBD: \n");
		perror("Lo siento, BASE DE DATOS de datos de usuario no establecida. :'( \n");
		exit(1);
	}else{ conexion++; }
	fclose(PATHUser);
	
	snprintf(bdusuarios.PATHActividades, MAXCARACTERES * 2 ,"%s%s/%s%s",
	FolderBD[0],
	bdusuarios.NoCuenta,
	FilesBD[0],
	bdusuarios.NoTarjeta
	);
	
	FILE *PATHActividades = fopen(bdusuarios.PATHActividades, "r");
	if(PATHActividades == NULL){
		perror("2) fncBD_EstablecerConexionBD: \n");
		perror("Lo siento, BASE DE DATOS de datos de actividades no establecida. :'( \n");
		exit(1);
	}else{ conexion++; }
	fclose(PATHActividades);
		
	snprintf(bdusuarios.PATHBanco, MAXCARACTERES * 2 ,"%s%s/%s%s",
	FolderBD[0],
	bdusuarios.NoCuenta,
	FilesBD[1],
	bdusuarios.NoTarjeta
	);
	
	FILE *PATHABanco = fopen(bdusuarios.PATHBanco, "r");
	if(PATHABanco == NULL){
		perror("3) fncBD_EstablecerConexionBD: \n");
		perror("Lo siento, BASE DE DATOS de datos de banco no establecida. :).\n");
		exit(1);
	}else{ conexion++; }
	fclose(PATHABanco);
	
	if( conexion == 3){
		MOSTRAR_MSGOPERACION("CONEXION ESTABLECIDA");
		if(verConexion)
			fncBD_MostrarConexionDB();
	}
}
