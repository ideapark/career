/*
 * sysstat/core/main_parser.c - sysstat parser main engine
 *
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "core/config.h"
#include "core/main.h"
#include "irq/irq.h"
#include "sys/sys.h"
#include "task/task.h"
#include "proc/proc.h"

static parser_entry g_parserqueue[CALLBACKQUEUE_LEN] = {{
  .file   = NULL,
  .parser = NULL,
  .taken  = untaken,
}};

static int option_usage(int argc, char *argv[])
{
  static const char *help = "Usage:\n\t%s sample-data-dir sqlite-db-path\n";

  struct stat statbuf;
  const char *dir;

  if (argc != 3)
    goto fail;

  dir = argv[1];
  if (stat(dir, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
    fprintf(stdout, "------- sysparser.exe -------\n");
    fprintf(stdout, "sample-data-dir: %s\n", argv[1]);
    fprintf(stdout, " sqlite-db-path: %s\n", argv[2]);
    return 0;
  } else
    goto fail;

fail:
  fprintf(stderr, help, argv[0]);
  exit(-1);
}

int main(int argc, char *argv[])
{
  short i;
  char datafile[1024];

  (void)option_usage(argc, argv);

  g_parserqueue[0].file = IRQ_SAMPLEFILE;
  g_parserqueue[0].parser = irq_parser;
  g_parserqueue[0].taken = taken;

  g_parserqueue[1].file = TASK_SAMPLEFILE;
  g_parserqueue[1].parser = task_parser;
  g_parserqueue[1].taken = taken;

  g_parserqueue[2].file = SYS_SAMPLEFILE;
  g_parserqueue[2].parser = sys_parser;
  g_parserqueue[2].taken = taken;

  g_parserqueue[3].file = PROC_SAMPLEFILE;
  g_parserqueue[3].parser = proc_parser;
  g_parserqueue[3].taken = taken;

  for (i = 0; i < CALLBACKQUEUE_LEN; i++) {
    if (g_parserqueue[i].taken == taken) {
      strcpy(datafile, argv[1]);
      strcat(datafile, "/");
      strcat(datafile, g_parserqueue[i].file);
      g_parserqueue[i].parser(datafile, argv[2]);
    }
  }

  return 0;
}
