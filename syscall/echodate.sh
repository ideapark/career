#!/bin/bash

xgettext --keyword=_ --keyword=N_ --default-domain=echodate echodate.c

msgfmt echodate.po -o echodate.mo
