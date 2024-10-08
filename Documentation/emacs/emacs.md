# Emacs

## Basic

    ┌─────────────────────────────┬──────────────────────────────────────────────────────────┐
    │                         UNDO│ C-/                                                      │
    ├─────────────────────────────┼──────────────────────────────────────────────────────────┤
    │        Find (or Create) file│ C-x C-f                                                  │
    ├─────────────────────────────┼──────────────────────────────────────────────────────────┤
    │                    Save file│ C-x C-s                                                  │
    ├─────────────────────────────┼──────────────────────────────────────────────────────────┤
    │                   Exit Emacs│ C-x C-c                                                  │
    ├─────────────────────────────┼──────────────────────────────────────────────────────────┤
    │Quit (i.e. interrupt) command│ C-g                                                      │
    └─────────────────────────────┴──────────────────────────────────────────────────────────┘


## Move & Delete

    ┌─────────────────────┬──────────────────────────────────────────────────────────────────┐
    │                     │                        Operation                                 │
    │ Cursor Motion       ├───────────────────────────┬──────────────────────────────────────┤
    │                     │               Move        │          Delete                      │
    ├─────────────────────┼─────────────┬─────────────┼─────────────┬────────────────────────┤
    │     Amount          │   forward   │   backward  │   forward   │ backward               │
    ├─────────────────────┼─────────────┼─────────────┼─────────────┼────────────────────────┤
    │ Characters          │ C-f         │ C-b         │ C-d         │ DEL                    │
    ├─────────────────────┼─────────────┼─────────────┼─────────────┼────────────────────────┤
    │ Words               │ M-f         │ M-b         │ M-d         │ M-DEL                  │
    ├─────────────────────┼─────────────┼─────────────┼─────────────┼────────────────────────┤
    │ Lines               │ C-n         │ C-p         │ C-k (to EOL)│ C-SPC C-a C-w          │
    ├─────────────────────┼─────────────┼─────────────┼─────────────┼────────────────────────┤
    │ Sentences           │ M-e         │ M-a         │ M-k         │ C-x DEL                │
    ├─────────────────────┼─────────────┼─────────────┼─────────────┼────────────────────────┤
    │ Expressions         │ C-M-f       │ C-M-b       │ C-M-k       │ C-M-DEL                │
    ├─────────────────────┼─────────────┼─────────────┼─────────────┴────────────────────────┤
    │ Paragraphs          │ M-}         │ M-{         │(no standard bindings for delete cmds)│
    ├─────────────────────┼─────────────┼─────────────┼──────────────────────────────────────┤
    │ End/Start of line   │ C-e         │ C-a         │(repeat count goes to following lines)│
    ├─────────────────────┼─────────────┼─────────────┼──────────────────────────────────────┤
    │ End/Start of buffer │ M->         │ M-<         │(no repeat count)                     │
    └─────────────────────┴─────────────┴─────────────┴──────────────────────────────────────┘


## Cutting and Pasting

    ┌────────┬───────────────────────────────────────────────────────────────────────────────┐
    │ C-SPC  │ Mark one end of region                                                        │
    ├────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ C-w    │ Cut (after you mark and move to other end)                                    │
    ├────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ M-w    │ Copy (after you mark and move to other end)                                   │
    ├────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ C-y    │ Yank (paster) most recently killed (cut or copied); will also use text        │
    │        │ currently selected in another application                                     │
    ├────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ M-y    │ Next most recently killed (do C-y first, repeat M-y to cycle through all)     │
    │        │ To make cut/copy/paste behave as it does in other apps, do M-x cua-mode, or   │
    │        │ put (cua-mode) in your .emacs to enable in every session.                     │
    └────────┴───────────────────────────────────────────────────────────────────────────────┘


## Files and Buffers

    ┌─────────────┬──────────────────────────────────────────────────────────────────────────┐
    │ C-x C-f     │ Find file (or create if not there); prompts for file name                │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-x C-s     │ Save file                                                                │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-x C-w     │ Write file; prompts for new name                                         │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-x s       │ Save modified buffers; asks about each                                   │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-x b       │ Select buffer; prompts for buffer name                                   │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-x C-b     │ List buffers; shows in other window                                      │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-x k       │ Kill buffer; prompts for buffer name                                     │
    └─────────────┴──────────────────────────────────────────────────────────────────────────┘


## Searching/Replacing

    ┌────────────────────────┬───────────────────────────────────────────────────────────────────────────────┐
    │ C-s                    │ Incremental search forward; searches as you type                              │
    ├────────────────────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ C-r                    │ Incremental search backward                                                   │
    ├────────────────────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ C-M-s                  │ Regexp search forward (there are differences in Emacs regexp syntax)          │
    ├────────────────────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ C-M-r                  │ Regexp search backward                                                        │
    ├────────────────────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ M-x replace-string RET │ String replace from here to end of buffer; prompts for string and replacement │
    ├────────────────────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ M-x query-replace RET  │ String replace from there to end of buffer; querying for each occurrence      │
    ├────────────────────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ M-x grep RET           │ Prompts for a grep command, shows hits in a buffer                            │
    ├────────────────────────┼───────────────────────────────────────────────────────────────────────────────┤
    │ C-x `                  │ Visit next grep hit                                                           │
    └────────────────────────┴───────────────────────────────────────────────────────────────────────────────┘


## Scrolling and Windows

    ┌─────────┬──────────────────────────────────────────────────────────────────────────────┐
    │ C-v     │ Scroll down (toward end of buffer)                                           │
    ├─────────┼──────────────────────────────────────────────────────────────────────────────┤
    │ M-v     │ Scroll up (toward beginning of buffer)                                       │
    ├─────────┼──────────────────────────────────────────────────────────────────────────────┤
    │ C-M-v   │ Scroll other window down                                                     │
    ├─────────┼──────────────────────────────────────────────────────────────────────────────┤
    │ C-x 1   │ One window on current buffer                                                 │
    ├─────────┼──────────────────────────────────────────────────────────────────────────────┤
    │ C-x 2   │ Split window vertically                                                      │
    ├─────────┼──────────────────────────────────────────────────────────────────────────────┤
    │ C-x 3   │ Split window horizontally                                                    │
    ├─────────┼──────────────────────────────────────────────────────────────────────────────┤
    │ C-x ^   │ Grow window vertically; prefix is number of lines                            │
    └─────────┴──────────────────────────────────────────────────────────────────────────────┘


## Command-related Stuff

    ┌─────────────┬──────────────────────────────────────────────────────────────────────────┐
    │ ESC ESC ESC │ Get me out of where I am now                                             │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-u #       │ Prefix numeric arg # (digits with optional "-" sign) to next cmd         │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-g         │ Stop a command in progress, or quit out of a partially entered command   │
    └─────────────┴──────────────────────────────────────────────────────────────────────────┘


## Getting Help

    ┌─────────────┬──────────────────────────────────────────────────────────────────────────┐
    │ C-h k       │ Show command documentation; prompts for keystrokes                       │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-h a       │ "Command apropos"; prompts for regexp and shows all matching commands    │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-h c       │ Show command name on message line; prompts for keystrokes                │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-h f       │ Describe function; prompts for command or function name, shows           │
    │             │ documentation in other window                                            │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-h i       │ Info browser; gives access to online documentation for emacs and more    │
    └─────────────┴──────────────────────────────────────────────────────────────────────────┘


## Miscellaneous

    ┌─────────────┬──────────────────────────────────────────────────────────────────────────┐
    │ C-_ or C-x u│ Undo/redo (a series of these keeps undoing; after doing something else,  │
    │             │ C-_ or C-x u will undo the undo's)                                       │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-q         │ Quoted insert; inserts the next character typed, even if it is a control │
    │             │ or meta character                                                        │
    ├─────────────┴──────────────┬───────────────────────────────────────────────────────────┤
    │ M-x shell-strip-ctrl-m RET │ Flush ^M at end of line                                   │
    ├─────────────┬──────────────┴───────────────────────────────────────────────────────────┤
    │ C-z         │ Suspend/iconify emacs (type "%emacs" in invoking shell to get it back)   │
    ├─────────────┼──────────────────────────────────────────────────────────────────────────┤
    │ C-x C-c     │ Exit emacs (asks about unsaved buffers and running programs)             │
    └─────────────┴──────────────────────────────────────────────────────────────────────────┘
