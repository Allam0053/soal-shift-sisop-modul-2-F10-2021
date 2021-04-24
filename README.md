# soal-shift-sisop-modul-2-F10-2021

berikut adalah rekaman jalannya program:
https://drive.google.com/drive/folders/1V_GKtlUyMYF2W-LEMDsg_AkY7COs2mun?usp=sharing

# Nomor 1

Steven menjadi budak cinta bagi Stevany. Sehingga Steven ingin memberikan suatu hadiah kepada Stevany berupa sebuah zip berisi berbagai foto, musik, dan video. Tahapan yang akan dilakukan Steven :
1b. Mendownload tiga zip masing-masing berisi folder FOTO yang berisikan file-file foto, MUSIK yang berisikan file-file musik, dan FILM yang berisikan file-file video, secara berurutan

https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view

https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view

https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view

1c. 1d. dan 1a. Zip tersebut harus di-ekstrak. Karena hasil ekstraknya berupa folder, maka foldernya cukup diubah namanya secara berurutan (Jujur, sedikit alay) menjadi Pyoto, Musyik, dan Fylm

1e. Tahapan diatas dilakukan secara otomatis pada jam 16.22 tanggal 9 April, 6 jam sebelum waktu ulang tahun Stevany, menurut Akte Kelahirannya

1f. Pada saat waktu ulang tahunnya Stevany, jam 22.22 tanggal 9 April, secara otomatis folder-folder Pyoto, Musyik, dan Fylm dimasukkan ke dalam zip bernama Lopyu_Stevany.zip. Setelah itu, folder-folder yang sudah dimasukkan ke dalam zip dihapuskan sehingga hanya menyisakan zip-nya

- Semua tahapan di atas dijadikan ke dalam satu script latar belakang (Daemon)
- Tidak boleh menggunakan system(), mkdir(), rename(), cron
- Harus menggunakan fork, exec, wait(), sleep(), dan wget

# Penyelesaian Nomor 1

- Website-website di atas akan diunduh menggunakan command bash :

      wget --no-check-certificate https://drive.google.com/uc?id=[id file]&export=download" -O [Namafile].zip
      
  id file adalah kode website yang bersangkutan mulai dari ...d/ sampai /view
  Karena nama situsnya lumayan panjang, situs downloadnya akan disimpan di dalam string tersendiri
  
      char foto1[] = "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download";
      char musik1[] = "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download";
      char film1[] = "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download";
  
  [Namafile].zip adalah file hasil download tersebut dengan nama [Namafile]. Karena awalanya dikira akan bermasalah jika tidak dijadikan string tersendiri, maka nama file zip dijadikan string tersendiri
  
      char fotozip[] = "Foto.zip";
      char musikzip[] = "Musik.zip";
      char filmzip[] = "Film.zip";

- Masing-masing perintah memiliki fork yang berbeda. Mendownload file zip satu fork, mengekstrak file zip satu fork, memindahkan folder-folder satu fork, memasukan ke dalam file zip satu fork, dan menghapus folder satu fork. Diantara masing-masing perintah dibatasi dengan :
   
      while(wait(NULL) > 0)
      
agar masing-masing perintah berjalan secara urut dan tidak bersamaan. (Atau agar sistem tidak bingung).

## 1b. Mendownload file zip dari link-link sebelumnya

      pid_t pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg1[] = {"wget", "--no-check-certificate", foto1, "-O", fotozip, NULL};
          //https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/
          execv("/bin/wget", arg1);
      }

      while(wait(NULL) > 0);
      
Karena proses mengunduh masing-masing file tidak jauh berbeda, hanya ada perubahan link download dalam string char multidimensi dan nama file-nya, ditampilkan salah satu perintah mengunduh, yaitu mengunduh file zip yang berisi folder FOTO. Awalnya ditentukan nilai dari fork() kepada variabel pid. Setelah di-inisialisasi nilai fork, yang seharusnya pasti 0 kalau bukan nilai PID, akan dilakukan perintah di dalam fungsi if(pid == 0).

