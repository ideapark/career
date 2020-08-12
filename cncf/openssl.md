# OpenSSL

## Some of the abbreviations related to certificates

- SSL: Secure Socket Layer
- CSR: Certificate Signing Request
- TLS: Transport Layer Security
- PEM: Privacy Enhanced Mail
- DER: Distinguished Encoding Rules
- SHA: Secure Hash Algorithm
- PKCS: Public-Key Cryptography Standards

## Usage example

- Create new private key and certificate signing request

```bash
openssl req -out geekflare.csr -newkey rsa:2048 -nodes -keyout geekflare.keyout
```

Above command will generate CSR and 2048-bit RSA key file. If you intend to use
this certificate in Apache or Nginx, then you need to send this CSR file to
certificate issuer authority, and they will give you signed certificate mostly
in der or pem format which you need to configure in Apache or Nginx web server.

- Create self-signed certificate

```bash
openssl req -x509 -sha256 -nodes -newkey rsa:2048 -keyout gfselfsigned.key -out gfcert.pem
```

Above command will generate a self-signed certificate and key file with 2048-bit
RSA. I have also included sha256 as it’s considered most secure at the moment.

Tip: by default, it will generate self-signed certificate valid for only one
month so you may consider defining –days parameter to extend the validity.

Ex: to have self-signed valid for two years.

```bash
openssl req -x509 -sha256 -nodes -days 730 -newkey rsa:2048 -keyout gfselfsigned.key -out gfcert.pem
```

- Verify CSR file

```bash
openssl req -noout -text -in geekflare.csr
```

Verification is essential to ensure you are sending CSR to issuer authority with
required details.

- Create RSA private key

```bash
openssl genrsa -out private.key 2048
```

If you just need to generate RSA private key, you can use above command. I have
included 2048 for stronger encryption.

- Remove passphrase from key

```bash
openssl rsa -in certkey.key -out nopassphrase.key
```

If you are using passphrase in key file and using Apache then every time you
start, you have to enter the password. If you are annoyed with entering a
password, then you can use above openssl rsa -in geekflare.key -check to remove
the passphrase key from existing key.

- Verify private key

```bash
openssl rsa -in certkey.key -check
```

If you doubt on your key file, you can use above command to check.

- Verify certificate file

```bash
openssl x509 -in certfile.pem -text -noout
```

If you would like to validate certificate data like CN, OU, etc. then you can
use above command which will give you certificate details.

- Verify the certificate signer authority

```bash
openssl x509 -in certfile.pem -noout -issuer -issuer_hash
```

Certificate issuer authority signs every certificate and in case you need to
check them, you can use above command.

- Check hash value of a certificate

```bash
openssl x509 -noout -hash -in bestflare.pem
```

- Convert DER to PEM format

```bash
openssl x509 -inform der -in sslcert.der -out sslcert.pem
```

Usually, certificate authority will give you SSL cert in .der format, and if you
need to use them in apache or .pem format, you can use above command to convert
them.

- Convert PEM to DER format

```bash
openssl x509 -outform der -in sslcert.pem -out sslcert.der
```

In case you need to change .pem format to .der

- Convert certificate and private key to PKCS#12 format

```bash
openssl pkcs12 -export -out sslcert.pfx -inkey key.pem -in sslcert.pem
```

If you need to use a cert with the java application or with any other who accept
only PKCS#12 format, you can use above command, which will generate single pfx
containing certificate & key file.

Tip: you can also include chain certificate by passing –chain as below.

```bash
openssl pkcs12 -export -out sslcert.pfx -inkey key.pem -in sslcert.pem -chain cacert.pem
```

- Create CSR using existing private key

```bash
openssl req -out certificate.csr -key existing.key -new
```

If you don’t want to create a new private key instead using existing one, you
can go with above command.

- Check contents of PKCS12 format cert

```bash
openssl pkcs12 -info -nodes -in cert.p12
```

PKCS12 is binary format so you won’t be able to view the content in notepad or
another editor. So you got to use above command to see the contents of PKCS12
format file.

- Convert PKCS12 format to PEM certificate

```bash
openssl pkcs12 -in cert.p12 -out cert.pem
```

If you wish to use existing pkcs12 format with Apache or just in pem format,
this will be useful.

- Test SSL certificate of particular URL

```bash
openssl s_client -connect yoururl.com:443 -showcerts
```

I use this quite often to validate the SSL certificate of particular URL from
the server. This is very handy to validate the protocol, cipher, and cert
details.

- Find out openssl version

```bash
openssl version
```

If you are responsible for ensuring OpenSSL is secure then probably one of the
first things you got to do is to verify the version.

- Check PEM file certificate expiration date

```bash
openssl x509 -noout -in certificate.pem -dates
```

Useful if you are planning to put some monitoring to check the validity. It will
show you date in notBefore and notAfter syntax. notAfter is one you will have to
verify to confirm if a certificate is expired or still valid.

- Check certificate expiration date of SSL URL

```bash
openssl s_client -connect secureurl.com:443 2>/dev/null | openssl x509 -noout -enddate
```

Another useful if you are planning to monitor SSL cert expiration date remotely
or particular URL.

- Check if SSL v2 or v3 is accepted on URL

To check SSL v2

```bash
openssl s_client -connect secureurl.com:443 -ssl2
```

To check SSL v3

```bash
openssl s_client -connect secureurl.com:443 -ssl3
```

To check TLS 1.0

```bash
openssl s_client -connect secureurl.com:443 -tls1
```

To check TLS 1.1

```bash
openssl s_client -connect secureurl.com:443 -tls1_1
```

To check TLS 1.2

```bash
openssl s_client -connect secureurl.com:443 -tls1_2
```

If you are securing web server and need to validate if SSL V2/V3 is enabled or
not, you can use above command. If activated, you will get “CONNECTED” else
“handshake failure.”

- Verify if particular cipher is accepted on URL

```bash
openssl s_client -cipher 'ECDHE-ECDSA-AES256-SHA' -connect secureurl:443
```

If you are working on security findings and pen test results show some of the
weak ciphers is accepted then to validate, you can use above command.

Of course, you will have to change the cipher and URL, which you want to test
against. If the mentioned cipher is accepted, then you will get “CONNECTED”
else “handshake failure.”
