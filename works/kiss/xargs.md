# xargs

### You tell me how to eat each line

> find /usr/include -type f -iname '*.h' | head -20 | xargs wc -l

```
[lockrecv@thinkpad lockrecv]$ find /usr/include -type f -iname '*.h' | head -20 | xargs wc -l
    74 /usr/include/jconfig.h
   496 /usr/include/dbstl_utility.h
   645 /usr/include/pygobject-3.0/pygobject.h
    37 /usr/include/spiro.h
   491 /usr/include/libelf.h
   681 /usr/include/tiff.h
   101 /usr/include/wayland-server.h
    80 /usr/include/tdbc.h
    34 /usr/include/itcl2TclOO.h
   230 /usr/include/gnutls/crypto.h
   534 /usr/include/gnutls/abstract.h
  1438 /usr/include/gnutls/x509.h
   380 /usr/include/gnutls/openpgp.h
  2596 /usr/include/gnutls/gnutls.h
   148 /usr/include/gnutls/pkcs12.h
    63 /usr/include/gnutls/system-keys.h
   242 /usr/include/gnutls/compat.h
    79 /usr/include/gnutls/tpm.h
    77 /usr/include/gnutls/urls.h
   194 /usr/include/gnutls/x509-ext.h
  8620 total
```
