package main

func match(regexp string, text string) bool {
	if regexp[0] == '^' {
		return matchhere(regexp[1:], text)
	}

	for ; len(text) > 0; text = text[1:] {
		if matchhere(regexp, text) {
			return true
		}
	}

	return false
}

func matchhere(regexp string, text string) bool {
	if len(regexp) == 0 {
		return true
	}
	if regexp[1] == '*' {
		return matchstar(regexp[0], regexp[2:], text)
	}
	if regexp[0] == '$' && len(regexp[1:]) == 0 {
		return len(text) == 0
	}
	if len(text) > 0 && (regexp[0] == '.' || regexp[0] == text[0]) {
		return matchhere(regexp[1:], text[1:])
	}
	return false
}

func matchstar(c byte, regexp string, text string) bool {
	for ; len(text) > 0 && (text[0] == c || c == '.'); text = text[1:] {
		if matchhere(regexp, text) {
			return true
		}
	}
	return false
}
