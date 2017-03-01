struct aout_hdr {
	int a_magic;  /* magic number            */
	int a_text;   /* text segment size       */
	int a_data;   /* initialized data size   */
	int a_bss;    /* uninitialized data size */
	int a_syms;   /* symbol table size       */
	int a_entry;  /* entry point             */
	int a_trsize; /* text relocation size    */
	int a_drsize; /* data relocation size    */
};
