#include <stdio.h> // Standart input/output işlemleri için kütüphane
#include <stdlib.h> // Standart kütüphane
#include <unistd.h> // POSIX API'leri için kütüphane
#include <sys/mman.h> // Bellek eşleme işlemleri için kütüphane
#include <sys/stat.h> // Dosya durumları için kütüphane
#include <fcntl.h> // Dosya kontrol işlemleri için kütüphane
#include <semaphore.h> // Semaforlar için kütüphane
#include <sys/wait.h> // Proses bekleme işlemleri için kütüphane

#define SHM_NAME "shared_memory" // Paylaşımlı bellek adı tanımlama
#define SEM_FULL_NAME "/sem_full" // Dolu semaforu adı tanımlama
#define SEM_EMPTY_NAME "/sem_empty" // Boş semaforu adı tanımlama
#define SEM_MUTEX_NAME "/sem_mutex" // Mutex semaforu adı tanımlama
#define BUFFER_SIZE 10 // Paylaşımlı bellek tampon boyutunu tanımlama

int main(int argc, char *argv[]) {
    // Komut satırı argümanlarının sayısını kontrol etme
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_processes> <program_name>\n", argv[0]);
        exit(1); // Yanlış kullanımda programdan çıkma
    }

    // Komut satırı argümanlarını alma
    int num_processes = atoi(argv[1]); // Proses sayısını alma
    char *program_name = argv[2]; // Çalıştırılacak programın adını alma

    // Paylaşımlı bellek oluşturma
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666); // Paylaşımlı bellek nesnesi oluşturma
    ftruncate(shm_fd, BUFFER_SIZE * sizeof(int)); // Bellek boyutunu ayarlama
    int *shared_buffer = mmap(NULL, BUFFER_SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); // Belleği eşleme

    // Semaforları oluşturma
    sem_t *full = sem_open(SEM_FULL_NAME, O_CREAT, 0666, 0); // Dolu semaforu oluşturuyorum ve başlangıç değerini 0 yapma
    sem_t *empty = sem_open(SEM_EMPTY_NAME, O_CREAT, 0666, BUFFER_SIZE); // Boş semaforu oluşturuyorum ve başlangıç değerini BUFFER_SIZE yapıyorum
    sem_t *mutex = sem_open(SEM_MUTEX_NAME, O_CREAT, 0666, 1); // Mutex semaforu oluşturuyorum ve başlangıç değerini 1 yapıyorum

    // Proses oluşturma
    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork(); // Yeni proses oluşturuyorum
        if (pid == 0) { // Çocuk proses
            char rank_str[10];
            sprintf(rank_str, "%d", i); // Proses sırasını string olarak hazırlıyorum
            execl(program_name, program_name, rank_str, NULL); // Programı ve argümanını çalıştırıyorum
            perror("execl"); // Hata durumunda hata mesajı yazıyorum
            exit(1); // Hata durumunda çıkıyorum
        }
    }

    // Proseslerin tamamlanmasını bekleme
    for (int i = 0; i < num_processes; i++) {
        wait(NULL); // Her bir çocuk prosesin bitmesini bekleme
    }

    // Temizlik işlemleri
    munmap(shared_buffer, BUFFER_SIZE * sizeof(int)); // Bellek eşlemesini kaldır
    shm_unlink(SHM_NAME); // Paylaşımlı bellek nesnesini silme
    sem_close(full); // Semaforları kapatma
    sem_close(empty); // Semaforları kapat
    sem_close(mutex); // Semaforları kapatma
    sem_unlink(SEM_FULL_NAME); // Semafor nesnesini sil
    sem_unlink(SEM_EMPTY_NAME); // Semafor nesnesini sil
    sem_unlink(SEM_MUTEX_NAME); // Semafor nesnesini sil

    return 0;
}
