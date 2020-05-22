# Identifier Design with URIs

## URI Format

> URI = scheme "://" authority "/" path [ "?" query ] [ "#" fragment ]

- Forward slash separator (/) must be used to indicate a hierarchical relationship

> http://api.canvas.restapi.org/shapes/polygons/quadrilaterals/squares

- A trailing forward slash (/) should not be included in URIs

- Hyphens (-) should be used to improve the readability of URIs

> http://api.example.restapi.org/blogs/mark-masse/entries/this-is-my-first-post

- Underscores (_) should not be used in URIs

- Lowercase letters should be preferred in URI paths

> http://api.example.restapi.org/my-folder/my-doc (1)
> HTTP://API.EXAMPLE.RESTAPI.ORG/my-folder/my-doc (2), equals to (1)
> http://api.example.restapi.org/My-Folder/my-doc (3), not the same as (1)

- File extensions should not be included in URIs

> http://api.college.restapi.org/students/3248234/transcripts/2005/fall.json (bad)
> http://api.college.restapi.org/students/3248234/transcripts/2005/fall

## URI Authority Design

- Consistent subdomain names should be used for your APIs

> http://api.soccer.restapi.org

- Consistent subdomain names should be used for your client developer portal

> http://developer.soccer.restapi.org

## Resource Modeling

Each of these URIs should also identify an addressable resource:

> http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet
> http://api.soccer.restapi.org/leagues/seattle/teams
> http://api.soccer.restapi.org/leagues/seattle
> http://api.soccer.restapi.org/leagues
> http://api.soccer.restapi.org

## Resource Archetypes

- Document

> http://api.soccer.restapi.org/leagues/seattle
> http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet
> http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet/players/mike

- Collection

> http://api.soccer.restapi.org/leagues
> http://api.soccer.restapi.org/leagues/seattle/teams
> http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet/players

- Store

> PUT /users/1234/favorites/alonso

- Controller

> POST /alerts/245743/resend

## URI Path Design

- A singular noun should be used for document names

> http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet/players/claudio

- A plural noun should be used for collection names

> http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet/players

- A plural noun should be used for store names

> http://api.music.restapi.org/artists/mikemassedotcom/playlists

- A verb or verb phrase should be used for controller names

> http://api.college.restapi.org/students/morgan/register
> http://api.example.restapi.org/lists/4324/dedupe
> http://api.ognom.restapi.org/dbs/reindex
> http://api.build.restapi.org/qa/nightly/runTestSuite

- Variable path segments may be substituted with identity-based values

> http://api.soccer.restapi.org/leagues/{leagueId}/teams/{teamId}/players/{playerId}

> http://api.soccer.restapi.org/leagues/seattle/teams/trebuchet/players/21
> http://api.soccer.restapi.org/games/3fd65a60-cb8b-11e0-9572-0800200c9a66

- CRUD function names should not be used in URIs

1. Good

> DELETE /users/1234

2. Bad

> GET /deleteUser?id=1234
> GET /deleteUser/1234
> DELETE /deleteUser/1234
> POST /users/1234/delete

## URI Query Design

> http://api.college.restapi.org/students/morgan/send-sms
> http://api.college.restapi.org/students/morgan/send-sms?text=hello

- The query component of a URI may be used to filter collections or stores

> GET /users
> GET /users?role=admin

- The query component of a URI should be used to paginate collection or store results

> GET /users?pageSize=25&pageStartIndex=50
> POST /users/search
