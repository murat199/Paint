#include <allegro.h>
#include <math.h>

BITMAP *bmp;
BITMAP *res_yeni,
       *res_kaydet,
       *res_ac,
       *res_cikis,
       *res_kalem,
       *res_silgi,
       *res_renkdoldur,
       *res_renksec,
       *res_kayit;


PALETTE pal;



void ekran_ayarlar();  ///bu fonksiyon ekrani olusturur. klavyeyi, fareyi, zamanlayiciyi yukler.
void ekran_yukle();   /// olusturdugumuz grafik ekranin arkaplani olusturur. Cizim alanini cizer.
void menu_resim_yukle();  ///menu ikonlari yuklenir.
void mesaj();  ///kullaniciya mesaj gosterdigimiz fonksiyon.

void ciz();  ///cizim yapilan fonksiyon
void renk_sec();  ///secilen rengi kontrol eder.
void arac_sec_sol(); ///sol taraftaki araclarin farenin uzerine geldigi araca kenarlik ekler.
void arac_sec_alt(); ///alt kisimdaki araclarin fare ile uzerine gelindiginde o aracin icini boyar.
void menu_sec();  ///sol kisimdaki menulerin(ac, kaydet, yeni) fare ile uzerine gelindiginde mavi kenarlik ekler.
void panel_yukle(); ///ekranin sag, sol ve alt kisimlarini olusturur.


int arac=1, ///bu degisken secili araci tutar.
    boyut=1, ///bu degisken boyutu tutar.
    secilen_renk, ///bu degisken secili rengi tutar.
    secilen_renk_2, ///bu degisken ikinci secili rengi tutar.
    xx1=0,  ///fareye ilk tiklamadaki(sol tik) x koordinati
    xx2=0,  ///fareyi sol tiktan biraktigimizdaki x koordinati
    yy1=0,  ///fareye ilk tiklamadaki(sol tik) y koordinati
    yy2=0;  ///fareyi sol tiktan biraktigimizdaki y koordinati

int x3 = -1,
    y3 = -1;

char *mesaj2="Giris";  ///bu degisken erkanda gozukecek mesaji tutar.

char *str_secili_arac="kalem"; ///bu degisken secili araci tutar

void alt_panel_secili_arac(){

    /**
    **********************
    Bu fonksiyonda str_secili_arac (char tipinde) değişkeni kontrol edilir.
    str_secili_arac degiskeni cizgi, silgi, ici bos daire gibi araclardan hangisine esitse o aracin secili oldugunu gostermek ıcın
    o aracın ıcını beyaza boyar(daire gibi) veya kenarligini mavi renk yapar.
    */

    if(str_secili_arac=="cizgi"){
        rectfill(bmp,80,590,140,595,makecol(255,255,255)); ///cizgi aracinin kenarligini mavi renk yapar. secili ol
    }
    else if(str_secili_arac=="dikdortgen_ici_bos"){
        rect(bmp,160,565,220,615,makecol(255,255,255));
        rect(bmp,161,566,219,614,makecol(255,255,255));
        rect(bmp,162,567,218,613,makecol(255,255,255));
    }
    else if(str_secili_arac=="dikdortgen_ici_dolu"){
        rectfill(bmp,240,565,300,615,makecol(255,255,255));
    }
    else if(str_secili_arac=="daire_ici_bos"){
        circle(bmp,350,590,30,makecol(255,255,255));
    }
    else if(str_secili_arac=="daire_ici_dolu"){
        circlefill(bmp,430,590,30,makecol(255,255,255));
    }
    else if(str_secili_arac=="ucgen_ici_bos"){
        line(bmp,480,615,540,615,makecol(255,255,255));
        line(bmp,510,565,480,615,makecol(255,255,255));
        line(bmp,510,565,540,615,makecol(255,255,255));
    }
    else if(str_secili_arac=="ucgen_ici_dolu"){
        triangle(bmp,590,565,560,615,620,615, makecol(255,255,255));
    }
    else if(str_secili_arac=="yeni"){
        rect(bmp,0,0,70,70,makecol(25,150,200));
        rect(bmp,1,1,69,69,makecol(25,150,200));
        rect(bmp,2,3,68,68,makecol(25,150,200));
    }
    else if(str_secili_arac=="kaydet"){
        rect(bmp,0,70,70,140,makecol(25,150,200));
        rect(bmp,1,71,69,139,makecol(25,150,200));
        rect(bmp,2,72,68,138,makecol(25,150,200));
    }
    else if(str_secili_arac=="ac"){
        rect(bmp,0,140,70,210,makecol(25,150,200));
        rect(bmp,1,141,69,209,makecol(25,150,200));
        rect(bmp,2,142,68,208,makecol(25,150,200));
    }
    else if(str_secili_arac=="kalem"){
        rect(bmp,0,345,70,415,makecol(25,150,200));
        rect(bmp,1,346,69,414,makecol(25,150,200));
        rect(bmp,2,347,68,413,makecol(25,150,200));
    }
    else if(str_secili_arac=="silgi"){
        rect(bmp,0,415,70,485,makecol(25,150,200));
        rect(bmp,1,416,69,484,makecol(25,150,200));
        rect(bmp,2,417,68,483,makecol(25,150,200));
    }
    else if(str_secili_arac=="doldur"){
        rect(bmp,0,485,70,555,makecol(25,150,200));
        rect(bmp,1,486,69,554,makecol(25,150,200));
        rect(bmp,2,487,68,553,makecol(25,150,200));
    }
    else if(str_secili_arac=="renk_al"){
        rect(bmp,0,555,70,625,makecol(25,150,200));
        rect(bmp,1,556,68,624,makecol(25,150,200));
        rect(bmp,2,557,69,623,makecol(25,150,200));
    }
}