Di-inisialisasikan suatu string char dua dimensi yang berisikan command dalam bahasa bash yang diakhiri dengan nilai NULL. Command tersebut adalah command wget untuk mendownload suatu file dari website di dalam command tersebut tanpa memperhatikan sertifikat dari website tersebut dan lalu hasil download tersebut diubah namanya. String char dua dimensi ini akan dieksekusi oleh fungsi execv. Setelah perintah sudah dijalankan, akan diakhiri dengan while(wait(NULL) > 0) untuk menjalankan perintah setelahnya, yaitu mendowndload file zip berisi musik dan film, yang mana tidak bisa dilakukan bersamaan dengan mendownload file zip foto karena wget dijalankan satu-persatu

Dan comment di bawah hanya untuk mengingat nama id link yang akan diunduh

## 1c. Mengekstrak zip-zip yang sudah di download

      pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg4[] = {"unzip", fotozip, NULL};
          execv("/bin/unzip", arg4);
      }

Untuk mengekstrak file zip, maka diperlukan command bash unzip. Perintah unzip dijalankan di dalam if jika nilai fork() adalah 0

## 1d. dan 1a. Memindahkan file di dalam folder yang sudah diekstrak ke dalam folder tujuan

      pid = fork();
      if(pid < 0) exit(EXIT_FAILURE);
      if(pid == 0){
          char *arg7[] = {"mv", "FOTO", "Pyoto", NULL};
          execv("/bin/mv", arg7);
      }
Perintah 1a dan 1d bisa digabungkan dengan menggunakan command bash mv, yang mana bisa mengubah nama folder dengan cara membuat folder baru bernama secara berurutan untuk masing-masing folder Pyoto, Musyik, dan Fylm lalu memindahkan seluruh isi folder lama ke dalam folder baru tersebut. Kemudian folder lama tersebut dihapuskan

## 1e. 1a. sampai 1d. dijalankan 6 jam secara otomatis sebelum jam 22.22 pada tanggal 9 April (Yaitu jam 16.22 pada tanggal yang sama)

Karena soal ini menggunakan fungsi waktu untuk menentukan waktu yang tepat, seperti pada jam 16.22 dan 22.22 pada tanggal 9 April, maka diperlukan library C bernama time.h yang memiliki fungsi time_t dan struct tm untuk menemukan waktu yang tertulis di dalam sistem

      #include <time.h>

      time_t rawtime = time(NULL);
      struct tm timeinfo = *localtime(&rawtime);
      
Jika waktu dalam sistem adalah jam 16.22 pada tanggal 9 April, maka soal nomor 1a. sampai 1d. dijalankan secara berurutan. Sedangkan jika waktu dalam sistem adalah 22.22 pada tanggal 9 April, maka soal nomor 1f. dijalankan

      if(timeinfo.tm_mday == 9 && timeinfo.tm_mon + 1 == 4 && timeinfo.tm_hour == 16 && timeinfo.tm_min == 22)
      /*proses 1a. sampai 1d.*/
      else if(timeinfo.tm_mday == 9 && timeinfo.tm_mon + 1 == 4 && timeinfo.tm_hour == 22 && timeinfo.tm_min == 22)
      /*proses 1f.*/

Perlu diketahui bahwa untuk timeinfo.tm_mon, Januari diterjemahkan menjadi bulan ke-0, bukan bulan ke-1, dan ada berbagai sub-struct yang dapat menyebutkan hari dengan berbagai format (Hari ke berapa dalam se-tahun, hari ke berapa dalam satu minggu, dan yang digunakan, hari ke berapa dalam satu bulan)

## 1f. Memasukan folder-folder tadi ke dalam zip Lopyu_Stevany.zip

      pid_t pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg10[] = {"zip", "-r", "Lopyu_Stevany.zip", "Pyoto", "Myusik", "Fylm", NULL};
          execv("/bin/zip", arg10);
      }

      while(wait(NULL) > 0);
      pid = fork();
      if (pid < 0) exit(EXIT_FAILURE);
      if (pid == 0) {
          char *arg11[] = {"rm", "-r", "Pyoto", "Myusik", "Fylm", NULL};
          execv("/bin/rm", arg11);
      }
      
Ada dua operasi dalam 1f, yaitu memasukan folder Pyoto, Myusik, dan Fylm ke dalam zip Lopyu_Stevany.zip, dan menghapus folder Pyoto, Myusik, dan Fylm sehingga menyisakan zip-nya saja.

