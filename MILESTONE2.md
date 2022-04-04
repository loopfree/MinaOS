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

| No  | Utility Shell |                        Command                        | Deskripsi                                                                        |
| :-: | :-----------: | :---------------------------------------------------: | -------------------------------------------------------------------------------- |
|  1  |      cd       |             `cd <folder>` `cd ..` `cd /`              | Merupakan alat dasar untuk melakukan navigasi pada filesystem.                   |
|  2  |      ls       |                  `ls <folder>` `ls`                   | Memperlihatkan konten yang ada pada current working directory.                   |
|  3  |      mv       | `mv <SRC> <DST>` `mv <SRC> /<DST>` `mv <SRC> ..<DST>` | Melakukan operasi rename atau memindahkan file maupun folder.                    |
|  4  |     mkdir     |                   `mkdir <folder>`                    | Membuat suatu folder baru pada current working directory.                        |
|  5  |      cat      |                     `cat <file>`                      | Menampilkan isi dari suatu file sebagai text file.                               |
|  6  |      cp       |        `cp <file/directory> <file/directory>`         | Melakukan copy file dari current working directory ke current working directory. |

[BACK](README.md)