char *str_secili_renk="siyah"; ///bu degisken secili rengi tutar
void renk_secili_arac(){
    /**
    **********************
    Bu fonksiyonda str_secili_renk(char tipinde) değişkeni kontrol edilir.
    str_secili_renk degiskeni secilen rengin ismini tutar.
    Bu fonksiyonda ise str_secili_renk degiskeni kontrol edilerek hangi renk secili ise o rengin secili oldugunu kullanıcının gormesi icin
    secili renge beyaz renk kenarlik eklenir.
    */

    if(str_secili_renk=="beyaz"){
        ///BEYAZ
        rect(bmp, 870, 80, 900, 110, makecol(0,0,0));
        rect(bmp, 871, 81, 899, 109, makecol(0,0,0));
        rect(bmp, 872, 82, 898, 108, makecol(0,0,0));
    }
    else if(str_secili_renk=="kirmizi"){
        ///KIRMIZI
        rect(bmp, 870, 120, 900, 150, makecol(255,255,255));
        rect(bmp, 871, 121, 899, 149, makecol(255,255,255));
        rect(bmp, 872, 122, 898, 148, makecol(255,255,255));
    }
    else if(str_secili_renk=="acik_yesil"){
        ///ACIK YESÝL
        rect(bmp, 870, 160, 900, 190, makecol(255,255,255));
        rect(bmp, 871, 161, 899, 189, makecol(255,255,255));
        rect(bmp, 872, 162, 898, 188, makecol(255,255,255));
    }
    else if(str_secili_renk=="lacivert"){
        ///LACIVERT
        rect(bmp, 870, 200, 900, 230, makecol(255,255,255));
        rect(bmp, 871, 201, 899, 229, makecol(255,255,255));
        rect(bmp, 872, 202, 898, 228, makecol(255,255,255));
    }
    else if(str_secili_renk=="sari"){
        ///SARI
        rect(bmp, 870, 240, 900, 270, makecol(255,255,255));
        rect(bmp, 871, 241, 899, 269, makecol(255,255,255));
        rect(bmp, 872, 242, 898, 268, makecol(255,255,255));
    }
    else if(str_secili_renk=="pembe"){
        ///PEMBE
        rect(bmp, 870, 280, 900, 310, makecol(255,255,255));
        rect(bmp, 871, 281, 899, 309, makecol(255,255,255));
        rect(bmp, 872, 282, 898, 308, makecol(255,255,255));
    }
    else if(str_secili_renk=="koyu_yesil"){
        ///KOYU YESIL
        rect(bmp, 870, 320, 900, 350, makecol(255,255,255));
        rect(bmp, 871, 321, 899, 349, makecol(255,255,255));
        rect(bmp, 872, 322, 898, 348, makecol(255,255,255));
    }
    else if(str_secili_renk=="kahverengi"){
        ///KAHVERENGI
        rect(bmp, 870, 360, 900, 390, makecol(255,255,255));
        rect(bmp, 871, 361, 899, 389, makecol(255,255,255));
        rect(bmp, 872, 362, 898, 388, makecol(255,255,255));
    }
    else if(str_secili_renk=="siyah"){
        ///SIYAH
        rect(bmp, 870, 400, 900, 430, makecol(255,255,255));
        rect(bmp, 871, 401, 899, 429, makecol(255,255,255));
        rect(bmp, 872, 402, 898, 428, makecol(255,255,255));
    }
    else if(str_secili_renk=="mavi"){
        ///MAVI
        rect(bmp, 870, 440, 900, 470, makecol(255,255,255));
        rect(bmp, 871, 441, 899, 469, makecol(255,255,255));
        rect(bmp, 872, 442, 898, 468, makecol(255,255,255));
    }
}
void boyut_secili_arac(){
    /**
    **********************
    Bu fonksiyonda boyut(int tipinde) değişkeni kontrol edilir.
    "boyut" degiskeni secili olan boyutu gosterir.
    Bu fonksiyonda ise boyut degiskeni kontrol edilir ve boyut hangisine esitse o boyutun secili oldugunu gostermek icin boyut aracinin kenarligi
    beyaz renk yapılır
    */
    if(boyut==1){
        rect(bmp,30,220,40,230,makecol(255,255,255));
        rect(bmp,31,221,39,229,makecol(255,255,255));
        rect(bmp,32,222,38,228,makecol(255,255,255));
    }
    else if(boyut==2){
        rect(bmp,25,235,45,255,makecol(255,255,255));
        rect(bmp,26,236,44,254,makecol(255,255,255));
        rect(bmp,27,237,43,253,makecol(255,255,255));
    }
    else if(boyut==3){
        rect(bmp,20,260,50,290,makecol(255,255,255));
        rect(bmp,21,261,49,289,makecol(255,255,255));
        rect(bmp,22,262,48,288,makecol(255,255,255));
    }
    else if(boyut==4){
        rect(bmp,15,295,55,335,makecol(255,255,255));
        rect(bmp,16,296,54,334,makecol(255,255,255));
        rect(bmp,17,297,53,333,makecol(255,255,255));
    }
}


