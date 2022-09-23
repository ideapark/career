# GO CRYPTOGRAPHY

## Cryptography objectives

- Confidentiality

_confidentiality_ is the requirement that only the intended party can
read a given message.

- Integrity

_integrity_ is the requirement that a message’s contents cannot be
tampered with.

- Authenticity

_authenticity_ is the requirement that the provenance (or origin) of a
message can be trusted.

## Cryptography Terms

- The _plaintext_ is the original message.

- The _ciphertext_ is traditionally a message that has been
  transformed to provide confidentiality.

- A _cipher_ is a cryptographic transformation that is used to encrypt
  or decrypt a message.

- A _message authentication code_ (or _MAC_) is a piece of data that
  provides authenticity and integrity. A MAC algorithm is used both to
  generate and validate this code.

- To _encrypt_ a message is to apply a confidentiality transformation,
  but is often used to describe a transformation that satisfies all
  three goals.

- To _decrypt_ a message to reverse the confidentiality
  transformation, and often indicates that the other two properties
  have been verified.

- A _hash_ or _digest algorithm_ transforms some arbitrary message
  into a fixed-size output, also called a digest or hash. A
  cryptographic hash is such an algorithm that satisfies some specific
  security goals.

- A _peer_ or _party_ describes an entity involved in the
  communication process. It might be a person or another machine.

## Basic Security

- Authentication

_authentication_ means that the system verifies the identity of
parties interacting with the system.

	multifactor authentication:
	- something you know (such as password)
	- something you have (such as app authentication code)
	- something you are (such as biometrics)

- Authorisation

_authorisation_ verifies that they should be allowed to carry out this
interaction.

- Auditing

_auditing_ creates a log of security events that can be verified and
checked to ensure the system is providing security.

## RSA

- Modulus and Totient

Lets choose two primes: `p=11` and `q=13`. Hence the modulus is `n =
p⋅q = 143`. The totient of n `ϕ(n) = (p−1)⋅(q−1) = 120`.

- Key Generation

For the public key, a random prime number that has a greatest common
divisor (gcd) of 1 with `ϕ(n)`. So `e=7`, and to determine `d`, the
secret key, we need to find the inverse of `7` with `ϕ(n)`. This can
be done very easily and quickly with the `Extended Euclidean
Algorithm`, and hence `d=103`. This can be easily verified: `e⋅d = 1
mod ϕ(n)` and `7⋅103 = 721 = 1 mod 120`.

    Public  Key: (e, n)
    Private Key: (d, n)

- Example

Lets choose our plaintext message, `m=9`:

	Encryption: m^e mod n = 9^7    mod 143 = 48 = c
	Decryption: c^d mod n = 48^103 mod 143 = 9  = m
