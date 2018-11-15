#include <fstream>
#include <iostream>
#include <clocale>
#include <string.h>
#define KAPASITE 3
#define A 1000
using namespace std;


struct BelgeSahibi{
  string ad;
  string soyad;
  string k_adi;
  string eposta;
  //int dyili;
};
struct Tarih{
	int yil;
	int gun;
	int ay;
	int saat;
	int dakika;
	int saniye;
};
struct Belge{
  BelgeSahibi belgeSahibi;
  Tarih tarih;
  string belgeAdi;
  double belgeBoyutu;
  int  sayfaSayisi;
  int saniye;
};


int main(){
	setlocale(LC_ALL,""); //turkce karakter i�in
	string dosyain = "odev.txt";

	int gonderim,yazmahizi;
	
	do{
	cout<<"PC ka� saniyede bir kuyruga belge g�nderir? (sn) :";
	cin>>gonderim;
	cout<<"Yaz�c�n�n bir sayfay� yazma h�z� nedir? (cn):";
	cin>>yazmahizi;
	if(gonderim<=0 || yazmahizi<=0) cout<<endl<<"Yanl�� giri� degeri. Tekrar deneyiniz"<<endl;
	
	}while(gonderim<=0 || yazmahizi<=0);//giri� degerlerinin 0 dan b�y�k olmas� sa�land�.
	
	
	ifstream dosya;
    dosya.open(dosyain.c_str());
	Belge veri[A] ,kuyruk[KAPASITE+1]; // +1 yaz�lmakta olan verinin tutuldugu indis.
	int i=0,sn=0;
	
	 while(!dosya.eof()){  	//dizi ad�nda bir arraya veriler al�n�yor
	 	
   	    dosya>>veri[i].belgeAdi;
  	    dosya>>veri[i].belgeBoyutu;
  	    dosya>>veri[i].sayfaSayisi;
  	    dosya>>veri[i].belgeSahibi.ad;
 	    dosya>>veri[i].belgeSahibi.soyad;
 	    dosya>>veri[i].belgeSahibi.k_adi;
 	    dosya>>veri[i].belgeSahibi.eposta;
 	    //dosya>>veri[i]belgeSahibi.dyili;   //dogumy�l� verisi yok
   	    dosya>>veri[i].tarih.yil;
 	    dosya>>veri[i].tarih.gun;
  	    dosya>>veri[i].tarih.ay;
  	    dosya>>veri[i].tarih.saat;
  	    dosya>>veri[i].tarih.dakika;
  	    dosya>>veri[i].tarih.saniye;
		veri[i].saniye=0;
    	i++;
 	 }
 	 dosya.close();
 	  	 
 	 int veriSayaci=0, cursor=0,kap=i,eskiYazma=0,ilkdeger=0,dolutest=0,bostest=0; //cursor kuyrugun isaret degiskeni. veri sayaci veri dizisindeki i�aret de�i�keni, kap veri sayaciinin ulasabilecegi max deger.
 	 
 	 while(kap!=0 || cursor!=0){ //yazacak veri kalmam�� ve kuyruk bo� ise ��kar(0 0 durumu)
 	 
 	 	
 	 		// YAZMA KISMI ilk ba�ta kuyrugu test ediyoruz. Yazma k�sm� ilk kontrol cunku kuyruk bosald�m� gonderne �slemi olabilsin.
 	 		
		  if(cursor!=0){
		  	
		  	if((sn - kuyruk[0].saniye) % ((yazmahizi * kuyruk[0].sayfaSayisi) + eskiYazma) == 0 ){ //o anki saniyeden al�nd��� zamanki saniye ��kar�larak ger�ek zamanl� ��kt� zaman� bulunuyor.
		  		ilkdeger=1;//bir defa yazd�ktan sonra kuyruk bo� diyebilir.
		  		dolutest=0;
		  		eskiYazma+=(kuyruk[0].sayfaSayisi * yazmahizi)+ kuyruk[0].saniye;//eyazma ile yazma s�releri tutuluyor.sn verisi kuyruk bos oldugunda al�nd�g� i�in eklenmesi gerekir.bos olmad�g� durumlarda zaten 0.
		  		
 	 			cout<<endl<< sn<< ".sn  -  Yaz�c� belgeyi yazd� - \t"<< kuyruk[0].belgeAdi;
				  
				 
				if(cursor==1 && kap!=0) cout<<endl<<sn<<".sn  -  Yaz�lacak belge yok";// cursor daha azalt�lmad�g�ndan
 	 							
				cursor--; //cursor azalt�larak dizinin boyutu bir k���lt�l�r
				
				
				for(int t=0;t<cursor;t++){							 //kuyruk dizisini ba�taki veri yaz�ld��� i�in bir a�a�� kayd�r�yor
					kuyruk[t]=kuyruk[t+1];
					
					}
						
				if(cursor!=0) cout<<endl<<sn<<".sn  -  Yaz�c� kuyruktan okudu : "<<kuyruk[0].belgeAdi;
				
				}
		  	}	
		  else if(ilkdeger==0) cout <<" ";							 // en ba�ta kuyruk bo� demesi engellendi. bir defa yazmadan kuyruk bo� diyemez.
		  
		  else {
		  		cout<<endl<<sn<<".sn  -  Yaz�lacak belge yok"; 
		  		eskiYazma=0;												  //kuyruk bo�sa en son yazma saniyesini s�f�rl�yor
 	 	  } 
 	 	
 	 	//GONDERME KISMI
 	 	
		  if(cursor==KAPASITE+1){
		  	if(sn%gonderim==0) cout<<endl<<sn<<".sn  -  PC kuyruga yazamad�"; 
		  //}
		  } 
		  else if(sn % gonderim==0 && kap!=0){     				     // kuyruk dizisine veri ekler. 			
 	 		  
				
			  kuyruk[cursor] = veri[veriSayaci];  					 //dizi nin s�radaki verisini al�r kuyru�a iter.0 dan kap a kadar(kap i-1 ye e�it)
 	 			
			  if(cursor==0)  kuyruk[cursor].saniye = sn;			 // eger kuyruk bo� i�e ilk veri al�nd���ndan yaz�lana kadar ge�en s�reyi hesaplamak i�in setlenir.
 	 		
			  cout<<endl<<sn<<".sn  -  PC kuyruga yazd� - \t"<< kuyruk[cursor].belgeAdi;
			  
			  
			  	
			  	if(cursor==0) cout<<endl<<sn<<".sn  -  PC kuyruktan okudu - \t"<<kuyruk[cursor].belgeAdi;
 	 		veriSayaci++;
 	 		cursor++;
 	 		kap--; 													//kapasite veri say�s�na e�it oldu�undan eksiltir ve en son al�nacak de�er olmad���nda 0 olur
 	 		
		      }
		  	
 	 	sn++;														// saniye de�i�keni
	  	
		  
		}

 	 cout<<endl<<"T�m belgeler yaz�ld�..."; 						//islemin bittigi yer
 	 

	return 0;
}
