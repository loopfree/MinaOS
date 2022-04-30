# Milestone 3 Tugas Besar IF2230

> Membuat <strong><em>binary executable</em></strong> terpisah dari <strong><em>kernel space</em></strong>

## Deskripsi Tugas

-   Membuat <em>library</em> sistem operasi
-   Membuat <strong><em>syscall executeProgram</em></strong>
-   Membuat aplikasi shell yang independen dari kernel
-   Membuat sistem <strong><em>message passing</em></strong> antar program
-   Menambah fitur eksekusi program pada aplikasi <strong><em>shell</em></strong>
-   Membuat <strong><em>utility program</em></strong>
-   Membuat eksekusi <strong><em>multiple program</em></strong> secara sekuensial

## Cara Run

1. Mula-mula, jalankan perintah berikut pada terminal

    ```bash
    make build-run
    ```

2. Tunggu hingga loading selesai, lalu ketik `c` dan disusul dengan mengetik `q`

3. Berikutnya, jalankan perintah berikut pada terminal

    ```bash
    make file_insert
    ```

4. Selanjutnya, jalankan perintah berikut pada terminal

    ```bash
    make run
    ```

5. Tunggu hingga loading selesai, lalu ketik `c`

## Konstrain Milestone 3

-   <div style="text-align: justify">Setiap <strong><em>user program</em></strong> memiliki ukuran maksimum 8192 bytes (Ukuran maksimum 1 <strong><em>entry file</em></strong> yang di <strong><em>support</em></strong> oleh <strong><em>filesystem</em></strong>)</div>

-   <div style="text-align: justify">Setelah <strong><em>user program</em></strong> selesai, sistem operasi akan meng<strong><em>-exec shell</em></strong> pada segmen <font color="steelblue">0x2000</font></div>

-   <div style="text-align: justify"><strong><em>User program</em></strong> dilarang untuk memanggil langsung <strong><em>syscall</em></strong> (ex. Implementasi kode <strong><em>write</em></strong>) di<strong><em>copy-paste</em></strong> dan dipanggil langsung pada <strong><em>shell.c</em></strong>. Gunakan <strong><em>interrupt 21h</em></strong> yang telah dibuat</div>

-   <div style="text-align: justify">Antar program dapat berkomunikasi dengan sistem <strong><em>message passing</em></strong> yang telah dibuat</div>

-   <div style="text-align: justify">Ukuran default kernel adalah 15 sektor (7680 bytes). <strong><em>Upper bound</em></strong> ukuran kernel pada tugas besar ini adalah 31 sektor (15872 bytes). Jika merubah ukuran kernel pastikan batas <font color="steelblue">fillMap</font>( ), <strong>KSIZE</strong> bootloader.asm, atas <strong><em>syscall read / write</em></strong>, dan batas-batas lain telah disesuaikan</div>

-   <div style="text-align: justify">Bergantung kepada banyaknya <strong><em>entry filesystem node</em></strong> yang digunakan folder dan executable (<strong><em>bin, shell, cp, ...</em></strong>), kondisi benar <strong><em>test case</em></strong> yang diberikan pada milestone 2 dapat berubah dikarenakan pergeseran <strong><em>parent index</em></strong> <font color="steelblue">insert_file</font>( ) dan <font color="steelblue">create_folder</font>( )</div>

-   <div style="text-align: justify">Gunakan <strong><em>interrupt 21h</em></strong> untuk memanggil <strong><em>syscall</em></strong> (<font color="steelblue">write</font>( ), <font color="steelblue">read</font>( ), <font color="steelblue">printString</font>( ), etc). <strong><em>Library</em></strong> tidak mengimplementasikan sendiri <strong><em>syscall</em></strong>, hanya memanggil <strong><em>interrupt 21h</em></strong> yang telah disediakan sistem operasi. <strong><em>Copy-paste</em></strong> langsung <strong><em>syscall</em></strong> ke <strong><em>library</em></strong> (ex. Implementasi <font color="steelblue">write</font>( ) di<strong><em>-copy</em></strong> ke <strong><em>fileio.c</em></strong>) akan menyebabkan penilaian yang tidak maksimal</div>

    <font color="white"><strong>TAMBAHAN</strong></font>

-   Untuk setiap user program, perlu memanggil <font color="steelblue">exit</font>( ) dari library program pada akhir user program

[BACK](README.md)
