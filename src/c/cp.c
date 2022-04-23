#include "header/filesystem.h"
#include "header/std_type.h"
#include "header/textio.h"
#include "header/fileio.h"
#include "header/program.h"
#include "header/utils.h"

void exit() {
  struct file_metadata meta;
  meta.node_name    = "shell";
  meta.parent_index = 0x00;

  exec(meta, 0x2000);
}

int main() {
  struct message msg;
  get_message(&msg);

  /* 
      TODO : Implementasi cp
  */

  exit();
}