# Kubernetes vs OpenShift

## OpenShift product vs. Kubernetes project

  1. OpenShift Container Platform is a product that you can install on your
     infrastructure that has a paid support included that comes with a
     subscription

  2. You need to renew your OpenShift subscription for your cluster and you pay
     more when your cluster grows

  3. Kubernetes has many distributions, but it's a project and if something bad
     happens you can count mostly on community or external experts (in some
     cases they might be sometimes better than Red Hat support)

  4. Kubernetes has many releases per year (4 actually), OpenShift has also many
     releases, but it falls behind Kubernetes release schedule -- currently it's
     one release (OpenShift 3.10 includes Kubernetes 1.10 while the newest
     release at the time of writing of this article is 1.11)

  5. As product OpenShift subscription includes CloudForms that enhance it with
     its features (e.g. configurable chargeback, monitoring, central
     provisioning etc.

  6. OKD version is free to use and includes most of the features of its
     commercial product, but you cannot buy a support nor you cannot use Red Hat
     based offical images)

## OpenShift limited installation vs. install Kubernetes (almost) anywhere

If you decide to install OpenShift you need to use either Red Hat Enterprise
Linux (or Red Hat Atomic) for OpenShift Container Platform and additionally
CentOS for OKD. You cannot install it on other linux distributions. Kubernetes,
on the other hand, can be installed almost on any linux distribution such as
Debian, Ubuntu (most popular) and many others.

## OpenShift has more strict security policies than default Kubernetes

OpenShift forbids to run a container as root and even many of official images
don't meet this requirement.

As a part of OpenShift you can install additional component such as:

- Internal Container Registry
- Logging stack based on EFK (ElasticSearch, Fluentd, Kibana)
- Monitoring based on Prometheus
- Jenkins

And you use a single account to authenticate to them with OAuth mechanism
(oauth-proxies running as sidecars). That makes permissions management easier
and can bring additional features like in EFK where you see logs only from
namespaces/projects you have access to. And yes - you can achieve the same on
Kubernetes as well, but it requires a lot of work.

## OpenShift templates are less flexible than Kubernetes Helm charts

Helm is so much better, but its current architecture (Tiller component installed
as Pod with huge permissions) isn't compatible with more strict security
policies in OpenShift.

## Routers on OpenShift vs. Ingress on Kubernetes

OpenShift have a Route objects which do almost the same job as Ingress in
Kubernetes. The main difference is that routes are implemented by good, old
HAproxy that can be replaced by commercial solution based on F5 BIG-IP. On
kubernetes, however, you have much more choice, as Ingress is an interface
implemented by multiple servers from most popular nignx, traefik, AWS ELB/ALB,
GCE, Kong and others including HAproxy as well.

OpenShift router has integration with cert-manager that allows you to automate
management of SSL certificates. No more manual actions for issuing and renewal
of certificates and additionally you can use trusted CA for free thanks to
integration with Letsencrypt!

## A different approach to deployments

In Kubernetes there are Deployment objects (you can use them in OpenShift with
all other Kubernetes objects as well) responsible for updating pods in a rolling
update fashion and is implemented internally in controllers. OpenShift has a
similar object called DeploymentConfig implemented not by controllers, but
rather by sophisticated logic based on dedicated pods controlling whole process.
It has drawbacks, but also one significant advantage over Kubernetes
Deployment - you can use hooks to prepare your environment for an update - e.g.
by chaning database schema. It's a nifty feature that is hard to implement with
Deployment (and no, InitContainers are not the same, as it's hard to coordinate
it with many instances running). Deployment, however, is better when dealing
with multiple, concurrent updates - DeploymentConfig doesn't support concurrent
updates at all and in Kubernetes you can have many of them and it will manage to
scale them properly.

