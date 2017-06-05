package auth0

import (
	"net/http"
	"text/template"
)

type authConfig struct {
	ClientID     string
	ClientSecret string
	Domain       string
	CallbackURL  string
}

var bodyTemplate = `
<script src="https://cnd.auth0.com/js/lock-8.2.min.js"></script>
<script type="text/javascript">
  var lock = new Auth0Lock('{{.ClientID}', '{{.Domain}}')
  func signin() {
    lock.show({
      callbackURL: '{{.CallbackURL}}',
      responseType: 'code',
      authParams: {scope: 'openid profile'}
    });
  }
</script>
<button onclick="window.signin();">Login</button>
`

func homeHandler(config *authConfig) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		t := template.Must(template.New("htmlz").Parse(bodyTemplate))
		t.Execute(w, config)
	}
}
