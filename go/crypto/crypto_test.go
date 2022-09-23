package crypto_test

import (
	"bytes"
	"crypto/rand"
	"errors"
	"io"
	"testing"

	"golang.org/x/crypto/nacl/secretbox"
)

const (
	KeySize   = 32
	NonceSize = 24
)

// GenerateKey creates a new random secret key.
func GenerateKey() (*[KeySize]byte, error) {
	key := new([KeySize]byte)
	_, err := io.ReadFull(rand.Reader, key[:])
	if err != nil {
		return nil, err
	}

	return key, nil
}

// GenerateNonce creates a new random nonce.
func GenerateNonce() (*[NonceSize]byte, error) {
	nonce := new([NonceSize]byte)
	_, err := io.ReadFull(rand.Reader, nonce[:])
	if err != nil {
		return nil, err
	}

	return nonce, nil
}

var (
	ErrEncrypt = errors.New("secret: encryption failed")
	ErrDecrypt = errors.New("secret: decryption failed")
)

// Encrypt generates a random nonce and encrypts the input using
// NaCl's secretbox package. The nonce is prepended to the
// ciphertext. A sealed message will the same size as the original
// message plus secretbox.Overhead bytes long.
func Encrypt(key *[KeySize]byte, message []byte) ([]byte, error) {
	nonce, err := GenerateNonce()
	if err != nil {
		return nil, ErrEncrypt
	}

	out := make([]byte, len(nonce))
	copy(out, nonce[:])
	out = secretbox.Seal(out, message, nonce, key)
	return out, nil
}

// Decrypt extracts the nonce from the ciphertext, and attempts to
// decrypt with NaCl's secretbox.
func Decrypt(key *[KeySize]byte, message []byte) ([]byte, error) {
	if len(message) < (NonceSize + secretbox.Overhead) {
		return nil, ErrDecrypt
	}

	var nonce [NonceSize]byte
	copy(nonce[:], message[:NonceSize])
	out, ok := secretbox.Open(nil, message[NonceSize:], &nonce, key)
	if !ok {
		return nil, ErrDecrypt
	}

	return out, nil
}

func TestNaCl(t *testing.T) {
	key, err := GenerateKey()
	if err != nil {
		t.Fatalf("NaCl: %s\n", err)
	}

	raw := []byte("golang.org/x/crypto/nacl")
	enc, _ := Encrypt(key, raw)
	dec, _ := Decrypt(key, enc)

	if !bytes.Equal(raw, dec) {
		t.Fatalf("raw: %s, enc: %s, dec: %s\n", raw, enc, dec)
	}
}
