# Identifier Design with URIs

## URI Format

> URI = scheme "://" authority "/" path [ "?" query ] [ "#" fragment ]

- Forward slash separator (/) must be used to indicate a hierarchical relationship

1. http://api.canvas.restapi.org/shapes/polygons/quadrilaterals/squares

- A trailing forward slash (/) should not be included in URIs

- Hyphens (-) should be used to improve the readability of URIs

1. http://api.example.restapi.org/blogs/mark-masse/entries/this-is-my-first-post

- Underscores (_) should not be used in URIs

- Lowercase letters should be preferred in URI paths

1. http://api.example.restapi.org/my-folder/my-doc (1)
2. HTTP://API.EXAMPLE.RESTAPI.ORG/my-folder/my-doc (2), equals to (1)
3. http://api.example.restapi.org/My-Folder/my-doc (3), not the same as (1)

- File extensions should not be included in URIs

1. http://api.college.restapi.org/students/3248234/transcripts/2005/fall.json (bad)
2. http://api.college.restapi.org/students/3248234/transcripts/2005/fall

## URI Authority Design

- Consistent subdomain names should be used for your APIs

1. http://api.soccer.restapi.org

- Consistent subdomain names should be used for your client developer portal

1. http://developer.soccer.restapi.org

## Resource Modeling

Each of these URIs should also identify an addressable resource:

1. http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet
2. http://api.soccer.restapi.org/leagues/seattle/teams
3. http://api.soccer.restapi.org/leagues/seattle
4. http://api.soccer.restapi.org/leagues
5. http://api.soccer.restapi.org

## Resource Archetypes

- Document

1. http://api.soccer.restapi.org/leagues/seattle
2. http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet
3. http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet/players/mike

- Collection

1. http://api.soccer.restapi.org/leagues
2. http://api.soccer.restapi.org/leagues/seattle/teams
3. http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet/players

- Store

> PUT /users/1234/favorites/alonso

- Controller

> POST /alerts/245743/resend

## URI Path Design

- A singular noun should be used for document names

1. http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet/players/claudio

- A plural noun should be used for collection names

1. http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet/players

- A plural noun should be used for store names

1. http://api.music.restapi.org/artists/mikemassedotcom/playlists

- A verb or verb phrase should be used for controller names

1. http://api.college.restapi.org/students/morgan/register
2. http://api.example.restapi.org/lists/4324/dedupe
3. http://api.ognom.restapi.org/dbs/reindex
4. http://api.build.restapi.org/qa/nightly/runTestSuite

- Variable path segments may be substituted with identity-based values

1. http://api.soccer.restapi.org/leagues/{leagueId}/teams/{teamId}/players/{playerId}
2. http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet/players/21
3. http://api.soccer.restapi.org/games/3fd65a60-cb8b-11e0-9572-0800200c9a66

- CRUD function names should not be used in URIs

Good

1. DELETE /users/1234

Bad

1. GET /deleteUser?id=1234
2. GET /deleteUser/1234
3. DELETE /deleteUser/1234
4. POST /users/1234/delete

## URI Query Design

1. http://api.college.restapi.org/students/morgan/send-sms
2. http://api.college.restapi.org/students/morgan/send-sms?text=hello

- The query component of a URI may be used to filter collections or stores

1. GET /users
2. GET /users?role=admin

- The query component of a URI should be used to paginate collection or store results

1. GET /users?pageSize=25&pageStartIndex=50
2. POST /users/search
