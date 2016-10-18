# Emacs

### The editor's God

> Emacs Key Notation

```
+------------------------------------------------------------+
| Prefix                     Meaning                         |
+------------------------------------------------------------+
| C-         (press and hold) the Control key                |
+------------------------------------------------------------+
| M-         the Meta key (the Alt key, on most keyboards)   |
+------------------------------------------------------------+
| S-         the Shift key (s.g. 'S-TAB' means Shift Tab)    |
+------------------------------------------------------------+
| DEL        the Backspace key (not the Delete key). Inside, |
|            is written as <backspace>.                      |
+------------------------------------------------------------+
| RET        the Return or Enter key                         |
+------------------------------------------------------------+
| SPC        the Space bar key                               |
+------------------------------------------------------------+
| ESC        the Escape key                                  |
+------------------------------------------------------------+
| TAB        the TAB key                                     |
+------------------------------------------------------------+
```

> Key Binding Remember Rules

C-x

prefix is for default and global binding that come with Emacs.

C-c

prefix is for users to define.

C-u

is for altering behaviors or commands. This is, one command
can behave differently depending on how many C-u you pressed
first before executing a command. Mostly you just have to hit
C-u once.

C-<number>

C-1, C-2... is similar to C-u, but passing a number to
a command. Usually, the number specifies how many times you
want to repeat a command.

> Built-in Help System

C-h m

runs describe-mode to see all the key bindings and
documentation of current major mode and minor modes of a
buffer.

C-h w

runs where-is to get which keystrokes invoke a given command.

C-h c

runs describe-key-briefly to find out what command is bound
to a key. For example, after C-h c, run C-x C-f gives you
find-files.

C-h k

runs describe-key to find out what command is bound to a key,
along with the documentation of the command. Use this if you
want to know how to use a command.

C-h e

runs view-echo-area-messages, allow you to see the logging of
echo area messages.

C-h v

runs describe-variable, and asks you for a variable; you can
TAB to complete a variable. This command is important, because
aside from describing a variable, it allows you to customize
the behavior of Emacs and 3rd party packages. But for now, you
don't need it.

C-h C-h

runs help-for-help. Use this command if you want to see a list
of available help commands. Remember, if you partially remember
a key binding, just press as much as you can remember and then
press C-h, Emacs will list available commands for that prefix.
Prefix C-h is no exception. C-h C-h simply returns all key
bindings and command of prefix C-h.

> Buffer

```
+------------------------------------------------------------+
|  Key                  Binding                              |
+------------------------------------------------------------+
| C-x C-s     Command: save-buffer                           |
|             Save the buffer at point                       |
+------------------------------------------------------------+
| C-x C-w     Command: write-file                            |
|             Save the buffer to a different file            |
+------------------------------------------------------------+
| C-x b       Command: switch-to-buffer                      |
|             Switch to a different buffer                   |
+------------------------------------------------------------+
| C-x k       Command: kill-buffer                           |
|             Kill a buffer. RET to kill the currently active|
|             one                                            |
+------------------------------------------------------------+
```

> Bookmark: Save Locations across Emacs Sessions

```
+------------------------------------------------------------+
|  Key            Binding                                    |
+------------------------------------------------------------+
| C-x r m     Command: bookmark-set                          |
|             Set bookmark at point. After executing the     |
|             command, a prompt asks for a name. Enter the   |
|             name and RET.                                  |
+------------------------------------------------------------+
| C-x r b     Command: bookmark-jump                         |
|             Jump to a saved bookmark, specified by user.   |
|             TAB for getting bookmark list.                 |
+------------------------------------------------------------+
| C-x r l     Command: bookmark-bmenu-list                   |
|             Open the list of all bookmarks.                |
+------------------------------------------------------------+
```

> Basic Motion Commands

Move forward one char: C-f (f stands for forward)
Move backward one char: C-b (b stands for backward)
Move upward one line: C-p (p stands for previous)
Move downward one line: C-n (n stands for next)

Move to beginning of line: C-a
Move to end of line: C-e
Move forward one word: M-f
Move backward one word: M-b

Scroll forward one screen: C-v, page down
Scroll backward one screen: M-v, page up
Move to the beginning of a sentence: M-a
Move to the end of a sentence: M-e
Recenter a screen: C-l
Re-position point to the top, middle and bottom of the current screen: M-r
Move to top of the buffer: M-<
Move to end of the buffer: M->
Move to the nth character: M-g c (c stands for character)
Move to the nth line: M-g l for Emacs < 23.2, M-g g for emacs >= 23.2 (l/g stands for line)