Command zip tidak akan juga memasukan file-file di dalam folder yang akan dimasukan ke dalam zip jika tidak diikuti dengan command -r (recursive) yang akan mengikutsertakan file-file di dalam folder. Begitupula dengan command rm, yang akan menghapus folder tersebut beserta file-file di dalamnya

- Dan yang terakhir, seluruh operasi tersebut, dari 1a. sampai 1f., terletak di dalam while(1) dan diakhiri dengan sleep(). Fungsi sleep() adalah untuk menentukan setelah berapa detik program daemon menge-loop
- Kesulitan dalam penyelesaian terletak pada batasan download dari Google Drive sehingga memunculkan error 403 dari ouput wget. Perlu beberapa kali restart untuk mendownload file zip dari link Google Drive tersebut. 

# Nomor 2

- Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.

- Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.
Contoh: Jenis peliharaan kucing akan disimpan dalam “/petshop/cat”, jenis peliharaan kura-kura akan disimpan dalam “/petshop/turtle”.

- Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
Contoh: “/petshop/cat/joni.jpg”. 

- Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”.

- Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.

<br>

# Solusi Nomor 2

- Sebelum menyelesaikan persoalan 2a dan selanjutnya, diperlukan file pets.zip. Maka diunduh dengan memasukkan perintah sebagai berikut:

      char link[] = "https://drive.google.com/uc?id=1g5rehatLEkqvuuK_eooHJXB57EfdnxVD&export=download";
      char dir_[] = "/home/allam/Downloads/pets.zip";
      char *arg_init0[] = {wget_[1], link, "-O", dir_, NULL};
      util (&cpid, wget_[0], arg_init0);

- Berikutnya file dipindah ke directory Downloads

      tunggu

      char source[] = "/home/allam/Downloads/pets.zip";
      char dest__[] = "/home/allam/pets.zip";
      char *arg_init1[] = {mv___[1], source, dest__, NULL};
      util (&cpid, mv___[0], arg_init1);

- Method / function util() adalah function untuk membuat child process. Function ini dibuat karena proses pembuatan child dilakukan lebih dari tiga kali sehingga diharapkan dapat menyederhanakan code. Berikut adalah isi method tersebut:

      void util (pid_t *cpid, char *arg, char **argv) {
        *cpid = fork();
        if (*cpid < 0) exit(1);
        if (*cpid == 0) {
            execv(arg, argv);
            exit(0);
        }
        return;
      }

## 2a
- Untuk menyelesaikan task 2am program melakukan ekstrak pets.zip tanpa menyertakan folder yang tidak penting berikut adalah code dari program yang telah dibuat:

      char *arg_2a[] = {mkdir[1], "-p", target_loc, NULL};
      util (&cpid1, mkdir[0], arg_2a);

      tunggu

      char *arg_2a1[] = {unzip[1], zip_file, "-d", target_loc, "-x", "*/*", NULL};
      util (&cpid2, unzip[0], arg_2a1);
  
  Inti dari code tersebut adalah membuat directory "/home/allam/modul2/petshop" lalu mengekstrak file yang diperlukan pada directory tersebut. Digunakan option -x untuk mengecualikan folder dan file dalam folder yang tidak berguna tersebut.

## 2b
- Program membuat folder dengan memeriksa tiap file, tiap jenis hewan yang ada akan dibuatkan folder tersendiri. berikut adalah code untuk 2b:

      cpid3 = fork();
      if (cpid3 < 0) exit(EXIT_FAILURE);
      
      if (cpid3 == 0) {
          listFilesRecursively("/home/allam/modul2/petshop");
          for (int i=0; i<list_dir; i++) {
              char *arg_2b[] = {mkdir[1], "-p", makedir[i], NULL};
              util (&cpid4, mkdir[0], arg_2b);
          }
          tunggu
          printf("2b selesai\n");
          exit(EXIT_SUCCESS);
      }
  
  Dengan menggunakan function listFilesRecursively() maka daftar jenis hewan akan tersimpan pada variable "char makedir[100][100]". Setelah mendapatkan jenis hewan maka akan dibuatkan folder dengan function util (&cpid4, mkdir[0], arg_2b).