int main() {

    ekran_ayarlar();  ///bu fonksiyon ekrani olusturur. klavyeyi, fareyi, zamanlayiciyi yukler.
	bmp=create_bitmap(920,625);  ///yeni bitmap olusturuluyor.
	show_mouse(screen);  ///farenin ekranda gosterilmesi saglandi.
    ekran_yukle();   /// olusturdugumuz grafik ekranin arkaplani olusturur. Cizim alanini cizer.
    secilen_renk=makecol(0,0,0);
    secilen_renk_2=makecol(255,255,255);
    menu_resim_yukle();  ///menu ikonlari yuklenir.

	while (!key[KEY_ESC])
    {
        acquire_screen(); ///cizim kodlarimizi acquire_screen() - release_screen() fonksiyonlari arasina yazmaliyiz.
                          ///aksi halde cizimlerimizde farkedilmeyecek hatalar olusabilir.

        blit(bmp, screen, 0, 0, 0, 0, 920, 625); ///bmp degiskenine koordinatlari belirtilen yerleri(x1,x2,y1,y2) kopyalar.
        textprintf_ex(screen ,font ,865, 580, makecol( 0, 0, 0) ,makecol(195, 195, 195) ,"x: %d", mouse_x);
        textprintf_ex(screen ,font ,865, 600, makecol( 0, 0, 0) ,makecol(195, 195, 195) ,"y: %d", mouse_y);
        mesaj();

        textout_ex(screen ,font , "Emre Kiziltepe" ,680, 595,makecol(0,0,0),makecol(195, 195, 195));
        textout_ex(screen ,font , "Murat Karakoc" ,680, 610,makecol(0,0,0),makecol(195, 195, 195));

        panel_yukle();
        alt_panel_secili_arac();
        renk_secili_arac();
        boyut_secili_arac();

        release_screen();///cizim kodlarimizi acquire_screen() - release_screen() fonksiyonlari arasina yazmaliyiz.
                        ///aksi halde cizimlerimizde farkedilmeyecek hatalar olusabilir.


        if((mouse_x>70) && (mouse_x<850) && (mouse_y>0) && (mouse_y<555) ){
            ciz();
        }
        else if((mouse_x>870) && (mouse_x<900) && (mouse_y>80) && (mouse_y<470)){
            renk_sec();
        }
        else if((mouse_x>0) && (mouse_x<70) && (mouse_y>210) && (mouse_y<625)){
            arac_sec_sol();
        }
        else if((mouse_x>70) && (mouse_x<630) && (mouse_y>555) && (mouse_y<625) ){
            arac_sec_alt();
        }
        else if((mouse_x>0) && (mouse_x<70) && (mouse_y>0) && (mouse_y<210) ){
            menu_sec();
        }
        else if((mouse_x>850) && (mouse_x<920) && (mouse_y>0) && (mouse_y<70) && (mouse_b==1)){
            exit(-1); ///CIKIS
        }
    }
	clear_keybuf();  ///klavye gecmisini siler.
	return 0;
}
END_OF_MAIN() ///allegroya ozgu fonksiyon. main fonksiyonu bitisiginde cagrilmasi gerekir.

