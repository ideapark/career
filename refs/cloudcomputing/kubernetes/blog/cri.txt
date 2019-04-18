# cri-containerd

How cri-containerd works for the case when kubelet creates a single-container
pod:

- kubelet calls cri-containerd, via the CRI runtime service API, to create a pod

- cri-containerd uses containerd to create and start a special pause container
  (the sandbox container) and put that container inside the pod's cgroups and
  namespace

- cri-containerd configures the pod's network namespace using CNI

- kubelet subsequently calls cri-containerd, via the CRI image service API, to
  pull the application container image

- cri-containerd further uses containerd to pull the image if the image is not
  present on the node

- kubelet then calls cri-containerd, via the CRI runtime service API, to create
  and start the application container inside the pod using the pulled container
  image

- cri-containerd finally calls containerd to create the application container,
  put it inside the pod's cgroups and namespace, then to start the pod's new
  application container. After these steps, a pod and its corresponding
  application container is created and running.
