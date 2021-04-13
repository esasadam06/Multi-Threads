#include<iostream>
#include<pthread.h>
#include<ctime>
#include<iomanip>

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
			//cout << " " << limit[2] << " ";
		}
	}
}

int main(){
	
	int kanal_sayisi, rnd = 200000, aralik, starts = 0;
	time_t start, finish;
	int dif[5];
	int cekirdek[] = {1,2,4,8,16,32};

	for(int j=0;j<6;j++){
		starts = 0;
		kanal_sayisi = cekirdek[j];
		cout << "\n" << kanal_sayisi;
		aralik = rnd/kanal_sayisi;
		int arry[kanal_sayisi][3];
		pthread_t kanal[kanal_sayisi];
	
		for(int i=0;i<kanal_sayisi;i++){
			arry[i][0]=starts;
			starts+=aralik;
			arry[i][1]=starts;
			arry[i][2]=i;
			//cout << "start :" << arry[i][0] << " end :" << arry[i][1] << " ";
		}
		start = clock();
		for(int i=0; i<kanal_sayisi; i++){
			pthread_create(&kanal[i],NULL,asalArama,arry[i]);
		}
		for(int i=0; i<kanal_sayisi; i++){
			pthread_join(kanal[i],NULL);
		}
	
		finish = clock();
		dif[j] = difftime(finish, start);
		cout << "\tThread ile harcanan zaman = " << dif[j] << " milisaniye";
	}
	
	cout << "\n";
	
	for(int i=0; i<6; i++){
		float temp = dif[i];
		float ilk = dif[0];
		float spd = ilk/temp;
		float verim = spd/cekirdek[i];
		cout << fixed << setprecision(5);
		cout << cekirdek[i] << "\tThread kullanimi ile hiz: " << spd << "\tVerim: " << verim <<endl;		
	}

	getchar();
	return 0;
}