void ekran_ayarlar() {
	int ekran_derinlik, mod;
	allegro_init();                                                 /// Bu fonsiyon klavye ile ilgili fonksiyonlari barindirir.
	ekran_derinlik = desktop_color_depth();                         /// desktop_color_depth fonksiyonu ekran derinligini verir.
	if (ekran_derinlik == 0) ekran_derinlik = 32;                   /// ekran derinligi degeri 32 olarak belirlendi.
	set_color_depth(ekran_derinlik);                                /// piksel renk derinligini 32(ekran_Derinlik) olarak ayarlar.
	mod = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 920, 625, 0, 0);    ///set_gfx_mode() ekran boyutunu ayarlar.
                                                                    ///GFX_AUTODETECT_WINDOWED pencerenin tam ekran olmamasini saglar.

	if (mod != 0) {                         /// ekran acilamiyorsa anlaminda.
		allegro_message(allegro_error);     /// hata mesaji gosterir.
		exit(-1);                           /// pencereyi kapatir.
	}
	install_timer();            ///zamanlayiciyi kullanilabilir hale getirir.
	install_keyboard();         ///klavyeyi kullanilabilir hale getirir.
	install_mouse();            ///fareyi kullanilabilir hale getirir.
	set_window_title("CAINT");  ///grafik penceresinin ismini belirtir.
}
void ekran_yukle(){

    clear_to_color(bmp,makecol(195,195,195));  /// olusturdugumuz grafik ekranin arkaplani degistirir.
    rectfill(bmp,70,0,850,555,makecol(255,255,255)); ///cizim ekranini olusturur.
    menu_resim_yukle();
    renk_secili_arac();
    arac=1;
}
void panel_yukle(){

    rectfill(bmp,0,0,70,625,makecol(195,195,195));
    rectfill(bmp,70,555,920,625,makecol(195,195,195));
    rectfill(bmp,850,0,920,625,makecol(195,195,195));
    ///SOL PANEL
    //menu_resim_yukle();
    blit(res_yeni,bmp,0,0,10,10,50,50);  ///yeni butonu
    hline(bmp,0,70,70,makecol(0,0,0));
    blit(res_kaydet,bmp,0,0,10,80,50,50);  ///kaydet butonu
    hline(bmp,0,140,70,makecol(0,0,0));
    blit(res_ac,bmp,0,0,10,150,50,50);  ///ac butonu
    hline(bmp,0,210,70,makecol(0,0,0));
    //KALINLIK
    rectfill(bmp,30,220,40,230,makecol(0,0,0)); /// boyut 1.derece
    rectfill(bmp,25,235,45,255,makecol(0,0,0)); /// boyut 2.derece
    rectfill(bmp,20,260,50,290,makecol(0,0,0)); /// boyut 3.derece
    rectfill(bmp,15,295,55,335,makecol(0,0,0)); /// boyut 4.derece
    //********
    hline(bmp,0,345,70,makecol(0,0,0));

    blit(res_kalem,bmp,0,0,10,355,50,50); ///kalem butonu
    hline(bmp,0,415,70,makecol(0,0,0));
    blit(res_silgi,bmp,0,0,10,425,50,50);  ///silgi butonu
    hline(bmp,0,485,70,makecol(0,0,0));
    blit(res_renkdoldur,bmp,0,0,10,495,50,50);  ///renk kutusu buton
    hline(bmp,0,555,920,makecol(0,0,0));
    blit(res_renksec,bmp,0,0,10,565,50,50);  ///renk secici buton
    ///*********

    vline(bmp,70,0,680,makecol(0,0,0));///SOL PANEL DIKEY CIZGI


    ///ALT PANEL
    rectfill(bmp,80,590,140,595,makecol(0,0,0));
    vline(bmp,150,555,625,makecol(0,0,0));

    rect(bmp,160,565,220,615,makecol(0,0,0));  ///ici bos dikdortgen
    rect(bmp,161,566,219,614,makecol(0,0,0));  ///ici bos dikdortgen
    rect(bmp,162,567,218,613,makecol(0,0,0));  ///ici bos dikdortgen
    vline(bmp,230,555,625,makecol(0,0,0));
    rectfill(bmp,240,565,300,615,makecol(0,0,0));  ///ici dolu dikdortgen
    vline(bmp,310,555,625,makecol(0,0,0));
    circle(bmp,350,590,30,makecol(0,0,0));  ///cember
    vline(bmp,390,555,625,makecol(0,0,0));
    circlefill(bmp,430,590,30,makecol(0,0,0));  ///daire
    vline(bmp,470,555,625,makecol(0,0,0));
    line(bmp,480,615,540,615,makecol(0,0,0)); ///ucgen alt cizgi
    line(bmp,510,565,480,615,makecol(0,0,0)); ///ucgen sol cizgi
    line(bmp,510,565,540,615,makecol(0,0,0)); ///ucgen sag cizgi
    vline(bmp,550,555,625,makecol(0,0,0));
    triangle(bmp,590,565,560,615,620,615, makecol(0,0,0)); ///ici dolu ucgen
    vline(bmp,630,555,625,makecol(0,0,0));

    ///*********

    ///SAG PANEL
    blit(res_cikis,bmp,0,0,860,10,50,50);  ///cikis butonu
    vline(bmp,850,0,625,makecol(0,0,0));
    hline(bmp,850,70,920,makecol(0,0,0));

    rectfill(bmp, 870, 80, 900, 110, makecol(255,255,255));///beyaz
    rectfill(bmp, 870, 120, 900, 150, makecol(255,0,0));///kirmizi
    rectfill(bmp, 870, 160, 900, 190, makecol(0,255,0));///acik yesil
    rectfill(bmp, 870, 200, 900, 230, makecol(0,0,255));///lacivert
    rectfill(bmp, 870, 240, 900, 270, makecol(240,240,0));///sari
    rectfill(bmp, 870, 280, 900, 310, makecol(255,0,255));///pembe
    rectfill(bmp, 870, 320, 900, 350, makecol(75,150,20));///kapali yesil
    rectfill(bmp, 870, 360, 900, 390, makecol(225,100,20));///turuncu
    rectfill(bmp, 870, 400, 900, 430, makecol(0,0,0));///siyah
    rectfill(bmp, 870, 440, 900, 470, makecol(25,150,200));///mavi

    rectfill(bmp, 860, 485, 900, 525, secilen_renk_2);///alt renk
    rectfill(bmp, 870, 495, 910, 535, secilen_renk);///ustrenk
    ///*********
}
void mesaj(){
    ///mesaj2 degiskeni daha once resmin kaydedilip kaydedilmedigini tutar.
    if(mesaj2!="Henuz resim kaydetmediniz!")
        textprintf_ex(screen ,font ,640,570, makecol( 0, 0, 0) ,makecol(195, 195, 195) ,"Mesaj : %s", mesaj2);
    else if(mesaj2=="Henuz resim kaydetmediniz!"){
        textout_ex(screen ,font,"Mesaj : Henüz resim",640,570, makecol( 0, 0, 0) ,makecol(195, 195, 195));
        textout_ex(screen ,font,"kaydetmediniz!",640,580, makecol( 0, 0, 0) ,makecol(195, 195, 195));
    }
}
void ciz(){
    /**
    Ciz fonksiyonu secili olan aracin cizim alanina cizim yapmasini saglar.
    */
    if(mouse_b!=1)
    {
        x3=-1;
        y3=-1;
    }
    else if(mouse_b==1){
        if(arac==1){
            ///KALEM
            if(boyut==1){
                if (x3 != -1 || y3 != -1){
                for(int i = -1; i < 3; i++)
                for(int j = -1; j < 3; j++)
                    line(bmp,x3+i, y3+j, mouse_x+i,mouse_y+j,secilen_renk);
                }
                x3 = mouse_x;
                y3 = mouse_y;
            }
            else if(boyut==2){
                if (x3 != -1 || y3 != -1){
                for (int i = -1; i < 6; i++)
                for(int j = -1; j < 6; j++)
                    line(bmp,x3+i, y3+j, mouse_x+i,mouse_y+j,secilen_renk);
                }
                x3 = mouse_x;
                y3 = mouse_y;
            }
            else if(boyut==3){
                if (x3 != -1 || y3 != -1){
                for (int i = -1; i < 9; i++)
                for(int j = -1; j < 9; j++)
                    line(bmp,x3+i, y3+j, mouse_x+i,mouse_y+j,secilen_renk);
                }
                x3 = mouse_x;
                y3 = mouse_y;
            }
            else if(boyut==4){
                if (x3 != -1 || y3 != -1){
                for (int i = -1; i < 12; i++)
                for(int j = -1; j < 12; j++)
                    line(bmp,x3+i, y3+j, mouse_x+i,mouse_y+j,secilen_renk);
                }
                x3 = mouse_x;
                y3 = mouse_y;
            }
        }
        else if(arac==3){
            ///SILGI
            if(boyut==1)
                rectfill(bmp,mouse_x-5,mouse_y-5,mouse_x+5,mouse_y+5,secilen_renk_2);
            else if(boyut==2)
                rectfill(bmp,mouse_x-10,mouse_y-10,mouse_x+10,mouse_y+10,secilen_renk_2);
            else if(boyut==3)
                rectfill(bmp,mouse_x-20,mouse_y-20,mouse_x+20,mouse_y+20,secilen_renk_2);
            else if(boyut==4)
                rectfill(bmp,mouse_x-30,mouse_y-30,mouse_x+30,mouse_y+30,secilen_renk_2);
        }
        else if(arac==4){
            ///DOLDUR
            floodfill(bmp, mouse_x, mouse_y, secilen_renk);
        }
        else if(arac==5){
            ///RENK AL
            secilen_renk=getpixel(bmp,mouse_x,mouse_y);
            rectfill(bmp, 870, 495, 910, 535, secilen_renk);
        }
        else if(arac==6){
            ///CIZGI
            xx1=mouse_x;
            yy1=mouse_y;
            while(1){
                if(mouse_b!=1){
                    xx2=mouse_x;
                    yy2=mouse_y;
                    break;
                }
            }
            line(bmp,xx1,yy1,xx2,yy2,secilen_renk);
        }
        else if(arac==7){
            ///ICI BOS KARE
            xx1=mouse_x;
            yy1=mouse_y;
            while(1){
                if(mouse_b!=1){
                    xx2=mouse_x;
                    yy2=mouse_y;
                    break;
                }
            }
            if(boyut==1){
                rect(bmp,xx1,yy1,xx2,yy2,secilen_renk);
                rect(bmp,xx1+1,yy1+1,xx2-1,yy2-1,secilen_renk);
            }
            else if(boyut==2){
                rect(bmp,xx1,yy1,xx2,yy2,secilen_renk);
                rect(bmp,xx1+1,yy1+1,xx2-1,yy2-1,secilen_renk);
                rect(bmp,xx1+2,yy1+2,xx2-2,yy2-2,secilen_renk);
            }
            else if(boyut==3){
                rect(bmp,xx1,yy1,xx2,yy2,secilen_renk);
                rect(bmp,xx1+1,yy1+1,xx2-1,yy2-1,secilen_renk);
                rect(bmp,xx1+2,yy1+2,xx2-2,yy2-2,secilen_renk);
                rect(bmp,xx1+3,yy1+3,xx2-3,yy2-3,secilen_renk);
            }
            else if(boyut==4){
                rect(bmp,xx1,yy1,xx2,yy2,secilen_renk);
                rect(bmp,xx1+1,yy1+1,xx2-1,yy2-1,secilen_renk);
                rect(bmp,xx1+2,yy1+2,xx2-2,yy2-2,secilen_renk);
                rect(bmp,xx1+3,yy1+3,xx2-3,yy2-3,secilen_renk);
                rect(bmp,xx1+4,yy1+4,xx2-4,yy2-4,secilen_renk);
            }
        }
        else if(arac==8){
            ///ICI DOLU KARE
            xx1=mouse_x;
            yy1=mouse_y;
            while(1){
                if(mouse_b!=1){
                    xx2=mouse_x;
                    yy2=mouse_y;
                    break;
                }
            }
            rectfill(bmp,xx1,yy1,xx2,yy2,secilen_renk);
        }
        else if(arac==9){
            ///ICI BOS DAIRE
            xx1=mouse_x;
            yy1=mouse_y;
            while(1){
                if(mouse_b!=1){
                    xx2=mouse_x;
                    yy2=mouse_y;
                    break;
                }
            }
            circle(bmp,(xx1+xx2)/2,(yy1+yy2)/2,sqrt(pow((xx2-xx1)/2,2)+pow((yy2-yy1)/2,2)),secilen_renk);
        }
        else if(arac==10){
            ///ICI DOLU DAIRE
            xx1=mouse_x;
            yy1=mouse_y;
            while(1){
                if(mouse_b!=1){
                    xx2=mouse_x;
                    yy2=mouse_y;
                    break;
                }
            }
            circlefill(bmp,(xx1+xx2)/2,(yy1+yy2)/2,sqrt(pow((xx2-xx1)/2,2)+pow((yy2-yy1)/2,2)),secilen_renk);
        }
        else if(arac==11){
            ///ICI BOS UCGEN
            xx1=mouse_x;
            yy1=mouse_y;
            while(1){
                if(mouse_b!=1){
                    xx2=mouse_x;
                    yy2=mouse_y;
                    break;
                }
            }
            line(bmp,xx1,yy1,xx2,yy2,secilen_renk);
            line(bmp,xx1,yy1,(xx1+(xx1-xx2)),yy2,secilen_renk);
            line(bmp,xx2,yy2,(xx1+(xx1-xx2)),yy2,secilen_renk);
        }
        else if(arac==12){
            ///ICI DOLU UCGEN
            xx1=mouse_x;
            yy1=mouse_y;
            while(1){
                if(mouse_b!=1){
                    xx2=mouse_x;
                    yy2=mouse_y;
                    break;
                }
            }
            triangle(bmp,xx1,yy1,xx2,yy2,(xx1-(xx2-xx1)),yy2,secilen_renk);
        }
        panel_yukle();
    }
}
void renk_sec(){

    /**
    Bu fonksiyon secilen rengi kontrol eder.
    eger fare sol tiksa secilen rengin renk kodunu "secilen_renk" degiskenine aktarir.
    eger fare sag tiksa secilen rengin renk kodunu "secilen_renk_2" degiskenine aktarir.
    tıksa secilen rengin ifadesi "str_secili_renk" degiskenine aktarilir.
     */


    if((mouse_x>870) && (mouse_x<900) && (mouse_y>80) && (mouse_y<110)){
        ///BEYAZ
        rect(bmp, 870, 80, 900, 110, makecol(0,0,0));
        rect(bmp, 871, 81, 899, 109, makecol(0,0,0));
        rect(bmp, 872, 82, 898, 108, makecol(0,0,0));
        if(mouse_b==1){
            str_secili_renk="beyaz";
            secilen_renk=makecol(255,255,255);
        }
        else if(mouse_b==2){
            secilen_renk_2=makecol(255,255,255);
        }
    }
    else if((mouse_x>870) && (mouse_x<900) && (mouse_y>120) && (mouse_y<150)){
        ///KIRMIZI
        rect(bmp, 870, 120, 900, 150, makecol(255,255,255));
        rect(bmp, 871, 121, 899, 149, makecol(255,255,255));
        rect(bmp, 872, 122, 898, 148, makecol(255,255,255));
        if(mouse_b==1){
            str_secili_renk="kirmizi";
            secilen_renk=makecol(255,0,0);
        }
        else if(mouse_b==2){
            secilen_renk_2=makecol(255,0,0);
        }
    }
    else if((mouse_x>870) && (mouse_x<900) && (mouse_y>160) && (mouse_y<190)){
        ///ACIK YESIL
        rect(bmp, 870, 160, 900, 190, makecol(255,255,255));
        rect(bmp, 871, 161, 899, 189, makecol(255,255,255));
        rect(bmp, 872, 162, 898, 188, makecol(255,255,255));
        if(mouse_b==1){
            str_secili_renk="acik_yesil";
            secilen_renk=makecol(0,255,0);
        }
        else if(mouse_b==2){
            secilen_renk_2=makecol(0,255,0);
        }
    }
    else if((mouse_x>870) && (mouse_x<900) && (mouse_y>200) && (mouse_y<230)){
        ///LACIVERT
        rect(bmp, 870, 200, 900, 230, makecol(255,255,255));
        rect(bmp, 871, 201, 899, 229, makecol(255,255,255));
        rect(bmp, 872, 202, 898, 228, makecol(255,255,255));
        if(mouse_b==1){
            str_secili_renk="lacivert";
            secilen_renk=makecol(0,0,255);
        }
        else if(mouse_b==2){
            secilen_renk_2=makecol(0,0,255);
        }
    }
    else if((mouse_x>870) && (mouse_x<900) && (mouse_y>240) && (mouse_y<270)){
        ///SARI
        rect(bmp, 870, 240, 900, 270, makecol(255,255,255));
        rect(bmp, 871, 241, 899, 269, makecol(255,255,255));
        rect(bmp, 872, 242, 898, 268, makecol(255,255,255));
        if(mouse_b==1){
            str_secili_renk="sari";
            secilen_renk=makecol(240,240,0);
        }
        else if(mouse_b==2){
            secilen_renk_2=makecol(240,240,0);
        }
    }
    else if((mouse_x>870) && (mouse_x<900) && (mouse_y>280) && (mouse_y<310)){
        ///PEMPE
        rect(bmp, 870, 280, 900, 310, makecol(255,255,255));
        rect(bmp, 871, 281, 899, 309, makecol(255,255,255));
        rect(bmp, 872, 282, 898, 308, makecol(255,255,255));
        if(mouse_b==1){
            str_secili_renk="pembe";
            secilen_renk=makecol(255,0,255);
        }
        else if(mouse_b==2){
            secilen_renk_2=makecol(255,0,255);
        }
    }
    else if((mouse_x>870) && (mouse_x<900) && (mouse_y>320) && (mouse_y<350)){
        ///KOYU YESIL
        rect(bmp, 870, 320, 900, 350, makecol(255,255,255));
        rect(bmp, 871, 321, 899, 349, makecol(255,255,255));
        rect(bmp, 872, 322, 898, 348, makecol(255,255,255));
        if(mouse_b==1){
            str_secili_renk="koyu_yesil";
            secilen_renk=makecol(75,150,20);
        }
        else if(mouse_b==2){
            secilen_renk_2=makecol(75,150,20);
        }
    }
    else if((mouse_x>870) && (mouse_x<900) && (mouse_y>360) && (mouse_y<390)){
        ///KAHVERENGI
        rect(bmp, 870, 360, 900, 390, makecol(255,255,255));
        rect(bmp, 871, 361, 899, 389, makecol(255,255,255));
        rect(bmp, 872, 362, 898, 388, makecol(255,255,255));
        if(mouse_b==1){
            str_secili_renk="kahverengi";
            secilen_renk=makecol(225,100,20);
        }
        else if(mouse_b==2){
            secilen_renk_2=makecol(225,100,20);
        }
    }
    else if((mouse_x>870) && (mouse_x<900) && (mouse_y>400) && (mouse_y<430)){
        ///SIYAH
        rect(bmp, 870, 400, 900, 430, makecol(255,255,255));
        rect(bmp, 871, 401, 899, 429, makecol(255,255,255));
        rect(bmp, 872, 402, 898, 428, makecol(255,255,255));
        if(mouse_b==1){
            str_secili_renk="siyah";
            secilen_renk=makecol(0,0,0);
        }
        else if(mouse_b==2){
            secilen_renk_2=makecol(0,0,0);
        }
    }
    else if((mouse_x>870) && (mouse_x<900) && (mouse_y>440) && (mouse_y<470)){
        ///MAVI
        rect(bmp, 870, 440, 900, 470, makecol(255,255,255));
        rect(bmp, 871, 441, 899, 469, makecol(255,255,255));
        rect(bmp, 872, 442, 898, 468, makecol(255,255,255));
        if(mouse_b==1){
            str_secili_renk="mavi";
            secilen_renk=makecol(25,150,200);
        }
        else if(mouse_b==2){
            secilen_renk_2=makecol(25,150,200);
        }
    }
}
void arac_sec_sol(){

    /**
    Bu fonksiyon araclarin uzerine geldiginde kullaniciya gostermek icin farenin uzerinde oldugu araca kenarlik ekler.
    Secilen araci "arac" degiskenine aktarir.
    Secilen boyutu boyut degiskenine aktarir.
    */

    if((mouse_x>0) && (mouse_x<70) && (mouse_y>210) && (mouse_y<345)){
        ///BOYUT SECIM
        if((mouse_x>30) && (mouse_x<40) && (mouse_y>220) && (mouse_y<230))
        {
            rect(bmp,30,220,40,230,makecol(255,255,255));
            rect(bmp,31,221,39,229,makecol(255,255,255));
            rect(bmp,32,222,38,228,makecol(255,255,255));
            if(mouse_b==1){
                boyut=1;
            }
        }
        else if((mouse_x>25) && (mouse_x<45) && (mouse_y>235) && (mouse_y<255))
        {
            rect(bmp,25,235,45,255,makecol(255,255,255));
            rect(bmp,26,236,44,254,makecol(255,255,255));
            rect(bmp,27,237,43,253,makecol(255,255,255));
            if(mouse_b==1){
                boyut=2;
            }
        }
        else if((mouse_x>20) && (mouse_x<50) && (mouse_y>260) && (mouse_y<290))
        {
            rect(bmp,20,260,50,290,makecol(255,255,255));
            rect(bmp,21,261,49,289,makecol(255,255,255));
            rect(bmp,22,262,48,288,makecol(255,255,255));
            if(mouse_b==1){
                boyut=3;
            }
        }
        else if((mouse_x>15) && (mouse_x<55) && (mouse_y>295) && (mouse_y<335))
        {
            rect(bmp,15,295,55,335,makecol(255,255,255));
            rect(bmp,16,296,54,334,makecol(255,255,255));
            rect(bmp,17,297,53,333,makecol(255,255,255));
            if(mouse_b==1){
                boyut=4;
            }
        }
    }
    else if((mouse_x>0) && (mouse_x<70) && (mouse_y>345) && (mouse_y<415)){
        ///KALEM
        rect(bmp,0,345,70,415,makecol(25,150,200));
        rect(bmp,1,346,69,414,makecol(25,150,200));
        rect(bmp,2,347,68,413,makecol(25,150,200));
        if(mouse_b==1){
            str_secili_arac="kalem";
            arac=1;
        }
    }
    else if((mouse_x>0) && (mouse_x<70) && (mouse_y>415) && (mouse_y<485)){
        ///SILGI
        rect(bmp,0,415,70,485,makecol(25,150,200));
        rect(bmp,1,416,69,484,makecol(25,150,200));
        rect(bmp,2,417,68,483,makecol(25,150,200));
        if(mouse_b==1){
            str_secili_arac="silgi";
            arac=3;
        }
    }
    else if((mouse_x>0) && (mouse_x<70) && (mouse_y>485) && (mouse_y<555)){
        ///RENK DOLDUR
        rect(bmp,0,485,70,555,makecol(25,150,200));
        rect(bmp,1,486,69,554,makecol(25,150,200));
        rect(bmp,2,487,68,553,makecol(25,150,200));
        if(mouse_b==1){
            str_secili_arac="doldur";
            arac=4;
        }
    }
    else if((mouse_x>0) && (mouse_x<70) && (mouse_y>555) && (mouse_y<625)){
        ///RENK AL
        rect(bmp,0,555,70,625,makecol(25,150,200));
        rect(bmp,1,556,68,624,makecol(25,150,200));
        rect(bmp,2,557,69,623,makecol(25,150,200));
        if(mouse_b==1){
            str_secili_arac="renk_al";
            arac=5;
        }
    }
}
void arac_sec_alt(){

    /**
    Bu fonksiyon araclarin uzerine geldiginde kullaniciya gostermek icin farenin uzerinde oldugu araca kenarlik ekler veya arkaplanini beyaza boyar.
    Secilen araci "arac" degiskenine aktarir.
    */

    if((mouse_x>70) && (mouse_x<150) && (mouse_y>555) && (mouse_y<625)){
        ///CIZGI
        rectfill(bmp,80,590,140,595,makecol(255,255,255));
        if(mouse_b==1){
            str_secili_arac="cizgi";
            arac=6;
        }
    }

    else if((mouse_x>150) && (mouse_x<230) && (mouse_y>555) && (mouse_y<625)){
        ///DIKDORTGEN ICI BOS
        rect(bmp,160,565,220,615,makecol(255,255,255));
        rect(bmp,161,566,219,614,makecol(255,255,255));
        rect(bmp,162,567,218,613,makecol(255,255,255));
        if(mouse_b==1){
            str_secili_arac="dikdortgen_ici_bos";
            arac=7;
        }
    }
    else if((mouse_x>230) && (mouse_x<310) && (mouse_y>555) && (mouse_y<625)){
        ///DIKDORTGEN ICI DOLU
        rectfill(bmp,240,565,300,615,makecol(255,255,255));
        if(mouse_b==1){
            str_secili_arac="dikdortgen_ici_dolu";
            arac=8;
        }
    }
    else if((mouse_x>310) && (mouse_x<390) && (mouse_y>555) && (mouse_y<625)){
        ///DAIRE ICI BOS
        circle(bmp,350,590,30,makecol(255,255,255));
        if(mouse_b==1){
            str_secili_arac="daire_ici_bos";
            arac=9;
        }
    }
    else if((mouse_x>390) && (mouse_x<470) && (mouse_y>555) && (mouse_y<625)){
        ///DAIRE ICI DOLU
        circlefill(bmp,430,590,30,makecol(255,255,255));
        if(mouse_b==1){
            str_secili_arac="daire_ici_dolu";
            arac=10;
        }
    }
    else if((mouse_x>470) && (mouse_x<550) && (mouse_y>555) && (mouse_y<625)){
        ///UCGEN ICI BOS
        line(bmp,480,615,540,615,makecol(255,255,255));//alt cizgi
        line(bmp,510,565,480,615,makecol(255,255,255));//sol
        line(bmp,510,565,540,615,makecol(255,255,255));//sag
        if(mouse_b==1){
            str_secili_arac="ucgen_ici_bos";
            arac=11;
        }
    }
    else if((mouse_x>550) && (mouse_x<630) && (mouse_y>555) && (mouse_y<625)){
        ///UCGEN ICI DOLU
        triangle(bmp,590,565,560,615,620,615, makecol(255,255,255));
        if(mouse_b==1){
            str_secili_arac="ucgen_ici_dolu";
            arac=12;
        }
    }
}
void menu_sec(){

    /**
    Bu fonksiyon araclarin uzerine geldiginde kullaniciya gostermek icin farenin uzerinde oldugu araca mavi kenarlik ekler.
    Secilen araci "arac" degiskenine aktarir.
    */

        if((mouse_x>0) && (mouse_x<70) && (mouse_y>0) && (mouse_y<70)){
            ///YENI
            rect(bmp,0,0,70,70,makecol(25,150,200));
            rect(bmp,1,1,69,69,makecol(25,150,200));
            rect(bmp,2,3,68,68,makecol(25,150,200));
            if(mouse_b==1){
                clear_bitmap(bmp); ///bmp bitmap degiskenini temizler.
                ekran_yukle();
                show_mouse(screen);  ///farenin ekranda gosterilmesini saglar.
                boyut=1;
                str_secili_renk="siyah";
                str_secili_arac="kalem";
                secilen_renk=makecol(0,0,0);
                mesaj2="Yeni sayfa açıldı.";
            }
        }
        else if((mouse_x>0) && (mouse_x<70) && (mouse_y>70) && (mouse_y<140)){
            ///KAYDET
            rect(bmp,0,70,70,140,makecol(25,150,200));
            rect(bmp,1,71,69,139,makecol(25,150,200));
            rect(bmp,2,72,68,138,makecol(25,150,200));
            if(mouse_b==1){
                str_secili_arac="kaydet";
                res_kayit = create_sub_bitmap(bmp, 70, 0, 780, 555);  ///"bmp" bitmap degiskenine yeni bir bitmap olusturur.
                save_bmp("image.bmp",res_kayit,pal);  ///"res_kayit" bitmap'ini kaydeder.
                boyut=1;
                str_secili_renk="siyah";
                str_secili_arac="kalem";
                secilen_renk=makecol(0,0,0);
                mesaj2="Resim kaydedildi.";
            }
        }
        else if((mouse_x>0) && (mouse_x<70) && (mouse_y>140) && (mouse_y<210)){
            ///AC
            rect(bmp,0,140,70,210,makecol(25,150,200));
            rect(bmp,1,141,69,209,makecol(25,150,200));
            rect(bmp,2,142,68,208,makecol(25,150,200));
            if(mouse_b==1){
                if(load_bitmap("image.bmp", NULL)){
                    str_secili_arac="ac";
                    blit((load_bitmap("image.bmp", NULL)), bmp, 0, 0, 70, 0, 850, 555); ///bitmap uzantılı resmi diger bitmap'e kopyalar.
                    boyut=1;
                    str_secili_renk="siyah";
                    str_secili_arac="kalem";
                    secilen_renk=makecol(0,0,0);
                    mesaj2="Resim açıldı.";
                }
                else{
                    mesaj2="Henuz resim kaydetmediniz!";
                }
            }
        }
}
void menu_resim_yukle(){
    res_yeni=load_bitmap("yeni.bmp",NULL);  ///yeni ikonu bitmap degiskene aktarildi.
    res_kaydet=load_bitmap("kaydet.bmp",NULL); ///kaydet ikonu bitmap degiskene aktarildi.
    res_ac=load_bitmap("ac.bmp",NULL); ///ac ikonu bitmap degiskene aktarildi.
    res_kalem=load_bitmap("kalem.bmp",NULL); ///kalem ikonu bitmap degiskene aktarildi.
    res_cikis=load_bitmap("cikis.bmp",NULL); ///cikis ikonu bitmap degiskene aktarildi.
    res_silgi=load_bitmap("silgi.bmp",NULL); ///silgi ikonu bitmap degiskene aktarildi.
    res_renkdoldur=load_bitmap("renkdoldur.bmp",NULL); ///renkdoldur ikonu bitmap degiskene aktarildi.
    res_renksec=load_bitmap("renksec.bmp",NULL); ///renksec ikonu bitmap degiskene aktarildi.
}


