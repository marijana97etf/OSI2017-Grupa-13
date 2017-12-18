# OSI2017-Grupa-13
PROJEKAT FINANCIAL MANAGEMENT SYSTEM

Glavni zadatak ovog projekta je da se napravi softver koji će da omogući efikasnu analizu troškova proizvoljne kompanije. Softver očekivano treba da:
1.	vrši pouzdanu analizu i automatsku obradu računa
2.	omogućava jednostavan interfejs i strukturu za korisnika
3.	omogućava otkrivanje grešaka prilikom prijave ili unosa podataka
4.	bude razumljiv, lakoodrziv i jednostavan
5.	kontroliše prava pristupa i opcije kroz korisnicke naloge

Podaci, odnosno računi kompanije, koje softver obrađuje se trebaju trajno čuvati u sistemu, kako računi koji se unose u sistem, 
tako i podaci sa  računa koji se dobijaju obradom računa.
Unos podataka u sistem treba da se vrši automatski, tako što se učitavaju računi sačuvani u folderu za učitavanje. 
Obrada podataka podrazumijeva učitavanje podataka sa računa, za razlicite formate racuna koji su definisani u sistemu, 
i njihovo memorisanje. Prije obrade potrebno je izvršiti validaciju računa tj. provjeru njihove ispravnosti (verifikacija 
podataka sa računa, provjera saglasnosti sa dozvoljenim formatima itd.). Ako je račun ispravan podaci se sačuvaju na odgovarajuća mjesta. 
U suprotnom, korisnik će imati priliku da vidi detalje o neispravnosti u  odgovarajućem fajlu. 
Takođe,  omogućeno je i ignorisanje računa koji su već obrađeni. 
Kroz organizaciju podataka u izlazne fajlove  i pregled rezultata obrade omogućena je analiza troškova. 
Podaci sa računa se izvoze u odgovarajuće fajlove (podaci za određenog kupca, za određeni proizvod, ukupnu prodaju na mjesečnom nivou) 
i sačuvaju.
Softver podržava još i korisničke naloge kojim se definišu različita prava pristupa i različite opcije za različite korisnike. S obzirom na ovo, potrebno je da se korisnici prijave prilikom pokretanja aplikacije pin kodom i korisničkim imenom, pri čemu softver na osnovu unesenih podataka korisnika određuje korisničku grupu kojoj pripada i time mu dodjeljuje određena prava pristupa.
