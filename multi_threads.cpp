#include<iostream>
#include<pthread.h>
#include<ctime>

using namespace std;

bool asalSayi(int sayi){
	if(sayi < 2)return false;
	int i = 2;
	int sinir = sayi/2;
	while(i<=sinir){
		if(sayi%i==0)
			return false;
		i++;
	}
	return true;
}

void *asalArama(void *args){
	int *limit = (int*) args;
	for(int i = limit[0];i <=limit[1];i++){
		if(asalSayi(i)){
			//cout << " " << i << " ";
		}
	}
}

int main(){
	
	int kanal_sayisi, rnd, aralik, starts = 0;
	time_t start, finish;
	cout << "Sistem Testi icin asal bulma islemi yapilacaktir. \nHangi sayiya kadar islem devam etsin: ";
	cin >> rnd;
	do{
		cout << " " << rnd  <<" tam bolen bir say¿ giriniz!..";
		cin >> kanal_sayisi;
		aralik = rnd/kanal_sayisi;	
	}while(rnd%kanal_sayisi!=0);
	
	int arry[kanal_sayisi][2];
	pthread_t kanal[kanal_sayisi];
	
	for(int i=0;i<kanal_sayisi;i++){
		arry[i][0]=starts;
		starts+=aralik;
		arry[i][1]=starts;
		//cout << "start :" << arry[i][0] << " end :" << arry[i][1] << " ";
	}
	start = clock();
	for(int i=0; i<kanal_sayisi; i++){
		pthread_create(&kanal[i],NULL,asalArama,arry[i]);
	}
	for(int i=0; i<kanal_sayisi; i++){
		pthread_join(kanal[0],NULL);
	}
	
	aramaAralik(0,40000);
	finish = clock();
	
	cout << "\n Harcanan zaman = " << difftime(finish, start) << " milisaniye";
	getchar();
	system("PAUSE");
	return 0;
}

