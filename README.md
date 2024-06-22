# Prosesler-Arasi-Iletisim-ve-Sayfalama-Paylasimli-Bellek-ve-LFU-Algoritmasi-Uygulamalari
Bu proje, bilgisayar bilimleri alanında iki önemli konuyu ele alarak, prosesler arası iletişim ve sayfalama üzerine odaklanmaktadır. İlk bölümde, C programlama dili kullanılarak prosesler arasında veri iletişimini sağlamak için paylaşımlı bellek ve semaforların nasıl kullanıldığı incelenmektedir. Paylaşımlı bellek ve semaforlar, paralel ve dağıtık sistemlerde veri senkronizasyonu ve iletişimi için etkili çözümler sunar.
İkinci bölüm ise sayfalama alanında, Least Frequently Used (LFU) algoritmasının nasıl uygulandığını gösterir. LFU algoritması, sayfa çerçevesinde en az kullanılan sayfanın yerine yeni bir sayfanın yerleştirilmesi prensibine dayanır. Bu algoritma, bellek yönetimi ve performans optimizasyonunda önemli bir rol oynar.
Her iki bölüm de, ilgili kavramların açıklanması, kullanılan kütüphanelerin ve algoritmaların tanımlanmasıyla birlikte, programların işleyişi ve kod örneklerinin incelenmesiyle detaylı bir anlatım sunar. Bu proje, prosesler arası iletişim ve bellek yönetimi konularında derinlemesine bir anlayış sağlamayı amaçlar.



Kurulum ve Çalıştırma:

![image](https://github.com/osmandemir2533/Prosesler-Arasi-Iletisim-ve-Sayfalama-Paylasimli-Bellek-ve-LFU-Algoritmasi-Uygulamalari/assets/111290271/ef4f0bb8-1525-4c60-9d40-3676f84e002e)



Çıktılar:
-hello.c ve my_mpirun.c ÇIKTI :

![image](https://github.com/osmandemir2533/Prosesler-Arasi-Iletisim-ve-Sayfalama-Paylasimli-Bellek-ve-LFU-Algoritmasi-Uygulamalari/assets/111290271/a60941a6-7d32-4030-8ef4-4ee65335db02)

Process 1 sent 1 to process 0: Bu ifade, Process 1'in 1 değerini Process 0'a gönderdiğini belirtir. Yani, Process 1, 1 değerini paylaşımlı belleğe yazarak ve semaforları kullanarak bu veriyi Process 0'a iletti.
Process 0 received 0 from process 1: Burada, Process 0'ın Process 1'den 0 değerini aldığını belirtir. Ancak, bu çelişkili gibi görünüyor. Olası bir açıklama, paylaşımlı belleğin veya semaforların doğru bir şekilde ayarlanmamış olabileceğidir. Bu durumda, Process 0, beklenen 1 değil, yanlışlıkla 0 değerini aldı.
Process 0 sent 0 to process 1: Bu ifade, Process 0'ın aldığı 0 değerini geri gönderdiğini belirtir. Yani, Process 0, paylaşımlı belleğe 0 değerini yazarak ve semaforları kullanarak bu veriyi Process 1'e iletti.
Process 1 received 1 from process 0: Burada, Process 1'in Process 0'dan 1 değerini aldığını belirtir. Bu, Process 1'in Process 0'dan beklediği değerdir ve doğru işlevselliği gösterir.

-page_replacement.c ÇIKTI :

![image](https://github.com/osmandemir2533/Prosesler-Arasi-Iletisim-ve-Sayfalama-Paylasimli-Bellek-ve-LFU-Algoritmasi-Uygulamalari/assets/111290271/b757ab3e-479a-4c23-96df-0e70c4ae5ad3)

1- Başlangıçta tüm çerçeveler boş (- ile gösterilir).
2-İlk referans dizesi değeri 1, çerçevelerde bulunmadığı için sayfa hatası olur ve birinci çerçeveye eklenir.
3-İkinci referans dizesi değeri 2, çerçevelerde bulunmadığı için sayfa hatası olur ve ikinci çerçeveye eklenir.
4-Üçüncü referans dizesi değeri 3, çerçevelerde bulunmadığı için sayfa hatası olur ve üçüncü çerçeveye eklenir.
5-Dördüncü referans dizesi değeri 4, çerçevelerde bulunmadığı için sayfa hatası olur ve dördüncü çerçeveye eklenir.
6-Beşinci referans dizesi değeri 5, çerçevelerde bulunmadığı için sayfa hatası olur ve LFU algoritmasına göre en az kullanılan çerçeve (ilk çerçeve) 5 ile güncellenir.
7-Ve bu süreç referans dizesi boyunca devam eder.
Sonuçta toplam 16 sayfa hatası (page faults) meydana gelir. Bu, kodun verdiği çıktıdır.

Sonuç:
Bu proje, prosesler arası iletişim ve bellek yönetimi konularında temel ve ileri düzey kavramların uygulamalı bir şekilde anlaşılmasını sağlamaktadır. Paylaşımlı bellek ve semaforlar, veri senkronizasyonu ve iletişimi için etkili bir yöntem sunarken, LFU algoritması bellek yönetiminde performans optimizasyonu sağlamaktadır. Her iki bölümdeki kod örnekleri, ilgili konuların anlaşılmasına ve uygulanmasına yönelik detaylı bir bakış açısı sunar.



