# Hard Links

When a file is created with open() or creat(), the system finds an unused i-node
and assigns it to the new file. I creates the directory entry for the file, with
the file's name and inode number in it.

Since directory entries associate filenames with inodes, it is possible for one
file have multiple names. Each directory entry referring to the same inode is
called a link, or hard link.

HARD LINKS ALL REFER TO THE SAME FILE.


# Symbolic Links

A symbolic link (soft link) is a special kind of file (just as a directory is a
special kind of file). The contents of the file are the pathname of the file
being "pointed to."

The file pointed to by the link need not exist. The system detects this at
runtime and acts appropriately.


# Hard vs Symbolic

Symbolic link take up extra disk space, requiring a separate inode and data
block. Hard links take up only a directory slot.

Symbolic link add overhead. The kernel has to work harder to resolve a pathname
containing symbolic links.

Symbolic link can introduce "loops". The kernel has to be able to detect this
case and produce an error message.

Symbolic link is easy to break. If you move the pointed-to file to a different
location or rename it, the symbolic link is no longer valid. This can't happen
with a hard link.
