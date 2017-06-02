### Start a New Match [POST]

You can create a new match with this action. It takes information about the players
and will set up a new game. The game will start at round 1, and it will be **black**'s
turn to play. Per standard Go rules, **black** plays first.

+ Request (application/json)
{
	"gridsize": 19,
	"players": [
		{
			"color": "white",
			"name": "bob"
		},
		{
			"color": "black",
			"name": "alfred"
		}
	]
}

+ Response 201 (application/json)
	+ Headers
		Location: /matches/5a003b78-409e-4452-b456-a6f0dcee05bd
	+ Body
		{
			"id": "5a003b78-409e-4452-b456-a6f0dcee05bd",
			"started_at": "2015-08-05T08:40:50.620Z",
			"gridsize": 19,
			"turn": 0,
			"players": [
				{
					"color": "white",
					"name": "bob",
					"score": 10
				},
				{
					"color": "black",
					"name": "alfred",
					"score": 22
				}
			]
		}