## Better management of container images

  1. with ImageStream you upload a container image once and then you manage it's
     virtual tags internally in OpenShift - in one project you would always use
     devel tag and only change reference to it internally, on prod you would use
     stable or prod tag and also manage it internally in OpenShift, not dealing
     with registry!

  2. when using ImageStream with DeploymentConfig you can set a trigger which
     starts deployment when a new image appears or tag changes its reference -
     it's perfect for development environments where app deploys itself whenever
     a new version is built (without any CI/CD process!)

  3. with triggers you can achieve even more - having chained builds to create
     an updated version of your app/tool whenever a new version of the base
     image is published - it's an automated patching of all container images
     built from insecure images at hand!

  4. you can hide the origin of the image by exposing it as an ImageStream -
     e.g. one time jenkins points to a original, official image and when you
     with to change something, you build your own, push it to your registry and
     change only reference in ImageStream, not in deployment configs like you
     would with traditional docker images.

## Integrated CI/CD with Jenkins

There are multiple CI/CD software solutions available, but Jenkins is still the
biggest, most universal, generic and mature solution. It is often used with
Kubernetes clusters to build container images, perform Continuous Integration
tasks on them and deploy them as containers on multiple environments with
Continuous Deployment pipelines. Since it's so popular then having it as a
builtin part of OpenShift makes the whole CI/CD a lot less painful. Here is a
list of features of integrated Jenkins on OpenShift:

  1. OAuth authentication - use your OpenShift login to log in to Jenkins and
     depending on the whole role you have on the project you get one of three
     jenkins role assigned (view, edit or admin)

  2. support for source-to-image that allows you to create a custom jenkins
     image - a few files with plugins list, custom configuration and other
     resources, enable you to easily update it when a source image changes (that
     part also can be automated!) and use Jenkins in a fully "immutable" mode.

  3. two version of template available - ephemeral for testing purposes and
     persistent with persistent storage for more serious job, configuration data
     and job history is kept seperately from Jenkins itself and thus making it
     very easy to manage (e.g. upgrades, testing different sets of plugins)

  4. synchronizatoin of secret object from a namespace it's running on -
     different secrets are synchronized with Jenkins credentials so that
     username/password, ssh key or secret text are available in your jobs
     without ever creating them in Jenkins

  5. last but not least - pipeline definition is a separate BuildConfig object
     and is also defined outside of Jenkins as a OpenShift object from simple
     yaml file

## OpenShift prjects are more than Kubernetes namespaces

Besides trivial things such as description and display name (they can be helpful
when you have dozens of them), projects add some default objects. Currently a
few roles (rolebinding objects to be precise) are created alongside with a
project, but you can modify default project for external traffic so that is
isolated and secure by default - if you want to permit some kind of traffic you
would do so by creating additional policies explicitly. In a similar way you
could provide default quotas or limitrange objects and make your new projects
preconfigured according to your organization rules.

## OpenShift is easier for beginners

When it comes to User experience. Containers are still new and having a complex,
sophisticated interface for managing them makes it even harder to learn and
adapt. OpenShift versions of both command line and web interfaces are superior
over Kubernetes ones.

- *oc* vs *kubectl*

  1. *oc* has support for logging to OpenShift cluster - with kubectl you need
     to obtain your credentials and create your kubeconfig file with some
     external tools

  2. *oc* lets you switch between projects/namespaces while *kubectl* doesn't
     (you need external tools such as kubens/kubectx) - if you start working
     with many namespaces and clusters you will appreciate that features

  3. *oc* allows you to build a container image from a source and then deploy it
     onto environments with a single command (oc new-app) it will create all
     required objects for you and then you may decide to export them, change and
     reapply or store somewhere in your repository

- OpenShift Web Console vs Kubernetes Dashboard

Kubernetes Dashboard doesn't bring much more informatoin than comand line and
you are not able to change most of the things - it's almost like read-only
panel. Dashboard is not a first-class citizen among many Kubernetes projects.

As to OpenShift Web Console, first of all it has a login window, something that
simple and trivial and I know it shouldn't be a feature, but have you seen
Kubernetes "login window"? Dashboard has a login window where you provide a
token and honestly is confusing, especially for beginners. Most of all OpenShift
Web Console is very useful, much more than Kubernetes Dashboard. In fact, you
can perform about 80% of tasks directly from it - no need to launch command line
or dealing with yaml objects - it can be actually a primary tool for managing
OpenShift on a daily basis.
