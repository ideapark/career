package npcs

import (
	"testing"
)

func TestNonPlayerCharacter(t *testing.T) {
	mob := NonPlayerCharacter{Name: "Alfred"}
	t.Log(mob)

	hortense := NonPlayerCharacter{
		Name: "Hortense",
		Loc:  Location{X: 10.0, Y: 10.0, Z: 10.0},
	}
	t.Log(hortense)

	t.Logf("Alfred is %f units from Hortense.\n", mob.DistanceTo(hortense))
}
