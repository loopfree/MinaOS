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
    <td align="center">readSector</td>
    <td align="justify">Baca sektor yang ada di dalam storage image ke memory.</td>
  </tr>

  <tr>
    <td align="center">2</td>
    <td align="center">writeSector</td>
    <td align="justify">Tulis sektor yang ada di dalam memory ke storage image.</td>
  </tr>

  <tr>
    <td align="center">3</td>
    <td align="center">read</td>
    <td align="justify">Melakukan pembacaan file.</td>
  </tr>

  <tr>
    <td align="center">4</td>
    <td align="center">write</td>
    <td align="justify">Melakukan penulisan file atau folder ke filesystem.</td>
  </tr>

<table>

## Daftar Utility Shell

| No  | Utility Shell |                           Tampilan Command                           | Deskripsi                                                                        |
| :-: | :-----------: | :------------------------------------------------------------------: | -------------------------------------------------------------------------------- |
|  1  |      cd       |                     `cd <folder>` `cd ..` `cd /`                     | Merupakan alat dasar untuk melakukan navigasi pada filesystem.                   |
|  2  |      ls       |                          `ls <folder>` `ls`                          | Memperlihatkan konten yang ada pada current working directory.                   |
|  3  |      mv       | `mv <SRC> <DST>` <br /> `mv <SRC> /<DST>` <br /> `mv <SRC> ../<DST>` | Melakukan operasi rename dan/atau memindahkan file maupun folder.                |
|  4  |     mkdir     |                           `mkdir <folder>`                           | Membuat suatu folder baru pada current working directory.                        |
|  5  |      cat      |                             `cat <file>`                             | Menampilkan isi dari suatu file sebagai text file.                               |
|  6  |      cp       |                          `cp <file> <file>`                          | Melakukan copy file dari current working directory ke current working directory. |

[BACK](README.md)
