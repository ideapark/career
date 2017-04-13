// Don't communicate by sharing memory, share memory by communicating.
package chat

import (
	"errors"
	"io"
	"net"
)

type Mux struct {
	ops chan func(map[net.Addr]net.Conn)
}

func (m *Mux) Add(conn net.Conn) {
	m.ops <- func(m map[net.Addr]net.Conn) {
		m[conn.RemoteAddr()] = conn
	}
}

func (m *Mux) Remove(addr net.Addr) {
	m.ops <- func(m map[net.Addr]net.Conn) {
		delete(m, addr)
	}
}

func (m *Mux) SendMsg(msg string) error {
	result := make(chan error, 1)
	m.ops <- func(m map[net.Addr]net.Conn) {
		for _, conn := range m {
			_, err := io.WriteString(conn, msg)
			if err != nil {
				result <- err
				return
			}
		}
		result <- nil
	}
	return <-result
}

func (m *Mux) PrivateMsg(addr net.Addr, msg string) error {
	result := make(chan net.Conn, 1)
	m.ops <- func(m map[net.Addr]net.Conn) {
		result <- m[addr]
	}
	conn := <-result
	if conn == nil {
		return errors.New("client not registered.")
	}
	_, err := io.WriteString(conn, msg)
	return err
}

func (m *Mux) loop() {
	conns := make(map[net.Addr]net.Conn)
	for op := range m.ops {
		op(conns)
	}
}
