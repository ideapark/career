/*
 * sysstat/irq/irq.c - sysstat interrupts sample
 *
 * Copyright (c) Zhou Peng <p@ctriple.cn>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>

#include "core/config.h"
#include "core/main.h"
#include "irq/irq.h"
#include "util/mapped_helper.h"
#include "util/misc_helper.h"

static mapfile_t g_irqfile;
static irq_header g_header;

static int16_t irq_nameidx(irq_header *header, char *irqname)
{
	int16_t i;

	for (i = 0; i < IRQ_MAXNO; i++) {
		if (header->irq_names[i][0] == '\0')
			strncpy(&header->irq_names[i][0], irqname, IRQ_NAMELEN);
		if (strncmp(irqname, &header->irq_names[i][0], IRQ_NAMELEN) == 0)
			return i;
	}
	return -1;
}

static int softirq_snapshot(irq_header *header)
{
	FILE *fp;
	short cores, sno, i;
	size_t n;
	char *line = NULL, *token;
	char namebuf[IRQ_NAMELEN];
	char serial[IRQ_SERIAL] = {'\0'};

	/* initialized interrupt entry */
	irq_entry entry = {
		.timestamp =  0,
		.cpu       =  0,
		.irq_type  = -1,
		.name_idx  = -1,
		.irq_num   =  0,
	};

	cores = cpu_cores();

	if (access(SOFTIRQ_FILE, F_OK) == -1)
		goto fail;
	if ((fp = fopen(SOFTIRQ_FILE, "r")) == NULL)
		goto fail;

	sno = SOFTIRQ_SERIAL;
	entry.irq_type = SOFT_IRQ;
	while (getline(&line, &n, fp) != -1) {
		if (strchr(line, ':') == NULL)
			continue;
		token = strtok(line, ":");
		sscanf(token, "%s", namebuf);
		snprintf(serial, IRQ_SERIAL, "-%d", sno++);
		/*
		 * append '-digit' to interrupt name,
		 * in case of two different interrupts
		 * of the same name
		 */
		strcat(namebuf, serial);
		entry.name_idx = irq_nameidx(header, namebuf);
		for (i = 0; i < cores; i++) {
			entry.timestamp = g_timestamp;
			entry.cpu = i;
			token = strtok(NULL, " ");
			if (token != NULL)
				sscanf(token, "%"SCNd32, &entry.irq_num);
			else
				entry.irq_num = 0;
			mapped_write(&g_irqfile, (void *)&entry, sizeof(entry));
			header->count++;
		}
	}
	free(line);
	fclose(fp);
	return 0;

fail:
	fprintf(stderr, "softirq snapshot failed.\n");
	return -1;
}

static int hardirq_snapshot(irq_header *header)
{
	FILE *fp;
	short cores, sno, i;
	size_t n;
	char *line = NULL, *token;
	char namebuf[IRQ_NAMELEN];
	char serial[IRQ_SERIAL] = {'\0'};

	/* initialized interrupt entry */
	irq_entry entry = {
		.timestamp =  0,
		.cpu       =  0,
		.irq_type  = -1,
		.name_idx  = -1,
		.irq_num   =  0,
	};

	cores = cpu_cores();

	if (access(HARDIRQ_FILE, F_OK) == -1)
		goto fail;
	if ((fp = fopen(HARDIRQ_FILE, "r")) == NULL)
		goto fail;

	sno = HARDIRQ_SERIAL;
	entry.irq_type = HARD_IRQ;
	while (getline(&line, &n, fp) != -1) {
		if (strchr(line, ':') == NULL)
			continue;
		token = strtok(line, ":");
		sscanf(token, "%s", namebuf);
		snprintf(serial, IRQ_SERIAL, "-%d", sno++);
		/*
		 * append '-digit' to interrupt name,
		 * in case of two different interrupts
		 * of the same name
		 */
		strcat(namebuf, serial);
		entry.name_idx = irq_nameidx(header, namebuf);
		for (i = 0; i < cores; i++) {
			entry.timestamp = g_timestamp;
			entry.cpu = i;
			token = strtok(NULL, " ");
			if (token != NULL)
				sscanf(token, "%"SCNd32, &entry.irq_num);
			else
				entry.irq_num = 0;
			mapped_write(&g_irqfile, (void *)&entry, sizeof(entry));
			header->count++;
		}
	}
	free(line);
	fclose(fp);
	return 0;

fail:
	fprintf(stderr, "hardirq snapshot failed.\n");
	return -1;
}

static int write_header(irq_header *header)
{
	int fd;

	if ((fd = open(IRQ_SAMPLEFILE, O_RDWR, 0644)) == -1)
		goto fail;

	if (write(fd, header, sizeof(*header)) != sizeof(*header))
		fprintf(stderr, "irq write_header failed.\n");
	close(fd);

	return 0;

fail:
	fprintf(stderr, "write irq sample file header failed.\n");
	return -1;
}

/*
 * @brief: interrupts sample initialization
 */
void irq_init(void)
{
	short i;

	g_header.magic = SYSSTAT_MAGIC;
	g_header.count = 0;
	g_header.cpu_cores = cpu_cores();

	for (i = 0; i < IRQ_MAXNO; i++)
		memset(&g_header.irq_names[i][0], '\0', IRQ_NAMELEN);

	mapped_open(&g_irqfile, IRQ_SAMPLEFILE);
	mapped_write(&g_irqfile, &g_header, sizeof(g_header));
}

/*
 * @brief: interrupts sample take one snapshot
 */
void irq_run(void)
{
	softirq_snapshot(&g_header);
	hardirq_snapshot(&g_header);
}

/*
 * @brief: finish interrupts sample, close mapped file and write irq_header
 */
void irq_exit(void)
{
	mapped_close(&g_irqfile);
	write_header(&g_header);
}
