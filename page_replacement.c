#include <stdio.h>
#include <stdlib.h>

// Sabitlerin tanımlanması
#define FRAME_SIZE 4  // Sayfa çerçevesi boyutu
#define REF_STRING_LENGTH 22  // Referans dizesinin uzunluğu

// Sayfa çerçevesi yapısının tanımlanması
typedef struct {
    int page_number;  // Sayfa numarası
    int counter;      // Sayfa kullanım sayacı (LFU algoritması için)
} PageFrame;

// Sayfa çerçevelerini başlangıç değerleriyle başlatan fonksiyon
void initialize_frames(PageFrame frames[]) {
    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i].page_number = -1;  // Sayfa numarası başlangıçta -1 olarak ayarlanır (boş çerçeve)
        frames[i].counter = 0;        // Sayfa kullanım sayacı sıfırlanır
    }
}

// Belirli bir sayfanın çerçevede olup olmadığını kontrol eden fonksiyon
int find_page(PageFrame frames[], int page) {
    for (int i = 0; i < FRAME_SIZE; i++) {
        if (frames[i].page_number == page) {
            return i;  // Sayfa çerçevesi bulunduğunda çerçevenin indeksini döndürür
        }
    }
    return -1;  // Sayfa çerçevesi bulunamazsa -1 döndürür
}

// Sayfa çerçevesindeki en az kullanılan sayfayı bulan fonksiyon (LFU algoritması için)
int find_lfu_page(PageFrame frames[]) {
    int min = 0;
    for (int i = 1; i < FRAME_SIZE; i++) {
        if (frames[i].counter < frames[min].counter) {
            min = i;  // Kullanım sayısı en az olan çerçevenin indeksini günceller
        }
    }
    return min;  // En az kullanılan sayfa çerçevesinin indeksini döndürür
}

// Sayfa çerçevelerini ekrana yazdıran fonksiyon
void print_frames(PageFrame frames[]) {
    for (int i = 0; i < FRAME_SIZE; i++) {
        if (frames[i].page_number != -1) {
            printf("%d ", frames[i].page_number);  // Dolu çerçevelerde sayfa numarasını yazdırır
        } else {
            printf("- ");  // Boş çerçeveleri '-' ile gösterir
        }
    }
    printf("\n");
}

// Sayfa yer değiştirme algoritması uygulayan fonksiyon
int page_replacement(int ref_string[], int ref_length) {
    PageFrame frames[FRAME_SIZE];
    initialize_frames(frames);  // Çerçeveleri başlangıç değerleriyle başlatır

    int page_faults = 0;  // Sayfa hatalarının sayacı

    for (int i = 0; i < ref_length; i++) {
        int page = ref_string[i];  // Referans dizesinden bir sayfa alır
        int index = find_page(frames, page);  // Sayfanın çerçevede olup olmadığını kontrol eder

        if (index == -1) {  // Sayfa çerçevede değilse
            page_faults++;  // Sayfa hatası sayacını artırır
            index = find_lfu_page(frames);  // LFU algoritmasıyla en az kullanılan sayfayı bulur
            frames[index].page_number = page;  // Çerçeveyi sayfa ile günceller
            frames[index].counter = 1;  // Kullanım sayacını 1 yapar (yeni sayfa eklendi)
        } else {  // Sayfa çerçevede ise
            frames[index].counter++;  // Kullanım sayacını artırır
        }

        print_frames(frames);  // Çerçeveleri ekrana yazdırır
    }

    return page_faults;  // Toplam sayfa hatalarını döndürür
}

// Ana fonksiyon
int main() {
    int ref_string[REF_STRING_LENGTH] = {1, 2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2};

    int page_faults = page_replacement(ref_string, REF_STRING_LENGTH);  // Sayfa yer değiştirme algoritmasını çağırır
    printf("Total page faults: %d\n", page_faults);  // Toplam sayfa hatalarını ekrana yazdırır

    return 0;
}
