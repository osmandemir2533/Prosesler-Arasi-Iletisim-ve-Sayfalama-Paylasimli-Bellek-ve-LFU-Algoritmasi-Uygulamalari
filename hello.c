#include <stdio.h>      // Standart giriş/çıkış işlemleri için
#include <stdlib.h>     // Genel standart kütüphane
#include <unistd.h>     // POSIX işlevleri ve konfigürasyonları için
#include <sys/mman.h>   // Bellek eşleme işlemleri için
#include <fcntl.h>      // Dosya işlemleri için
#include <semaphore.h>  // Semaför işlemleri için

#define SHM_NAME "shared_memory"  // Paylaşılan bellek adı
#define SEM_FULL_NAME "/sem_full" // Dolu semaforun adı
#define SEM_EMPTY_NAME "/sem_empty"   // Boş semaforun adı
#define SEM_MUTEX_NAME "/sem_mutex"   // Kilit semaforun adı
#define BUFFER_SIZE 10   // Paylaşılan bellek boyutu

// Veri gönderen işlev
void mpi_send(int rank, int number) {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666); // Paylaşılan bellek dosyasını aç
    int *shared_buffer = mmap(NULL, BUFFER_SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); // Belleği eşle

    sem_t *full = sem_open(SEM_FULL_NAME, 0);   // Dolu semaforunu aç
    sem_t *empty = sem_open(SEM_EMPTY_NAME, 0); // Boş semaforunu aç
    sem_t *mutex = sem_open(SEM_MUTEX_NAME, 0); // Kilit semaforunu aç

    sem_wait(empty); // Boş semaforu beklet
    sem_wait(mutex); // Kilit semaforu beklet

    shared_buffer[rank % BUFFER_SIZE] = number; // Paylaşılan belleğe veri yaz

    sem_post(mutex); // Kilit semaforunu serbest bırak
    sem_post(full);  // Dolu semaforunu serbest bırak

    munmap(shared_buffer, BUFFER_SIZE * sizeof(int)); // Belleği kaldır
}

// Veri alan işlev
void mpi_recv(int rank, int *number) {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666); // Paylaşılan bellek dosyasını aç
    int *shared_buffer = mmap(NULL, BUFFER_SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); // Belleği eşle

    sem_t *full = sem_open(SEM_FULL_NAME, 0);   // Dolu semaforunu aç
    sem_t *empty = sem_open(SEM_EMPTY_NAME, 0); // Boş semaforunu aç
    sem_t *mutex = sem_open(SEM_MUTEX_NAME, 0); // Kilit semaforunu aç

    sem_wait(full);  // Dolu semaforu beklet
    sem_wait(mutex); // Kilit semaforu beklet

    *number = shared_buffer[rank % BUFFER_SIZE]; // Paylaşılan bellekten veriyi oku

    sem_post(mutex); // Kilit semaforunu serbest bırak
    sem_post(empty); // Boş semaforunu serbest bırak

    munmap(shared_buffer, BUFFER_SIZE * sizeof(int)); // Belleği kaldır
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rank>\n", argv[0]); // Komut satırı argümanlarını kontrol et
        exit(1);
    }

    int rank = atoi(argv[1]); // İşlem sırasını al
    int number;

    if (rank % 2 == 0) { // Çift sıradaki işlem
        mpi_recv(rank + 1, &number); // Veri al
        printf("Process %d received %d from process %d\n", rank, number, rank + 1); // Veriyi yazdır
        mpi_send(rank + 1, number); // Veri gönder
        printf("Process %d sent %d to process %d\n", rank, number, rank + 1); // Gönderilen veriyi yazdır
    } else { // Tek sıradaki işlem
        number = rank; // Veri ata
        mpi_send(rank - 1, number); // Veri gönder
        printf("Process %d sent %d to process %d\n", rank, number, rank - 1); // Gönderilen veriyi yazdır
        mpi_recv(rank - 1, &number); // Veri al
        printf("Process %d received %d from process %d\n", rank, number, rank - 1); // Alınan veriyi yazdır
    }

    return 0;
}
