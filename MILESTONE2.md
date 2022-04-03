# Milestone 2 Tugas Besar IF2230

## Deskripsi Tugas

- Memahami <em><strong>filesystem</strong></em> sederhana yang fungsional
- Membuat <em>syscall</em>
  - readSector
  - writeSector
  - read
  - write
- Membuat sebuah <em><strong>shell</strong></em> sederhana
- Membuat utility kecil pada shell
  - cd
  - ls
  - mkdir
  - cat
  - cp
  - mv

## Daftar Syscall

<table>
  <tr>
    <td align="center">No</td>
    <td align="center">Syscall</td>
    <td align="center">Deskripsi</td>
  </tr>

  <tr>
    <td align="center">1</td>
    <td>readSector</td>
    <td>Baca sektor yang ada di dalam storage image ke memory.</td>
  </tr>

  <tr>
    <td align="center">2</td>
    <td>writeSector</td>
    <td>Tulis sektor yang ada di dalam memory ke storage image.</td>
  </tr>

  <tr>
    <td align="center">3</td>
    <td>read</td>
    <td>Melakukan pembacaan pada filesystem.</td>
  </tr>

  <tr>
    <td align="center">4</td>
    <td>write</td>
    <td>Melakukan penulisan file atau folder ke filsystem.</td>
  </tr>

<table>

## Daftar Utility Shell

<table>
  <tr>
    <td align="center">No</td>
    <td align="center">Utility Shell</td>
    <td align="center">Deskripsi</td>
  </tr>

  <tr>
    <td align="center">1</td>
    <td align="center">cd</td>
    <td>Merupakan alat dasar untuk melakukan navigasi pada filesystem.</td>
  </tr>

  <tr>
    <td align="center">2</td>
    <td align="center">ls</td>
    <td>Memperlihatkan konten yang ada pada current working directory.</td>
  </tr>

  <tr>
    <td align="center">3</td>
    <td align="center">mv</td>
    <td>Melakukan operasi rename atau memindahkan file maupun folder.</td>
  </tr>

  <tr>
    <td align="center">4</td>
    <td align="center">mkdir</td>
    <td>Membuat suatu folder baru pada current working directory.</td>
  </tr>

  <tr>
    <td align="center">5</td>
    <td align="center">cat</td>
    <td>Menampilkan isi dari suatu file sebagai text file.</td>
  </tr>

  <tr>
    <td align="center">6</td>
    <td align="center">cp</td>
    <td>Melakukan copy file dari current working directory ke current working directory.</td>
  </tr>

<table>

[BACK](README.md)
