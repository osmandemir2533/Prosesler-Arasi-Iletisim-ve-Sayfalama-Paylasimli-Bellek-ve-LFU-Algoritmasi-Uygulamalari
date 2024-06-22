	Kodların Derlenmesi ve Çalıştırılması
BÖLÜM 1-- PROCESSLER ARASI İLETİŞİM , PAYLAŞILAN HAFIZA VE SEMAFORLAR

my_mpirun ve hello programlarının derlenmesi ve çalıştırılması
1-)Aşağıdaki komutlarla my_mpirun ve hello programlarını derleyin:
--> gcc -o my_mpirun my_mpirun.c -lrt -lpthread
--> gcc -o hello hello.c -lrt -lpthread

2-)my_mpirun programını çalıştırarak hello programını çağırın:
-->./my_mpirun 2 ./hello



BÖLÜM 2-- SAYFALAMA

1-)Sayfa değiştirme algoritmasının derlenmesi ve çalıştırılması:
page_replacement.c dosyasını derleyin:
-->gcc -o page_replacement page_replacement.c

2-)Programı çalıştırın:
-->./page_replacement

	Bu adımları izleyerek projeyi başarıyla derleyebilir ve çalıştırabilirsiniz.
	Her bir programın çıktısını terminalde görülecektir.
