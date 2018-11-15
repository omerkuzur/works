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
	setlocale(LC_ALL,""); //turkce karakter için
	string dosyain = "odev.txt";

	int gonderim,yazmahizi;
	
	do{
	cout<<"PC kaç saniyede bir kuyruga belge gönderir? (sn) :";
	cin>>gonderim;
	cout<<"Yazýcýnýn bir sayfayý yazma hýzý nedir? (cn):";
	cin>>yazmahizi;
	if(gonderim<=0 || yazmahizi<=0) cout<<endl<<"Yanlýþ giriþ degeri. Tekrar deneyiniz"<<endl;
	
	}while(gonderim<=0 || yazmahizi<=0);//giriþ degerlerinin 0 dan büyük olmasý saðlandý.
	
	
	ifstream dosya;
    dosya.open(dosyain.c_str());
	Belge veri[A] ,kuyruk[KAPASITE+1]; // +1 yazýlmakta olan verinin tutuldugu indis.
	int i=0,sn=0;
	
	 while(!dosya.eof()){  	//dizi adýnda bir arraya veriler alýnýyor
	 	
   	    dosya>>veri[i].belgeAdi;
  	    dosya>>veri[i].belgeBoyutu;
  	    dosya>>veri[i].sayfaSayisi;
  	    dosya>>veri[i].belgeSahibi.ad;
 	    dosya>>veri[i].belgeSahibi.soyad;
 	    dosya>>veri[i].belgeSahibi.k_adi;
 	    dosya>>veri[i].belgeSahibi.eposta;
 	    //dosya>>veri[i]belgeSahibi.dyili;   //dogumyýlý verisi yok
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
 	  	 
 	 int veriSayaci=0, cursor=0,kap=i,eskiYazma=0,ilkdeger=0,dolutest=0,bostest=0; //cursor kuyrugun isaret degiskeni. veri sayaci veri dizisindeki iþaret deðiþkeni, kap veri sayaciinin ulasabilecegi max deger.
 	 
 	 while(kap!=0 || cursor!=0){ //yazacak veri kalmamýþ ve kuyruk boþ ise çýkar(0 0 durumu)
 	 
 	 	
 	 		// YAZMA KISMI ilk baþta kuyrugu test ediyoruz. Yazma kýsmý ilk kontrol cunku kuyruk bosaldýmý gonderne ýslemi olabilsin.
 	 		
		  if(cursor!=0){
		  	
		  	if((sn - kuyruk[0].saniye) % ((yazmahizi * kuyruk[0].sayfaSayisi) + eskiYazma) == 0 ){ //o anki saniyeden alýndýðý zamanki saniye çýkarýlarak gerçek zamanlý çýktý zamaný bulunuyor.
		  		ilkdeger=1;//bir defa yazdýktan sonra kuyruk boþ diyebilir.
		  		dolutest=0;
		  		eskiYazma+=(kuyruk[0].sayfaSayisi * yazmahizi)+ kuyruk[0].saniye;//eyazma ile yazma süreleri tutuluyor.sn verisi kuyruk bos oldugunda alýndýgý için eklenmesi gerekir.bos olmadýgý durumlarda zaten 0.
		  		
 	 			cout<<endl<< sn<< ".sn  -  Yazýcý belgeyi yazdý - \t"<< kuyruk[0].belgeAdi;
				  
				 
				if(cursor==1 && kap!=0) cout<<endl<<sn<<".sn  -  Yazýlacak belge yok";// cursor daha azaltýlmadýgýndan
 	 							
				cursor--; //cursor azaltýlarak dizinin boyutu bir küçültülür
				
				
				for(int t=0;t<cursor;t++){							 //kuyruk dizisini baþtaki veri yazýldýðý için bir aþaðý kaydýrýyor
					kuyruk[t]=kuyruk[t+1];
					
					}
						
				if(cursor!=0) cout<<endl<<sn<<".sn  -  Yazýcý kuyruktan okudu : "<<kuyruk[0].belgeAdi;
				
				}
		  	}	
		  else if(ilkdeger==0) cout <<" ";							 // en baþta kuyruk boþ demesi engellendi. bir defa yazmadan kuyruk boþ diyemez.
		  
		  else {
		  		cout<<endl<<sn<<".sn  -  Yazýlacak belge yok"; 
		  		eskiYazma=0;												  //kuyruk boþsa en son yazma saniyesini sýfýrlýyor
 	 	  } 
 	 	
 	 	//GONDERME KISMI
 	 	
		  if(cursor==KAPASITE+1){
		  	if(sn%gonderim==0) cout<<endl<<sn<<".sn  -  PC kuyruga yazamadý"; 
		  //}
		  } 
		  else if(sn % gonderim==0 && kap!=0){     				     // kuyruk dizisine veri ekler. 			
 	 		  
				
			  kuyruk[cursor] = veri[veriSayaci];  					 //dizi nin sýradaki verisini alýr kuyruða iter.0 dan kap a kadar(kap i-1 ye eþit)
 	 			
			  if(cursor==0)  kuyruk[cursor].saniye = sn;			 // eger kuyruk boþ iþe ilk veri alýndýðýndan yazýlana kadar geçen süreyi hesaplamak için setlenir.
 	 		
			  cout<<endl<<sn<<".sn  -  PC kuyruga yazdý - \t"<< kuyruk[cursor].belgeAdi;
			  
			  
			  	
			  	if(cursor==0) cout<<endl<<sn<<".sn  -  PC kuyruktan okudu - \t"<<kuyruk[cursor].belgeAdi;
 	 		veriSayaci++;
 	 		cursor++;
 	 		kap--; 													//kapasite veri sayýsýna eþit olduðundan eksiltir ve en son alýnacak deðer olmadýðýnda 0 olur
 	 		
		      }
		  	
 	 	sn++;														// saniye deðiþkeni
	  	
		  
		}

 	 cout<<endl<<"Tüm belgeler yazýldý..."; 						//islemin bittigi yer
 	 

	return 0;
}