> Basic Editing Commands

Kill a character at the point: C-d
Kill entire line: C-S-DEL (remember, DEL is your <backspace> key)
Kill forward to the end of a word from current point: M-d
Kill backward to the beginning of a word from the current point: M-DEL
Kill all spaces at point: M-\
Kill all spaces except one at point: M-SPC
Kill to the end of line: C-k
Kill a sentence: M-k

> Useful Built-in Key Bindings for Navigating pairs

C-M-f

binds to forward-sexp, move forward over a balanced expression.

C-M-b

binds to backward-sexp, move backward over a balanced expression.

C-M-k

binds to kill-sexp, kill balanced expression forward.

C-M-t

binds to transpose-sexps, transpose expressions.

C-M-<SPC> or C-M-@

binds to mark-sexp, put mark after following expression.

> Basic Editing Commands

Kill a character at the point: C-d
Kill entire line: C-S-DEL (remember, DEL is your <backspace> key)
Kill forward to the end of a word from current point: M-d
Kill backward to the beginning of a word from the current point: M-DEL
Kill all spaces at point: M-\
Kill all spaces except one at point: M-SPC
Kill to the end of line: C-k
Kill a sentence: M-k

If you write code, you can quickly add comments or comment/uncomment
code with M-;
    If you do not highlight a text region, M-; adds a comment to the end of line.
    If you highlight  a region, M-; comments out the region.

> Dynamic Abbreviations

Completion in emacs: M-/

> Mark and Region

Place a mark in bufer with: C-SPC C-SPC
Go back to previous mark: C-u C-SPC
Cycle the global mark ring: C-x C-SPC

> Undo/redo

To undo: C-/ or C-x u

> Search for Text

C-s

Invokes isearch-forward, allows you to look forward from
the current point for something.

C-r

Invokes isearch-backward, allows you to look backward from
the current point.

M-x occur

Command occur lists all line that match a string or a regexp
and displays the search result in a buffer named *Occur*.

M-%

Execute query-replace. M-% asks you two inputs:
A string to be replaced.
A string to replace.

M-x rgrep

Search for text with external grep command and displays the
results in a buffer.

> Modeline

```
cs:ch-fr | buf | pos line | (major minor)
```

   cs: describes the character set of the text in the buffer.
   ch: describes editing state of current buffer.
        '--': buffer has the same contents as the corresponding file one the disk
        '**': buffer is modified
        '%*': read-only buffer is modified
        '%%': read-only buffer is unmodified
   fr: gives the selected frame name.
  buf: is buffer name.
  pos: is display the current position of your viewing screen.
 line: displays the current line number.
major: displays the current major mode.
minor: displays the current minor mode.

> Frame

```
+----------------------------------------------------------+
|  Key            Binding                                  |
+----------------------------------------------------------+
| C-x 5 C-f     Command: find-file-other-frame             |
|               Open file in a different frame             |
+----------------------------------------------------------+
| C-x 5 f       Command: find-file-other-frame             |
|               Same as C-x 5 C-f                          |
+----------------------------------------------------------+
| C-x 5 C-o     Command: display-buffer-other-frame        |
|               Open buffer in a different frame and move  |
|               point there                                |
+----------------------------------------------------------+
| C-x 5 .       Command: find-tag-other-frame              |
|               Find tag at point in a different frame     |
+----------------------------------------------------------+
| C-x 5 0       Command: delete-frame                      |
|               Delete the current frame point is in       |
+----------------------------------------------------------+
| C-x 5 2       Command: make-frame-command                |
|               Create a frame                             |
+----------------------------------------------------------+
| C-x 5 b       Command: switch-to-buffer-other-frame      |
|               Same as C-x 5 C-o                          |
+----------------------------------------------------------+
| C-x 5 d       Command: dired-other-frame                 |
|               Open a Dired buffer in another frame       |
+----------------------------------------------------------+
| C-x 5 m       Command: compose-mail-other-frame          |
|               Open another frame for composing email     |
+----------------------------------------------------------+
| C-x 5 o       Command: other-frame                       |
|               Cycle through available frames             |
+----------------------------------------------------------+
| C-x 5 r       Command: find-file-read-only-other-frame   |
|               Open file for read only in another frame   |
+----------------------------------------------------------+
```

