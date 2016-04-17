#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	//int preX; //onceki noktanin x koordinati
	//int preY; //onceki noktanin y koordinati
	int cost; //koordinatin maliyeti
	char change; //dogrudan islemin adını da tutabiliriz
}CELL;

/*
Algoritma word1 in word2 ye donusturulmesi uzerine kurgulanmıstır

koordinat i ,j ise
-----------------
I insert i, j-1
D delete i-1, j
M match  i-1, j-1
R replace i-1, j-1
*/

//fonksiyon prototipleri
CELL ** allocateMatrix(int, int); //matris icin dinamik olarak yer ayir
void initializeMatrix(CELL **, int, int); //matrisi ilklendir
void displayCostMatrix(CELL **, int, int); //maliyetleri ekrana yaz
void displayChangeMatrix(CELL **, int, int); //degisimleri ekrana yaz
int editDistance(CELL ** , char *, char *, int , int );
void findMinimum(CELL ** , int , int );

int main(){
	/*int k = 10;
	int deleteCost = 1;
	int insertCost = 1;
	int replaceCost = 1;*/

	/*
	char word1[20];
	char word2[20];

	printf("ilk kelimeyi giriniz\n");
	scanf("%s", word1);
	printf("ikinci kelimeyi giriniz\n");
	scanf("%s", word2);
	*/

	int i,j; //döngü i
	int minimumCost;
	char word1[20] = "maths";
	char word2[20] = "arts";

	int m = strlen(word1) + 1;
	int n = strlen(word2) + 1;

	//edit distance matrisi icin yer ac
	CELL **editMatrix = allocateMatrix(m, n);

	initializeMatrix(editMatrix, m, n);

	displayCostMatrix(editMatrix, m, n);
	displayChangeMatrix(editMatrix, m, n);

	minimumCost = editDistance(editMatrix, word1, word2, m, n);
	displayCostMatrix(editMatrix, m, n);
	displayChangeMatrix(editMatrix, m, n);

	printf("\nmimimum maliyet : %d\n", minimumCost);

	return 0;
}

int editDistance(CELL ** editMatrix, char *word1, char *word2, int m, int n ){
	int i, j; //dongu indisleri
	char change;

	for(i=1; i<m; i++){
		for(j=1; j<n; j++){
			if(word1[i-1] == word2[j-1]){//harfler aynı ise matching
				editMatrix[i][j].cost = editMatrix[i-1][j-1].cost;
				editMatrix[i][j].change = 'M';
			}
			else{ //harfler farkli ise minimum maliyeti bul
				findMinimum(editMatrix, i, j);
			}
		}
		displayCostMatrix(editMatrix, m, n);
	}// end for
	displayCostMatrix(editMatrix, m, n);

	printf("\n\n%d %dn", i, j);
	return editMatrix[i-1][j-1].cost;
}//end editDistance

void findMinimum(CELL ** editMatrix, int i, int j){
	/*ekleme silme ve degisme maliyeti 1 kabul edilmistir
	maliyetlerin degismesi halinde once maliyet degerleri eklenmeli
	sonra karsilastirma yapılmalidir*/

	int delete = editMatrix[i-1][j].cost +1 ; // + deleteCost
	int insert = editMatrix[i][j-1].cost + 1; // + insertCost
	int replace = editMatrix[i-1][j-1].cost + 1; // + replaceCost

	if(delete <= insert && delete <= replace){
		editMatrix[i][j].cost = delete;
		editMatrix[i][j].change = 'D';
	}
	else if(insert < delete && insert <= replace){
		editMatrix[i][j].cost = insert;
		editMatrix[i][j].change = 'I';
	}
	else{
		editMatrix[i][j].cost = replace;
		editMatrix[i][j].change = 'R';
	}
}

CELL ** allocateMatrix(int m, int n){
	int i;

	//satirlar icin yer ayir
	CELL **editMatrix = (CELL **) malloc (m * sizeof(CELL *));

	//sutunlar icin yer ayir
	for(i=0; i<m; i++)
		editMatrix[i] = (CELL *) malloc (n * sizeof(CELL));

	//istenen bellek alani ayrilamadiysa programi sonladir
	if(editMatrix == NULL){
		printf("Yer ayrilamadi");
		exit(0);
	}

	return editMatrix;
}

void initializeMatrix(CELL **editMatrix, int m, int n){
	int i;

	//ilk sutun icin
	for(i=0; i<m; i++){
		editMatrix[i][0].cost = i;
		editMatrix[i][0].change = 'D';
	}

	//ilk satir icin
	for(i=0; i<n; i++){
		editMatrix[0][i].cost = i;
		editMatrix[0][i].change = 'I';
	}
}

void displayCostMatrix(CELL ** editMatrix, int m, int n){
	int i, j; //dongu indisleri

	for(i=0; i<m; i++){
		printf("\n");
		for(j=0; j<n; j++){
			printf("%3d", editMatrix[i][j].cost);
		}
	}
	printf("\n");
}

void displayChangeMatrix(CELL **editMatrix, int m, int n){
	int i, j; //dongu indisleri

	for(i=0; i<m; i++){
		printf("\n");
		for(j=0; j<n; j++){
			printf("%3c", editMatrix[i][j].change);
		}
	}
	printf("\n");
}
