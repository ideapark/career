# Microservice

A microservice architecture is the natural consequence of applying the single
responsibility principle at the architectural level. This results in a number of
benefits over a traditional monolithic architecture such as independent
deployability, language, platform and technology independence for different
components, distinct axes of scalability and increased architectural
flexibility.

In terms of size, there are no hard and fast rules. Commonly, microservices are
of the order of hundreds of lines but can be tens or thousands depending on the
responsibility they encapsulate. A good, albeit non-specific, rule of thumb is
`as small as possible but as big as necessary to represent the domain concept
they own`.

## Pros and Cons

- Pros

1. Microservices allows for Independent development and deployment
   of the various services. This allows for teams to work and deploy
   at their own pace without having to wait on other teams to finish
   their projects.

2. Due to the loosely coupled structure of a microservices architecture,
   the individual services can scale independently based on their
   needs. Based on the individual requirements of a service, the team
   can decide what resources to use and how many resources are needed
   to make the service available using pools, clusters, and grids.

3. Since each service is loosely coupled each team has a high level
   of autonomy. Each team can choose programming languages and
   libraries that make the most sense for their service. However,
   this freedom could have some drawbacks if the number of technologies
   is not properly managed and operational homogeneity is lost.
   Code within a legacy, monolithic application is known to become
   more complex over time. As a result, various components of an
   application can become difficult to understand and maintain. Within
   a microservices architecture, the individual services are generally
   smaller in size and scope making microservice easier to analyze and
   develop. This is especially true for new developers.

4. If a service goes down for any reason, the rest of the application
   is left untouched. Microservices creates a more fault tolerant and
   resilient system. Also, the fact that each service is smaller in
   scope and easier to maintain means that, in theory, a service that
   goes down should be easier to fix.

5. A microservices architecture allows managers to divide their teams
   up differently than a team managing a monolithic application. Teams
   are no longer divided across operations and developer lines. Instead,
   teams are built around the service that needs to be developed and
   managed. As a result, teams are focused on their individual
   microservice and can develop and manage their application at a much
   quicker rate.

6. Because microservice are smaller in size and scope, teams don't have
   to enter a long-term commitment with their initial technology stack.
   Given that the microservice is a smaller size and it is efficient
   to do so, then the team can simply retool their microservices to a
   new stack.

7. Teams can also make technology upgrades independently and at their
   own discretion. This can be very beneficial because it does not
   force changes to a particular component if not needed.

8. With a microservices architecture, it is common practice for service
   to be segmented around business capabilities. This results in clear
   cut lines between various components of the application. While this
   can be achieved with a monolithic application, sometimes it is not
   always easy to manage. Microservice aides in the organization and
   management of the code.

9. Hotfixes are easier and quicker to deploy because teams only have
   to fix and deploy the isolated service instead of being forced to
   deploy the entire application.

- Cons

1. A microservices architecture necessitates a distributed system which
   can be complex and hard to manage. Having the right resources and
   knowledge can be an inhibitor for organizations considering a
   transition.

2. Microservices creates an increased amount of infrastructure and
   increased operations management. Each service will require its own
   resources, monitoring, and testing. Additionally, replicating the
   automated build, test, and deployment pipeline of each service
   using continuous delivery practices is a standard for most
   microservices infrastructures.

3. Testing within each service is not anything unusual or difficult.
   However, testing an application utilizing a microservices architecture
   is not cut and dry. Testing the entire application as a whole, and
   how services function with one another can be difficult.

4. Since microservices are isolated from one another, developers have
   the opportunity to choose which technologies, languages, and
   libraries should be used for their component. While this is on the
   list of advantages, a polyglot environment could lead to a more
   chaotic and hard to manage application.

5. Common practice in a microservices architecture is to segment services
   and their corresponding data management systems. Since each database
   is segmented to support the service, management of the databases and
   its data becomes much more difficult.

6. While most argue that team segmentation is generally a positive thing,
   management complexity increases when teams are separated and working
   in isolation. Orchestration of microservices brings about a need for
   increased communication throughout the organization.

7. A microservices architecture could increase the amount of memory
   used. In most applications, several classes and libraries are often
   replicated in each microservice bundle and the overall memory footprint
   increases.

8. Depending on how you implement communications between microservices,
   there could be decreased performance due to increase in communication
   between various services via HTTP calls.
