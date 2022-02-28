# Milestone 1 Tugas Besar IF2230

## Deskripsi Tugas
* Menyiapkan disk image
* Melakukan instalasi bootloader
* Implementasi kernel sederhana
* Menjalankan sistem operasi
* Melakukan implementasi beberapa syscall:
    * Membaca input dari keyboard
    * Menulis output ke layar
    * Membersihkan (clear) layar
* Pembuatan script untuk build OS
* Mengerti cara kerja interrupt
* Mengerti cara kerja kernel.asm

## Daftar Syscall
### printString
> Menampilkan null terminated string dengan character set ASCII pada lokasi kursor.

### readString
> Menerima input non-control character ASCII dan memasukkan pada buffer. readString berhenti membaca ketika mendapatkan carriage return / tombol enter.

### clearScreen
> Menghapus layar dengan spesifikasi sebagai berikut: <br /> 1. Menghapus layar <br /> 2. Memindahkan kursor ke pojok kiri atas <br /> 3. Mengganti buffer warna menjadi warna putih / 0xF

[BACK](README.md)