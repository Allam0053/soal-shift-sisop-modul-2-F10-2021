# soal-shift-sisop-modul-2-F10-2021

# Nomor 3

- Membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

- Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix

- Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

- Men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankanprogram “Killer” yang dibuat nantinya harus merupakan program bash.

- Program yang dibuat dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai

<br>

# Solusi Nomor 3

## Penyelesaian nomor 3a - 3c ada didalam loop daemon

<br>

- **Nomor 3a**

  - Pertama akan dibuat string timestamp dengan format sesuai soal. Untuk melakukannya cukup sederhana, dapat menggunakan fungsi `time()` dan `localtime()`. Dari situ kita bisa mendapat informasi tahun, bulan, hari, jam, menit, dan detik yang kemudian hanya perlu di-concate hingga terbentuk sesuai format. Proses tersebut ada di dalam fungsi user-defined `get_timestamp()` dimana fungsi ini juga sekaligus mereturn nilai epochtime ([lihat detail fungsi](https://github.com/Allam0053/soal-shift-sisop-modul-2-F10-2021/blob/main/soal3/soal3.c#L130)).

        pid_t pid_create_dir = fork();

        char dir_timestamp[20] = "";
        get_timestamp(dir_timestamp);

  <br>

  - Berikutnya hanya perlu membuat foldernya dengan menjalankan command `mkdir` menggunakan fungsi `execv()`.

        if (THIS_PROCESS == pid_create_dir) {
          char* argv[] = { "mkdir", "-p", dir_timestamp, NULL };
          execv("/bin/mkdir", argv);
        }

  <br>

  - Setelah itu program akan tidur selama 40 detik lalu kembali mengulangi proses pembuatan folder.

        pid_t pid_download_pictures = fork();

        if (THIS_PROCESS != pid_download_pictures) {
          sleep(40);
          continue;
        }

<br><br>

- **Nomor 3b**

  - Cara mendownload 10 gambar adalah menggunakan perulangan `while (foto terdownload < 10)`.

        int downloaded_pictures = 0;

        while (downloaded_pictures++ < 10) {
          pid_t pid_for_download = fork();
          if (THIS_PROCESS == pid_for_download) {
            ...
          }
          ...
        }

  <br>

  - Kemudian untuk setiap proses mendownload 1 gambar

    - Bentuk string timestamp sekaligus mendapatkan epochtime dengan menggunakan fungsi user-defined `get_timestamp()` yang sudah dijelaskan di **Nomor 3a**

          char pic_timestamp[20] = "";
          int time = (int) get_timestamp(pic_timestamp);

    <br>

    - Kalkulasi ukuran gambar menggunakan formula yang diberikan pada soal

          int size = (time % 1000) + 50

    <br>

    - Lalu concat string url (untuk download gambar) dengan size yang sudah dikalkulasi dan juga concat untuk membentuk nama file gambar

          char url[27];
          sprintf(url, "https://picsum.photos/%d", size);

          char pic_path_dest[100] = "";
          strcat(pic_path_dest, dir_timestamp);
          strcat(pic_path_dest, "/");
          strcat(pic_path_dest, pic_timestamp);
          strcat(pic_path_dest, ".jpg");

    <br>

    - Ketika nama file dan url sudah didapatkan, maka hanya perlu mendownload dengan command `wget` mengggunakan fungsi `execv()`

          char* argv[] = { "wget", "-q", "-O", pic_path_dest, url, NULL };
          execv("/usr/local/bin/wget", argv);

    <br>

  - Setiap setelah proses download 1 gambar selesai, jeda loop selama 5 detik dengan fungsi `sleep()`

        sleep(5);

<br><br>

- **Nomor 3c**

  - Membuat file **status.txt**

    - Buat string yang berisikan pesan `"Download Success"` kemudian enkripsi pesan dengan `metode caesar`. Proses enkripsinya dilakukan menggunakan fungsi user-defined `caesar_encrypt()` ([lihat disini](https://github.com/Allam0053/soal-shift-sisop-modul-2-F10-2021/blob/main/soal3/soal3.c#L167))

          char message[20] = "Download Success";
          caesar_encrypt(message);

    <br>

    - Kemudian buat file **status.txt** menggunakan fungsi `fopen()`

          char file_message_name[100] = "./";
          strcat(file_message_name, dir_timestamp);
          strcat(file_message_name, "/status.txt");

          FILE* fp = fopen(file_message_name, "w+");
          fputs(message, fp);
          fclose(fp);

    <br>

  - Zip folder timestamp yang dibuat pada nomor 3a dengan menggunakan command `zip` menggunaakn fungsi `execv()`

        pid_t pid_for_zip = fork();

        if (THIS_PROCESS == pid_for_zip) {
          char zip_name[50];
          strcat(zip_name, dir_timestamp);
          strcat(zip_name, ".zip");

          char* argv[] = { "zip", "-qq", "-r", zip_name, dir_timestamp, NULL };
          execv("/usr/bin/zip", argv);
        }

  <br>

  - Hapus folder timestamp dengan command `rm` menggunakan fungsi `execv()`

        char* argv[] = { "rm", "-r", dir_timestamp, NULL };
        execv("/bin/rm", argv);

<br><br>

- **Nomor 3d & 3e**

  Sebelum membahas solusinya, perhatikan bahwa terdapat variabel global `signal_process` yang pada awalnya bernilai **1** dan variabel tersebut digunakan pada loop daemon.

      #include <sys/stat.h>
      ...

      int signal_proccess = 1;
      ...

      int main(int argc, char* args[]) {
        ...

        // Daemon loop
        while(signal_proccess) {
          ...
        }

        return 0;
      }

  <br>

  - Untuk menerima opsi mode, pada fungsi `int main()` harus diberi parameter `int argc & char* args[]` sehingga opsi mode akan ditangkap oleh variabel `args`. Lalu buat file killernya dengan fungsi user-defined `request_create_kill_file()` Sehingga file killer akan terbentuk (jika modenya valid)

        int main(int argc, char* args[]) {
          if (argc >= 2) request_create_kill_file(args);
          ...
        }

  <br>

  - Detail fungsi `request_create_kill_file()` dapat dilihat dibawah

        void request_create_kill_file(char* args[]) {
          const int EQUAL = 0;
          if (strcmp(args[1], "-z") == EQUAL) return create_kill_file('z');
          if (strcmp(args[1], "-x") == EQUAL) {
            signal(SIGTERM, stop_process);
            return create_kill_file('x');
          }
        }

    <br>

    - Jika mode -z maka file killer akan dibuat menggunakan fungsi user-defined `create_kill_file()` dengan mode 'z' ([lihat disini](https://github.com/Allam0053/soal-shift-sisop-modul-2-F10-2021/blob/main/soal3/soal3.c#L177))

    - Jika mode -x maka akan didaftarakan event listener untuk **sinyal 15** (direpresentasinya pada variable `SIGTERM`) dimana jika sinyal 15 diterima maka fungsi `stop_process()` ([lihat disini](https://github.com/Allam0053/soal-shift-sisop-modul-2-F10-2021/blob/main/soal3/soal3.c#L202)) akan dijalankan dimana fungsi `stop_process()` akan membuat variabel global `signal_process` **bernilai 0**. Kemudian membuat file killer menggunakan fungsi `create_kill_file()` dengan mode 'x'

  <br>

  - Jika mode -z maka file killernya akan meng-kill dengan mengirim **sinyal 9** sehingga jika program killer dijalankan maka proses daemon akan langsung berhenti saat itu juga.

  - Jika mode -x maka file killernya akan mengirim **sinyal 15** sehingga ketika program daemon ini menerima sinyal tersebut fungsi `stop_process()` akan dijalankan yang menyebabkan variabel global `signal_process` akan **bernilai 0**. Akibatnya proses daemon yang saat itu berjalan akan diselesaiakan sampai selesai kemudian daemon akan berkahir karena loop utama daemmon `while (signal_process)` berhenti.
