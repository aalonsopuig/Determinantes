/*	
	Programa "Determinantes v2.3" 
	Por Alejandro Alonso Puig 
	14/7/03
	
	Realiza el cálculo de determinantes de cualquier tamaño
	-Uso de punteros. 
	-Código en C++. 
	-Uso de FSTREAM (Incluye IOSTREAM). 
	-Uso de ficheros
*/

#include	<fstream.h>

float		fCalcDet (float *pfDet,int iTam);	//Función cálculo determinantes
ifstream	ifsIn;								//Flujo de entrada
ofstream	ofsOut;								//Flujo de salida

int main (void)
{

	float	*pfDeterminante;					//Puntero al determinante a calcular
	float	*pfElemento;						//Puntero a cada elemento

	float	fResultado;							//Resultado del determinante
	int		iFila, iColumna,					//Indices
			iTamanio;							//Tamaño determinante
	char	cContinue='s';						//Usuario decide si calcular otro

	cout << "PROGRAMA DETERMINANTES v2.2\n";
	cout << "\nPor Alejandro Alonso Puig";
	cout << "\n12-Julio-2003";
	cout << "\n-------------------------";

	do
	{
		do
		{
			cout << "\n\nIntroduzca tamano del determinante: ";
			cin >> iTamanio;
		}
		while (iTamanio <= 0);
		pfDeterminante = new float[iTamanio*iTamanio];	//Asignamos espacio para determinante
		cout << "\nIntroduzca los valores del determinante\n";

		//Entrada valores Determinante
		for (iFila=0; iFila < iTamanio; iFila++) 
		{
			cout << "\n";
			for (iColumna=0; iColumna < iTamanio; iColumna++)
			{
				cout << "[" << iFila+1 << "," << iColumna+1 << "]: ";
				pfElemento=pfDeterminante+(iFila*iTamanio + iColumna);
				cin >> *pfElemento;
			}
		}

		//Se muestra en pantalla el Determinante introducido (Previamente lo guarda en fichero)

		ofsOut.Open("Determinante.txt");
		if(!ofsOut) cerr<<"\nImposible abrir fichero como salida";
		ofsOut.put
		cout << "\nDeterminante introducido:\n\n";
		for (iFila=0; iFila < iTamanio; iFila++) 
		{
			cout << "| ";
			for (iColumna=0; iColumna < iTamanio; iColumna++) 
			{
				pfElemento=pfDeterminante+(iFila*iTamanio + iColumna);
				cout.setf(ios::fixed);
				cout.width(8);
				cout.precision(2);
				cout <<  *pfElemento << " ";
			}
			cout << "|\n";
		}
		cout << "\n\n";

		//Se muestra el resultado del Determinante
 		fResultado = fCalcDet(pfDeterminante, iTamanio);
		cout << "Resultado = " << fResultado <<"\n\n";

		delete(pfDeterminante); //Liberamos la memoria usada
		//Se pregunta si queremos calcular otro Determinante
		cout << "Calcular otro determinante (s/n)?";
		cin >> cContinue;
//		scanf ("%c", &cContinue);
		
	}
	while (cContinue!='n');
	return (0);
}
					
	
float fCalcDet (float *pfDet,int iTam)
//Devuelve el valor de un determinante de tamaño iTam x iTam
//Se utiliza el método de triangulación por el que se calcula
//un Determinante triangular equivalente y se multiplican los 
//valores de la diagonal.

{
	float	fResult=1;					//Resultado Determinante
	float	*pfCalcDet;					//Puntero a area de cálculos (Det Triangular)
	float	fFactor;					//Factor multiplicador
	int		iCol, iFil,					//Indices
			iFilCalc, iColCalc,			//Indices en cálculo
			iFilMov, iColMov;			//Indice para intercambio filas
	float	*pfMovDet;					//Puntero area para mov filas
	bool	bOkDet;						//Control calculos posibles


	pfCalcDet = new float[iTam*iTam];	//Asignamos espacio para determinante
	pfMovDet = new float[iTam];		//Asignamos espacio para area mov filas
	// Hacemos copia del determinante para cálculos
	for (iFil=0; iFil < iTam; iFil++) 
		for (iCol=0; iCol < iTam; iCol++) 
			*(pfCalcDet+(iFil*iTam + iCol))=*(pfDet+(iFil*iTam + iCol));
	// Obtenemos un determinante triangular equivalente
	for (iCol=0; iCol < iTam; iCol++) 
	{
		iFilCalc=iCol;
		for (iFil=iCol+1; iFil < iTam; iFil++) 
		{
			iColCalc=iCol;
			if (*(pfCalcDet+(iFilCalc*iTam + iColCalc))==0)
			//Hay que intercambiar filas para evitar división por 0
			{
				bOkDet=false;	//Determinante no OK hasta que encontremos un valor no 0
				for (iColMov=0; iColMov <iTam; iColMov++)
					*(pfMovDet+iColMov)=*(pfCalcDet+(iFilCalc*iTam + iColMov));
				for (iFilMov=iFilCalc; iFilMov < iTam; iFilMov++)
				//Bucle búsqueda no ceros en columna actual
				{
					if (*(pfCalcDet+(iFilMov*iTam + iColCalc))!=0)
					//Encontrado valor no 0. Intercambiamos filas
					{
						for (iColMov=0; iColMov <iTam; iColMov++)
						{
							*(pfCalcDet+(iFilCalc*iTam + iColMov))=*(pfCalcDet+(iFilMov*iTam + iColMov));
							*(pfCalcDet+(iFilMov*iTam + iColMov))=*(pfMovDet+iColMov);
						}
						bOkDet=true;		//Todo OK. Podemos seguir con calculos
						fResult *=-1;	//Al intercambiar filas cambia el signo
						break;			//Salimos bucle busqueda no ceros.
					}
				}
				if (!bOkDet)
					return (0);		//Si no encontramos un no cero, resultado nulo
			}

			fFactor=*(pfCalcDet+(iFil*iTam + iCol)) 
			      / *(pfCalcDet+(iFilCalc*iTam + iColCalc));	//Calculo factor multiplicador

			//Multiplicamos fila por factor multiplicador y restamos de fila actual
			for (iColCalc=iCol; iColCalc < iTam; iColCalc++)
				*(pfCalcDet+(iFil*iTam + iColCalc)) -=*(pfCalcDet+(iFilCalc*iTam + iColCalc))*fFactor;
		}
	}

	//Ya tenemos el determinante triangular equivalente. Multiplicamos
	//valores de diagonal para calcular resultado.
	for (iCol=0; iCol <iTam; iCol++)
		fResult *=*(pfCalcDet+(iCol*iTam + iCol));

	delete(pfCalcDet); //Liberamos la memoria usada
	delete(pfMovDet); //Liberamos la memoria usada



	return (fResult);	//Devolvemos resultado Determinante
}