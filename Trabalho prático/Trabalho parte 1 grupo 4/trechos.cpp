
//       Intercalação de Trechos

void intercala(int a[], int inicio, int meio, int fim) {
	int i = inicio, j = meio+1;
	int tamanho = fim - inicio + 1;
	int aux[tamanho]; // vetor auxiliar
	for (int k=0; k < tamanho; k++) {
		if ((i <= meio) and (j <= fim)){ 
			if (a[i] <= a[j]){ 
				aux[k] = a[i]; // copia trecho1 em aux[]
				i++; 			// avança em trecho1
			} else { // 
				aux[k] = a[j]; // copia trecho2 em aux[]
				j++;	 		// avanca em trecho2
 			}
        } else if (i > meio) { // terminou o trecho1	
			aux[k] = a[j];
			j++;
		} else { 				 // terminou o trecho2
			aux[k] = a[i];
			i++;
		}		
	}	
	// terminando: copiar de aux[] em a[inicio:fim]
	for (int k=0; k < tamanho; k++){ 
		a[inicio + k] = aux[k];
	}
}

//      Merge Sort em Memória
void mergesort(int a[], int inicio, int fim){
	int meio;
	if (inicio < fim) {
		meio = (inicio + fim)/2; 
		mergesort(a, inicio, meio);
		mergesort(a, meio+1, fim);
		intercala(a,inicio,meio,fim);
	}
}

//      Reescrita da Intercala()

// intercala v[p..q-1] e v[q..r] em v[p..r] 
void intercala(int v[], int p, int q, int r){
    int i = p, j = q;
    int tamanho = r - p + 1;
    int w[tamanho]; // vetor auxiliar
    int k = 0;
    while ((i < q) and (j <= r)) {                
       if (v[i] <= v[j])  {
           w[k++] = v[i++]; /* w[k] = v[i]; k++; i++; */
		} else  {
			w[k++] = v[j++]; /* w[k] = v[j]; k++; j++; */
		}
	} 

    // terminou um dos vetores, agora copia o outro
    while (i < q) {
        w[k++] = v[i++];
    }

    while (j <= r) {
       w[k++] = v[j++]; 
    }

    // agora copiamos do vetor auxiliar aux[] em v[p:r]
	for (int m = 0; m < tamanho; m++){ 
		v[p + m] = w[m];
    }
}