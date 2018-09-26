# Source Control Management

OpenShift Online takes advantage of preexisting source control management (SCM)
systems hosted either internally (such as an in-house Git server) or externally
(for example, on GitHub, Bitbucket, etc.). Currently, OpenShift Online only
supports Git solutions.

SCM integration is tightly coupled with builds, the two points being:

- Creating a BuildConfig using a repository, which allows building your
  application inside of OpenShift Online. You can create a BuildConfig manually
  or let OpenShift Online create it automatically by inspecting your repository.

- Triggering a build upon repository changes.
