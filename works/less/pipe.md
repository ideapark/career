# pipe

### Pipe chains multiple programs to do much more complicated work

> find /usr/lib/ -iname 'lib*.so' -type f | rev | cut -d '/' -f1 | rev | uniq | sort -r | tail -n 20

```
[esc@thinkpad esc]$ find /usr/lib/ -iname 'lib*.so' -type f | rev | cut -d '/' -f1 | rev | uniq | sort -r | tail -n 20
libapplicationsmenu.so
libanl-2.23.so
libalsa-util.so
libaep.so
libadwaita.so
libactions.so
liba11y-settings.so
liba11y-keyboard.so
libSegFault.so
libLTO.so
libLLVM-3.8.so
libKSC.so
libJISX0213.so
libJIS.so
libISOIR165.so
libGB.so
libCNS.so
libBrokenLocale-2.23.so
lib4758cca.so
Libproxy.so
```