## 2c dan 2d
- Program melakukan pemindahan file dan merubah nama file sesuai dengan nama hewan yang ada. Berikut adalah code untuk 2c:

      listFiles("/home/allam/modul2/petshop");
      char temp[100];
      char source[200], dest__[200];
      char under[]="_";
      char jpg[]=".jpg";

      for (int i=0; i<list_files; i++) {
          sprintf(source, "%s/%s", target_loc, files[i]);
          strcpy(temp, files[i]);
          strcpy(kind[i], strtok(temp,";"));
          strcpy(name[i], strtok(NULL,";"));
          strcpy(age[i], strtok(NULL,"j"));
          age[i][strlen(age[i])-1] = '\0';

          if(strstr(files[i], jpg)==NULL){ //if 1 poto ada 2 hewan: duplicate, namai poto dg 1 hewan
              tunggu

              sprintf(source, "%s/%s%s%s", target_loc, files[i], under, files[i+1]);
              sprintf(dest__, "%s/%s.jpg", target_loc, files[i]);
              char *arg_2c[] = {cp___[1], source, dest__, NULL};
              util (&cpid6, cp___[0], arg_2c);

              tunggu

              sprintf(source, "%s/%s%s%s", target_loc, files[i], under, files[i+1]);
              sprintf(dest__, "%s/%s", target_loc, files[i+1]);
              char *arg_2c1[] = {mv___[1], source, dest__, NULL};
              util (&cpid6, mv___[0], arg_2c1);

              strcat(files[i],".jpg");            
          }
          tunggu

          sprintf(source, "%s/%s", target_loc, files[i]);
          sprintf(dest__, "%s/%s/%s.jpg", target_loc, kind[i], name[i]);
          char *arg_2c2[] = {mv___[1], source, dest__, NULL};
          util (&cpid6, mv___[0], arg_2c2);
      }

      tunggu
      printf("2c 2d selesai\n");
  
  Function listFiles("/home/allam/modul2/petshop") akan membaca ada file apa saja di directory tersebut (tanpa membaca folder), lalu akan menyimpan nama-nama file yang ada pada variable "char files[100][100]". Lalu data tiap hewan akan disimpan pada variable char kind[100][100] untuk jenis hewan, char name[100][100] untuk nama hewannya, dan char age[100][100] untuk umur hewan. Bila file mempunyai dua hewan maka akan diduplikasi dan direname dengan nama salah satu hewan di satu file dan nama hewan yg lain pada file yang lainnya. Setelah proses pengambilan data hewan, files akan dipindah sesuai jenis hewan dan direname dengan nama hewannya saja.

## 2e
- Program menulisakan data yang ada pada folder terkait pada keterangan.txt. Berikut adalah code untuk program tersebut:

      FILE *output;
      listFolder(target_loc);

      for(int i=0; i<list_folders; i++) {
          tunggu
          sprintf(dest__, "%s/%s/keterangan.txt", target_loc, folders[i]);
          char *arg_2e[] = {touch[1], dest__, NULL};
          util (&cpid8, touch[0], arg_2e);

          tunggu

          cpid8 = fork();
          if (cpid8 < 0) exit(1);
          if (cpid8 == 0) {
              pid_t pid, sid;

              pid = fork();
              if (pid < 0) exit(EXIT_FAILURE);
              if (pid > 0) exit(EXIT_SUCCESS);
              umask(0);
              sid = setsid();
              if (sid < 0) exit(EXIT_FAILURE);
              if ((chdir("/")) < 0) exit(EXIT_FAILURE);

              sprintf(dest__, "%s/%s/keterangan.txt", target_loc, folders[i]);
              output = fopen(dest__, "w+");
              umask(0);
              for(int j=0; j<list_files; j++) {
                  if( strcmp(folders[i], kind[j])==0 ) {
                      fprintf(output, "nama : %s\n", name[j]);
                      fprintf(output, "umur : %s tahun\n\n", age[j]);
                  }
              }
              fclose(output);

              exit(0);
          }
      }
      tunggu
      printf("2e selesai\n");

  Sesuai data yang telah diperoleh atau direkam pada 2c dan 2d, tiap data tersebut dicetak pada file terkait yaitu keterangan.txt pada tiap folder jenis hewan. Sebelum menuliskan data, file keterangan.txt dibuat dengan command touch.

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
