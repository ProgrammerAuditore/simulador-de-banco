void fncBD_CrearBDBanco(){
	
	// Crear la base de datos de banco
	snprintf(bdusuarios.PATHBanco, MAXCARACTERES * 2 ,"%s%s/%s%s",
	FolderBD[0], banco.NoCuenta,
	FilesBD[1], banco.NoTarjeta);
	
	FILE *bd = fopen(bdusuarios.PATHBanco, "w+");
	
	if( bd == NULL){
		perror("fncBD_CrearBDBanco: \n");
		perror("Base de datos << banco >> no creado... \n");
		exit(1);
	}

	fprintf(bd, "%s; // No. Tarjeta \n", banco.NoTarjeta);
	fprintf(bd, "%s; // No. Cuenta \n", banco.NoCuenta);
	fprintf(bd, "%i; // PIN \n", banco.PIN);
	fprintf(bd, "%i; // Estado de cuenta \n", banco.EstadoDeCuenta);
	fprintf(bd, "%lf; // Saldo ", banco.Saldo);
	
	fclose(bd);	
}