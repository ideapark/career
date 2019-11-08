# git

### SCM that you should use every day

> Git environment configuration

```
[global]
    git config --global user.name "Zhou Peng"
    git config --global user.email "p@ctriple.cn"

    git config --global color.ui auto
    git config --global core.editor vim

    git config --global merge.tool vimdiff
    git config --global mergetool.prompt false

[project]
    git config core.autocrlf false

[env]
    git config --list
```

> .gitignore

```
[Git internal]

    Git is designed for #TEXT# file version managment; Binary file is not good
    for Git, which can slow down git speed heavily.

[What's text file]

    Files that can be open by Notepad++, VIM etc. Most important, can be read
    and unstandand by human directly. Such as C/C++/Java/C# source code, XML
    CSS.

[What's binary file]

    All files but text file, such as executable file, picture, tar, rar, zip,
    word, excel, ppt, chm, pdf, iso, ..., too much, too dangerous.

[HOW-TO]

    Write .gitignore to ignore unwanted files, make the word clean and better.

[.gitignore]

  +------------------------------------------------------------+
  |  # Comment - ignore                                        |
  |                                                            |
  |  # ignore all file suffix by .a or .o                      |
  |  *.[oa]                                                    |
  |                                                            |
  |  # keep lib.a                                              |
  |  !lib.a                                                    |
  |                                                            |
  |  # ignore TODO only under root direcotry, no subdir/TODO   |
  |  /TODO                                                     |
  |                                                            |
  |  # ignore all files under build/ directory                 |
  |  build/                                                    |
  |                                                            |
  |  # ignore doc/notes.txt, no doc/server/arch.txt            |
  |  doc/*.txt                                                 |
  |                                                            |
  |  # ignore all .txt files in the doc/ directory             |
  |  doc/**/*.txt                                              |
  +------------------------------------------------------------+
```

> git commit guide

```
1. Don't submit any whitespace errors, git provides an easy way
   to check for this, before you commit, run

        git diff --check

   which identifies possible whitespace errors and lists them
   for you.

2. Try to make each commit a logically separate changeset. If
   you can, try to make your changes digestible - don't code for
   a whole weekend on five different issues and then submit them
   all as one massive commit on Monday. Even if you don't commit
   during the weekend, use the staging area on Monday to split
   your work into at least one commit per issue, with a userfull
   message per commit. If some of the changes modify the same
   file, try to use git add --patch to partially stage files.

3. As a general rule, your messages should start with a single
   line that's no more than about 50 characters and that
   describes the changeset concisely, followed by a blank line,
   followed by a more detailed explanation. Template written by
   Tim Pope:


   Short (50 chars or less) summary of changes

   More detailed explanatory text, if necessary. Wrap it to
   about 72 characters or so. In some contexts, the first line
   is treated as the subject of an email and the reset of the
   text as the body. The blank line separating the summary from
   the body is critical (unless you omit the body entirely).
   tools like rebase can get confused if you run the two
   tegether.

   Further paragraphs come after blank lines.

     - Bullet points are okay, too

     - Typically a hyphen or asterisk is used for the bullet,
       preceded by a single space, with blank lines in between,
       but conventions vary here
```

> git tricks

```
1. Who changed my code?

    git blame [COMMIT-SHA1 --] file-name

2. Review repository log?

    git log --oneline --graph --decorate [--all|COMMIT-SHA1]

3. Partly commit a file?

    git add -p file-name

4. Squash commits?

    git rebase -i HEAD~[n]

5. Stash uncommit change?

    git stash [list|apply|pop]

6. Commit lost+found?

    git fsck --lost-found

7. Choose what to merge?

    git cherry-pick COMMIT-SHA1

8. Checkout to last branch?

    git checkout -
```
