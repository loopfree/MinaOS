// Parameter dapat diganti lagi nantinya

void cd() {
  // implemen cd
}

void ls() {
  // implemen ls
}

void mv() {
  // implemen mv
}

void mkdir() {
  // implemen mkdir
}

void cat() {
  // implemen cat
}

void cp() {
  // implemen cp
}

void shell() {
  char input_buf[64];
  char path_str[128];
  byte current_dir = FS_NODE_P_IDX_ROOT;

  while (true) {
    printString("MinaOS:");
    printCWD(path_str, current_dir);
    printString("$");
    readString(input_buf);

    if (strcmp(input_buf, "cd")) {
      // Utility cd
    }
    else {
      printString("Unknown command\r\n");
    }
  }
}
