struct elf_hdr {
	char magic[4] = "\177ELF"; /* magic number */
	char class;                /* address size, 1: 32 bit, 2: 64 bit */
	char byteorder;            /* 1: little-endian, 2: big-endian */
	char hversion;             /* header version, always 1 */
	char pad[9];
	short filetype;            /* file type: 1: relocatable, 2: executable, 3: shared object, 4: core image */
	short archtype;            /* 2: SPARC, 3: x86, 4: 68K, etc. */
	int fversion;              /* file version, always 1 */
	int entry;                 /* entry point if executable */
	int phdrpos;               /* file position of program header or 0 */
	int shdrpos;               /* file position of section header or 0 */
	int flags;                 /* architecture specific flags, usually 0 */
	short hdrsize;             /* size of this ELF header */
	short phdrent;             /* size of an entry in program header */
	short phdrcnt;             /* number of entries in program header or 0 */
	short shdrent;             /* size of an entry in section header */
	short phdrent;             /* number of entries in section header or 0 */
	short strsec;              /* section number that contains section name strings */
};