> Window

C-x 2

split the current window into two horizontal windows.

C-x 3

split the current window into two vertical windows.

C-x 0

closes the window at point

C-x 1

closes all other windows except the current selected one.

C-x 4

common prefix for opening things in other buffer.

```
+----------------------------------------------------------+
|  Key            Binding                                  |
+----------------------------------------------------------+
| C-x 4 C-f   Command: find-file-other-window              |
|             Just like find-file discussed earlier,       |
|             except open file in new window. If the       |
|             current frame only has one window, a new     |
|             window is created.                           |
+----------------------------------------------------------+
| C-x 4 C-o   Command: display-buffer                      |
|             Select a buffer from buffer list and         |
|             display it in another window but not move    |
|             point to that window.                        |
+----------------------------------------------------------+
| C-x 4 .     Command: find-tag-other-window               |
|             Open the tag at point in another window      |
+----------------------------------------------------------+
| C-x 4 0     Command: kill-buffer-and-window              |
|             Just like C-x 0 but kill the buffer in that  |
|             window as well.                              |
+----------------------------------------------------------+
| C-x 4 a     Command: add-change-log-entry-other-window   |
|             Open another buffer and allow you to record  |
|             the change of the current editing file.      |
|             These days, you use version control system   |
|             to manage file changes, and Emacs dose this  |
|             better. Probaly this feature exists when     |
|             thing like Git does not exist.               |
+----------------------------------------------------------+
| C-x 4 b     Command: switch-to-buffer-other-window       |
|             Open a selected buffer in another window     |
|             and move point to that window.               |
+----------------------------------------------------------+
| C-x 4 c     Command: clone-indirect-buffer-other-windwow |
|             Clone the current buffer in another window   |
|             and give a different buffer name.            |
+----------------------------------------------------------+
| C-x 4 f     Command: find-file-other-window              |
|             Same as C-x 4 C-f                            |
+----------------------------------------------------------+
| C-x 4 m     Command: compose-mail-other-window           |
|             Write mail in other window. You can write    |
|             email and send it directly from Emacs.       |
+----------------------------------------------------------+
| C-x 4 r     Command: find-file-read-only-other-window    |
|             Similar to find-file-other-window, but open  |
|             for read-only.                               |
+----------------------------------------------------------+
| M-<next>    Command: scroll-other-window                 |
|             Scroll other window forward.                 |
+----------------------------------------------------------+
| M-<prior>   Command: scroll-other-window-down            |
|             Scroll other window backward.                |
+----------------------------------------------------------+
```

> Macro

```
+----------------------------------------------------------+
|  Key             Binding                                 |
+----------------------------------------------------------+
| F3 or C-x (    Start recording macro                     |
+----------------------------------------------------------+
| F4 or C-x )    Stop recording macro                      |
+----------------------------------------------------------+
| F4 or C-x e    Playback macro                            |
+----------------------------------------------------------+
```

> Versoin Control

```
+----------------------------------------------------------+
|  Key                     Binding                         |
+----------------------------------------------------------+
| C-x v =     Command: vc-diff                             |
|             Displays a diff showing the changes you've   |
|             made to the current files.                   |
+----------------------------------------------------------+
| C-x v ~     Command: vc-revision-other-window            |
|             Prompts you for a version number and shows   |
|             you that version of current file in another  |
|             window.                                      |
+----------------------------------------------------------+
| C-x v g     Command: vc-annotate                         |
|             Displays an annotated version of the file    |
|             showing, for each line, the commit where that|
|             line was last changed and by whom. On any    |
|             you can press l to view the log message for  |
|             that commit or d to view the associated diff.|
+----------------------------------------------------------+
| C-x v l     Command: vc-print-log                        |
|             Displays a log of previous changes to file.  |
|             When point is on a particular log entry, you |
|             can press d to view the diff associated with |
|             that change or f to view that version of the |
|             file                                         |
+----------------------------------------------------------+
| C-x v u     Command: vc-revert                           |
|             Revert working copies of the selected fileset|
|             to their repository contents. This asks for  |
|             confirmation if the buffer contents are not  |
|             identical to the working revision (except for|
|             keyword expansion)                           |
+----------------------------------------------------------+
```
