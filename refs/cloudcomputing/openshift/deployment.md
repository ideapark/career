# Deployment

## Deployment Strategies

A deployment strategy is a way to change or upgrade an application. The aim is
to make the change without downtime in a way that the user barely notices the
improvements.

- blue-green deployment

The new version (the blue version) is brought up for testing and evaluation,
while the users still use the stable version (the green version). When ready,
the users are switched to the blue version. If a problem arises, you can switch
back to the green version.

- A/B versions

A/B versions are both active at the same time and some users use one version,
and some users use the other version. This can be used for experimenting with
user interface changes and other features to get user feedback. It can also be
used to verify proper operation in a production context where problems impact a
limited number of users.

- canary deployment

A canary deployment test the new version but when the problem is detected it
quickly falls back to the previous version. This can be done with both of the
above strategies.

- route based deployment

The route based deployment strategies do not scale the number of pods in the
services. To maintain desired performance characteristics the deployment
configurations may need to be scaled.

## Deployment Strategy Considerations

- Long running connections need to be handled gracefully

- Database conversions can get tricky and will need to be done and rolled back
  along with the application

- If the application is hybrid of microservices and traditional components
  downtime may be needed to complete the transition

- You need the infrastructure to do this

- If you have a non-isolated test environment, you can break both new and old
  version.
